#include <mineral.h>
#include <rmconfig.h>
#include <iostream>
using namespace std;
void Mineral::run() {
    initMineral();
    while (keepRunning)
    {
        if (use_cam) {
            cutecap >> src;
            if (src.empty()) {
                std::cout << "empty" <<std::endl;
                break;
            }
            //cv::resize(src, src, cv::Size(640, 640));
        }
        //Detect_line(src,cutecap);
        //Select_ROI(src);
        Detect_mineral(src,cutecap);
    }
}