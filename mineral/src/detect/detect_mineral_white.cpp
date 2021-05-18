#include <parameter.h>
#include <mineral.h>
#include <rmserial.h>
#include <rmconfig.h>


void Mineral::detectWhiteMineral(Mat &operand) {
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

    cvtColor(src,dst,COLOR_BGR2GRAY);
    blur(dst,dst,Size(3,3));

    Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3));
    Mat kernel_large = getStructuringElement(MORPH_RECT,Size(9,9));
    //morphologyEx(dst,dst,MORPH_CLOSE,kernel);

    GammaTransform(dst,dst);
    erode(dst,dst,kernel);
    //erode(dst,dst,kernel);
    //erode(dst,dst,kernel);
    dilate(dst,dst,kernel_large);
    //morphologyEx(dst,dst,MORPH_CLOSE,kernel);
    threshold(dst,dst,80,255,THRESH_BINARY);


#ifdef DEBUG
    imshow("after Mor",dst);
    waitKey(1);
#endif

    //找轮廓
    vector<vector<Point>> Contours;
    vector<Vec4i> hierarchy;
    Canny(dst, dst, 80, 100);
    findContours(dst, Contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //筛选轮廓
    for (int i = 0; i < Contours.size(); i++) {
        if(arcLength(Contours[i],1)<mineral_white_threshold_length) continue;
        RotatedRect fit_rotated = minAreaRect(Contours[i]);
        Rect fit = boundingRect(Contours[i]);                                                       //矩形拟合合适的轮廓
//        bool scale_fit = float(fit.width) / fit.height < mineral_white_threshold_scale_high &&                //通过长宽比筛选
//                         float(fit.width) / fit.height > mineral_white_threshold_scale_low;
//        bool area_fit = float(fit.width) * float(fit.height) > mineral_white_threshold_area_low&&float(fit.width) * float(fit.height) < mineral_white_threshold_area_high;             //通过区域面积筛选
       // bool scale_fit = float(fit.width) / fit.height < mineral_white_threshold_scale_high &&                //通过长宽比筛选
       //                  float(fit.width) / fit.height > mineral_white_threshold_scale_low;
        double area_rect = float(fit.width) * float(fit.height);
        double area_contour = contourArea(Contours[i]);
        double decrease = area_rect-area_contour;
        bool area_fit = float(fit_rotated.size.width) * float(fit_rotated.size.height) > mineral_white_threshold_area_low&&
                        float(fit_rotated.size.width) * float(fit_rotated.size.height) < mineral_white_threshold_area_high;             //通过区域面积筛选
        bool scale_fit = float(fit_rotated.size.width) / fit_rotated.size.height < mineral_white_threshold_scale_high &&                //通过长宽比筛选
                         float(fit_rotated.size.width) / fit_rotated.size.height > mineral_white_threshold_scale_low;
                if (scale_fit&&area_fit&&decrease>500) {
            all_fit_rects.push_back(fit);
#ifdef DEBUG
            rectangle(BackGround,fit, Scalar(255, 0, 0), 2);
            drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
        }
    }
    for(auto item:all_fit_rects){
        Point center;
        center.x = item.x+item.width/2;
        center.y = item.y+item.height/2;
        all_fit_points.push_back(center);
    }
    getFitPoints(all_fit_rects,all_fit_points);
    sortPointsVector(all_fit_points,1);
    Number_white = all_fit_points.size();


#ifdef __DEBUG__WRITER

#endif
#ifdef DEBUG
    //if(receive_config_data.start) sendTarget();
    //else cout<<"Not Sending data"<<endl;
    sendTarget();
    for(auto item:all_fit_points){
        circle(BackGround,item,1,Scalar(0,255,0),4);
//        cout<<"Size"<<all_fit_points.size()<<endl;
//        cout<<"坐标：("<<item.x<<","<<item.y<<")"<<endl;
    }
    //cout<<"NUmber of Rects"<<all_fit_rects.size()/2<<endl;
    imshow("result",BackGround);
#endif

}
