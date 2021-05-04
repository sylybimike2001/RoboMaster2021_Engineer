#include <parameter.h>
#include <mineral.h>
#include <rmserial.h>
#include "../../tools/sort/sort_points_vector.cpp"

/*
 * 本函数还需要做优化
 * 1、形态学操作效率低
 * 2、遍历轮廓效率低
 * 3、中心点算法
 *
 *
 */

void Mineral::sortPointsVector(vector<cv::Point> &all_fit_points){
    sort(all_fit_points.begin(),all_fit_points.end(),[](cv::Point &a,cv::Point &b){
        return a.x < b.x;
    });
    vector<cv::Point>::iterator new_end;
    new_end = unique(all_fit_points.begin(),all_fit_points.end());
    all_fit_points.erase(new_end,all_fit_points.end());
}

void Mineral::Detect_mineral(Mat &operand,VideoCapture &capture){
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
        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
        GaussianBlur(dst, dst, Size(3, 3), 3, 3);
        inRange(dst, Scalar(11, 43, 46), Scalar(34, 255, 255), dst);   //78,99
        erode(dst, dst, kernel);
        erode(dst, dst, kernel);
        dilate(dst, dst, kernel);
#ifdef __DEBUG__WRITER
        imshow("after Mor",dst);
        waitKey(1);
#endif

        //找轮廓
        vector<vector<Point>> Contours;
        vector<Vec4i> hierarchy;
        Canny(dst, dst, 10, 50);
        findContours(dst, Contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

        //筛选轮廓

        for (int i = 0; i < Contours.size(); i++) {
            if ((arcLength(Contours[i], false) < mineral_threshold_area_low) || (arcLength(Contours[i], false) > mineral_threshold_area_high)) continue;
            else {
                Rect fit = boundingRect(Contours[i]);                                                     //矩形拟合合适的轮廓
                bool scale_fit = float(fit.width) / fit.height < mineral_threshold_scale_high &&                //通过长宽比筛选
                        (float) fit.width / fit.height > mineral_threshold_scale_low;
                bool area_fit = float(fit.width) * float(fit.height) > mineral_threshold_area_high;             //通过区域面积筛选
                //bool height_fit = fit.br().y <= Max_y;                                                          //通过y坐标筛选，未启用
                if (scale_fit&&area_fit) {
                    all_fit_rects.push_back(fit);
#ifdef DEBUG
                    rectangle(BackGround, fit, Scalar(255, 0, 0), 2);
                    drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
                }
                }
        }
        if(all_fit_rects.size()<2) return;
        getFitPoints(all_fit_rects,all_fit_points);
        sortPointsVector(all_fit_points);
        sendTarget();

#ifdef DEBUG
        imshow("result", BackGround);
        waitKey(1);
        //cout<<"center Point"<<all_fit_points[1]<<endl;
#endif

}
