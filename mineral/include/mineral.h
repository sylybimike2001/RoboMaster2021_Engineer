#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <rmserial.h>


using namespace cv;
class Mineral{
public:
    bool initMineral();
    void Detect_line(Mat &operand,VideoCapture &capture);                                     //找资源岛的边界线
    void Select_ROI(Mat &operand);                                      //根据边界线框选下一步的搜索区域
    void Detect_mineral(Mat &operand,VideoCapture &capture);            //在区域内搜索目标，如果检测不到线，全局搜索
    bool sendTarget();
    void getFitPoints(std::vector<Rect> &fitRects,std::vector<Point> &fitPoints);
    void sortPointsVector(std::vector<cv::Point> &all_fit_points);
    void run();
private:
    std::vector<Rect>    all_fit_rects;
    std::vector<Point>   all_fit_points;
    VideoCapture cutecap;
    RmSerial rmSerial;
    Mat src;
    float Max_y;
    float Min_y;
    Rect ROI;
    bool isHorizontal;
    bool ROI_possible;

};
