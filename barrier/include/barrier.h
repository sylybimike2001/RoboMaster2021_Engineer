#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <rmserial.h>
#include <rmconfig.h>
#include <uvc_v4l2.h>
using namespace std;
using namespace cv;


class Barrier{
public:
    bool initBarrier();
    void detectBarrierSingle(Mat &operand,V4L2Capture &cap);
    void detectBarrierDouble(Mat &operand,V4L2Capture &cap);
    bool sendTarget();
    void getFitPoints(vector<Rect> &all_fit_rects,vector<Point> &all_fit_points);
    void getSendData(SendData &data,int index);

    void run(V4L2Capture & cap);
private:
    //VideoCapture cutecap;

    RmSerial rmSerial;
    Mat src;
    vector<Rect> all_fit_rects;
    vector<Rect> all_fit_points;
};
