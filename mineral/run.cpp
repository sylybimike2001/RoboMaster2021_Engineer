#include <mineral.h>
#include <rmconfig.h>
#include <iostream>
using namespace std;
//McuConfig receive_config_data;
void Mineral::run() {
    initMineral();
    while (1)
    {
        if (use_cam) {
            cutecap >> src;
            if (src.empty()) {
                break;
            }
            //cv::resize(src, src, cv::Size(640, 640));
        }
        //Detect_line(src,cutecap);
        //Select_ROI(src);
        Detect_mineral(src,cutecap);
    }
}