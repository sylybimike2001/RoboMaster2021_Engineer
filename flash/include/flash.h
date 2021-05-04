#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <rmserial.h>
using namespace cv;
class Flash{
public:
    bool initFlash();
    void detectFlash(Mat & operand);
    void run();

private:
    VideoCapture cutecap;
    std::vector<Rect> Rects_flash;       //闪光灯条范围
    RmSerial rmSerial;
    Mat src;

    bool keepRunning;
    bool AboutToRelease;     //表征矿石是否将要落下
};