#include <mineral.h>
#include <rmconfig.h>
#include <uvc_v4l2.h>
void Mineral::runBigResourceIsland(V4L2Capture & cap) {
    initMineral();
    receive_config_data.start = 1;
    while (receive_config_data.state==BIG_RESOURCE_ISLAND_AUTO_RUN&&
                receive_config_data.start == 1&&isHorizontal == 0)      //接收到单片机开始对位的指令
    {
        if (use_cam) {
            cap>>src;
            if (src.empty()) {
                cout << "empty" << endl;
                break;
            }
        }
        detectYellowMineral(src);
    }
}
void Mineral::runSmallResourceIsland(V4L2Capture & cap) {
    initMineral();
    receive_config_data.start = 1;
    while (receive_config_data.state==SMALL_RESOURCE_ISLAND_AUTO_RUN&&
           receive_config_data.start == 1 && isHorizontal == 0)
    {
        if (use_cam) {
            cap>>src;
            if (src.empty()) {
                cout<<"empty"<<endl;
                break;
            }
        }
        detectWhiteMineral(src);
    }
}