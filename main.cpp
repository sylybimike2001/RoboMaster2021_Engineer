#include <iostream>
#include <mineral.h>
#include <barrier.h>
#include <rmconfig.h>
#include <rmserial.h>
using namespace std;
using namespace cv;
using namespace std;
using namespace cv;
unsigned char *yuv422rame = NULL;
unsigned long yuvframeSize = 0;
char devices[40] = "/dev/video2";
McuConfig receive_config_data;              //extern
RmSerial rmSerial;                          //extern
/*
 * 曝光：
 * 1、小资源岛白色矿石100
 * 2、大资源岛黄色矿石300+
 */
int main()
{
    bool keepRunning =1;
    rmSerial.init();
    receive_config_data.state = SMALL_RESOURCE_ISLAND_AUTO_RUN;   //单片机上电时给出状态：FREE——MODE
    Mineral MineralDetector;                                    //矿石检测实例化对象
    waitKey( 100);

    while(keepRunning){                                         //死循环
        switch (receive_config_data.state){
            case  BIG_RESOURCE_ISLAND_AUTO_RUN:
            {
                cout << "Mode:BIG_RESOURCE_ISLAND_AUTO_RUN" << endl;
                V4L2Capture cap(devices, 720, 480);
                cap.set_exposure(300);
                MineralDetector.runBigResourceIsland(cap);      //进入函数内部等待单片机发出启动指令
            }
                break;
            case SMALL_RESOURCE_ISLAND_AUTO_RUN:{
                cout<< "Mode:SMALL_RESOURCE_ISLAND_AUTO_RUN"<<endl;
                V4L2Capture cap(devices, 720, 480);
                cap.set_exposure(300);
                MineralDetector.runSmallResourceIsland(cap);
            }
                break;
            case FREE_MODE:
                cout<<"free mode"<<endl;
                break;
            default:
                return 2;
        }
    }
}


