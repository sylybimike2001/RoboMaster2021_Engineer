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
    bool keepRunning =0;
    receive_config_data.start=1;
    RmSerial rmSerial;
    rmSerial.init();
    while (1){
        if(0){}
        //监听信息
    }
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
    Mineral MineralDetector;
    Barrier BarrierDetector;




}


