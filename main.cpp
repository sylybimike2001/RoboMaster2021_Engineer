#include <iostream>
#include <mineral.h>
#include <barrier.h>
using namespace std;
using namespace cv;
using namespace std;
using namespace cv;
unsigned char *yuv422rame = NULL;
unsigned long yuvframeSize = 0;
char devices[40] = "/dev/video2";
McuConfig receive_config_data;
int main()
{
    bool keepRunning =0;
    receive_config_data.start=1;
    receive_config_data.state == SMALL_RESOURCE_ISLAND_AUTO_RUN;
    V4L2Capture cap(devices, 720, 480);
    cap.set_exposure(100);
   // bool keepRunning = 1;
//    Barrier BARRIER_DETECTOR;
//    BARRIER_DETECTOR.run(cap);
//    VideoCapture cap(0);
    Mineral MINERAL_BOSS;
    MINERAL_BOSS.run(cap);


}


