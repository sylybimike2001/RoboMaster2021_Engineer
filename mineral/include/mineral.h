#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <rmserial.h>
#include <rmconfig.h>

using namespace std;
using namespace cv;
class Mineral{
public:
    bool initMineral();
    void detectMineral(Mat &operand,VideoCapture &capture);            //在区域内搜索目标，如果检测不到线，全局搜索
    bool sendTarget();
    void getFitPoints(std::vector<Rect> &fitRects,std::vector<Point> &fitPoints);
    void sortPointsVector(std::vector<cv::Point> &all_fit_points);
    void getSendData(SendData &data,int index);
    void run();
private:
    std::vector<Rect>    all_fit_rects;
    std::vector<Point>   all_fit_points;
    VideoCapture cutecap;
    RmSerial rmSerial;
    Mat src;
    float Max_y;
    float Min_y;
    bool isHorizontal;
    int Number;
};
