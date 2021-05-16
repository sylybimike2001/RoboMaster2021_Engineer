#include <parameter.h>
#include <barrier.h>
#include <rmserial.h>


void  GammaTransform(cv::Mat &image, cv::Mat &dist)
{
    Mat imageGamma;
    //灰度归一化
    image.convertTo(imageGamma, CV_64F, 1.0 / 255, 0);

    //伽马变换
    double gamma = 1.5;

    pow(imageGamma, gamma, dist);//dist 要与imageGamma有相同的数据类型

    dist.convertTo(dist, CV_8U, 255, 0);
}

void Barrier::detectBarrierSingle(Mat &operand, V4L2Capture &cap) {
    all_fit_points.clear();
    all_fit_rects.clear();
#ifdef DEBUG
    imshow("current", operand);
    waitKey(1);
    Mat BackGround = Mat::zeros(operand.size(), CV_8UC3);
#endif

    //HSV
    Mat dst(operand.size(), CV_8UC1);
    vector<Mat> hsvSplit;
    cvtColor(operand,dst, COLOR_BGR2HSV);
    split(dst, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, dst);



    //形态学操作，有改进的空间，可以调这部分
    Mat kernel = getStructuringElement(MORPH_RECT,Size(9,9));
    cvtColor(src,dst,COLOR_BGR2GRAY);
    GaussianBlur(dst,dst,Size(5,5),3);
    GammaTransform(dst,dst);
    morphologyEx(dst,dst,MORPH_CLOSE,kernel);
    threshold(dst,dst,20,255,THRESH_BINARY);

#ifdef DEBUG
    imshow("after Mor",dst);
    waitKey(1);
#endif

    //找轮廓
    vector<vector<Point>> Contours;
    vector<Vec4i> hierarchy;
    Canny(dst, dst, 30, 50);
    findContours(dst, Contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //筛选轮廓
    for (int i = 0; i < Contours.size(); i++) {
        if(arcLength(Contours[i],1)<barrier_threshold_length) continue;
        Rect fit = boundingRect(Contours[i]);                                                       //矩形拟合合适的轮廓
        bool scale_fit = float(fit.width) / fit.height < barrier_threshold_scale_high &&                //通过长宽比筛选
                         float(fit.width) / fit.height > barrier_threshold_scale_low;
        bool area_fit = float(fit.width) * float(fit.height) > barrier_threshold_area_low&&float(fit.width) * float(fit.height) < barrier_threshold_area_high;             //通过区域面积筛选
        if (scale_fit&&area_fit) {
            all_fit_rects.push_back(fit);
#ifdef DEBUG
            rectangle(BackGround, fit, Scalar(255, 0, 0), 2);
            drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
        }
    }



#ifdef __DEBUG__WRITER
    if(receive_config_data.start) sendTarget();
    else cout<<"Not Sending data"<<endl;
#endif
#ifdef DEBUG
    cout<<"NUmber of Rects"<<all_fit_rects.size()<<endl;
    imshow("result",BackGround);
#endif
}
