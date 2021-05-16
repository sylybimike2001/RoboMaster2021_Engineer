#include <parameter.h>
#include <mineral.h>
#include <rmserial.h>

/*
 * 函数说明
 * 1、用途：检测已经落在大资源岛上的矿石
 * 2、参数：
 *      Mat &operand摄像机读取的图像
 *      VideoCapture &capture 摄像头实例化对象（等新摄像头到了还要改）
 * 3、版本：Version 3.0
 */



void Mineral::detectMineral(Mat &operand){
    Number = 0;
    all_fit_rects.clear();
    all_fit_points.clear();

#ifdef DEBUG
    imshow("current", operand);
    waitKey(1);
    Mat BackGround = Mat::zeros(operand.size(), CV_8UC3);
#endif

    //HSV 空间下分离黄色
    Mat dst(operand.size(), CV_8UC3);
    vector<Mat> hsvSplit;
    cvtColor(operand,dst, COLOR_BGR2HSV);
    split(dst, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, dst);


    //形态学操作，有改进的空间，可以调这部分
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    GaussianBlur(dst, dst, Size(5, 5), 3, 3);
    //inRange(dst, Scalar(20, 40, 70), Scalar(34, 255, 255), dst);   //78,99
    //inRange(dst, Scalar(20, 80, 100), Scalar(34, 255, 255), dst);   //近距离
    inRange(dst, Scalar(15, 80, 80), Scalar(34, 255, 255), dst);//全距离
    //inRange(dst, Scalar(20, 70, 100), Scalar(34, 255, 255), dst);//全距离
    erode(dst, dst, kernel);
    erode(dst, dst, kernel);
    dilate(dst, dst, kernel);

#ifdef DEBUG
    imshow("after Mor",dst);
    waitKey(1);
#endif

    //找轮廓
    vector<vector<Point>> Contours;
    vector<Vec4i> hierarchy;
    Canny(dst, dst, 30, 100);
    findContours(dst, Contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //筛选轮廓
    for (int i = 0; i < Contours.size(); i++) {
            Rect fit = boundingRect(Contours[i]);                                                     //矩形拟合合适的轮廓
            bool scale_fit = float(fit.width) / fit.height < mineral_threshold_scale_high &&                //通过长宽比筛选
                             float(fit.width) / fit.height > mineral_threshold_scale_low;
            bool area_fit = float(fit.width) * float(fit.height) > mineral_threshold_area_low&&float(fit.width) * float(fit.height) < mineral_threshold_area_high;             //通过区域面积筛选
            if (scale_fit&&area_fit) {
                all_fit_rects.push_back(fit);
#ifdef DEBUG
                rectangle(BackGround, fit, Scalar(255, 0, 0), 2);
                drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
        }
    }
    if(all_fit_rects.size()<2) return;

    getFitPoints(all_fit_rects,all_fit_points);
    sortPointsVector(all_fit_points);

    if(all_fit_points.size()<3) return;

    if(all_fit_points.size()==7) Number = 2;
    if(all_fit_points.size()==3) Number = 1;

    cout<<"Number:"<<Number<<endl;

#ifdef __DEBUG__WRITER
    if(receive_config_data.start) sendTarget();
    else cout<<"Not Sending data"<<endl;
#endif
#ifdef DEBUG
    if(Number == 1) circle(BackGround,all_fit_points[1],2,Scalar(0,0,255),2);
    if(Number ==2){
        circle(BackGround,all_fit_points[1],2,Scalar(0,0,255),2);
        circle(BackGround,all_fit_points[all_fit_points.size()-2],2,Scalar(0,255,0),2);
    }
    imshow("result11", BackGround);
    waitKey(1);
#endif
}
