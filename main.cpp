#include <iostream>
#include <mineral.h>
#include <barrier.h>
using namespace std;
using namespace cv;
using namespace std;
using namespace cv;
unsigned char *yuv422rame = NULL;
unsigned long yuvframeSize = 0;
char devices[40] = "/dev/video0";

int main()
{
    /*
    uint8_t start_flag;                     //帧头是‘s’，帧尾是‘e’
    float error;                            //矿石中间点和图像中心点（车正中心）的偏差
    uint8_t Vertical;                       //图像y方向是否对齐
    uint8_t Standard;                       //图像x方向是否对齐（线是否水平）
    uint8_t end_flag;
    */
    receive_config_data.start=1;
//    Mineral MINERAL_DETECTOR;
//    MINERAL_DETECTOR.run();
//    cout<<"project start"<<endl;
//    V4L2Capture cap(devices, 720, 480);
//    cap.set_exposure(1000);
//    bool keepRunning = 1;
//    Barrier BARRIER_DETECTOR;
//    Mineral MINERAL_BOSS;
//    MINERAL_BOSS.run(cap);
//    //BARRIER_DETECTOR.run(cap);



}


