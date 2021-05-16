#include <parameter.h>
#include <mineral.h>
#include <rmserial.h>

/*
 * 函数说明
 * 1、功能：检测高处的矿石，放入容器中
 * 2、参数：
 *      Mat &operand摄像机读取的图像
 *      VideoCapture &capture 摄像头实例化对象
 * 3、版本：Version1.0
 */



void Mineral::detectMineralHigh(Mat &operand,VideoCapture &capture){
    //初始化各容器
    Number = 0;
    all_fit_rects.clear();
    all_fit_points.clear();
#ifdef DEBUG
    imshow("current", operand);
    waitKey(1);
#endif

    //形态学操作，src不会被改变
    Mat dst(operand.size(), CV_8UC3);
    MorMineral(operand,dst);

#ifdef DEBUG
    Mat BackGround = Mat::zeros(operand.size(), CV_8UC3);
    imshow("after Mor",dst);
    waitKey(1);
#endif

    //轮廓提取
    vector<vector<Point>> Contours;
    vector<Vec4i> hierarchy;
    Canny(dst, dst, 30, 50);
    findContours(dst, Contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //筛选轮廓
    //依据：面积，长宽比例，轮廓周长
    for (int i = 0; i < Contours.size(); i++) {
        if(arcLength(Contours[i],1)<30) continue;                       //周长太小的轮廓舍弃
        Rect fit = boundingRect(Contours[i]);                                  //矩形拟合合适的轮廓
        bool scale_fit = float(fit.width) / fit.height < mineral_high_threshold_scale_high &&                //通过长宽比筛选，低处看高处的矿石，近似是矩形，筛选条件宽容
                         float(fit.width) / fit.height > mineral_high_threshold_scale_low;

        bool area_fit = float(fit.width) * float(fit.height) > mineral_high_threshold_area_low&&
                        float(fit.width) * float(fit.height) < mineral_high_threshold_area_high;             //通过区域面积筛选

        if (scale_fit&&area_fit) {
            all_fit_rects.push_back(fit);
#ifdef DEBUG
            rectangle(BackGround, fit, Scalar(255, 0, 0), 2);
            drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
        }
    }

#ifdef DEBUG
    imshow("Detect Mineral High", BackGround);
    waitKey(1);
#endif
}
