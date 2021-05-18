#include <mineral.h>
#include <rmconfig.h>
#include <uvc_v4l2.h>
void Mineral::run(V4L2Capture & cap) {
    initMineral();
    while (1)
    {
        if (use_cam) {
            cap>>src;
            if (src.empty()) {
                break;
            }
        }
//        detectMineralHigh(src);
        detectWhiteMineral(src);
        //locateMineralHigh();

    }
}
void Mineral::run(VideoCapture & cap) {
    initMineral();
    while (1)
    {
        if (use_cam) {
            cap>>src;
            if (src.empty()) {
                break;
            }
        }
//        detectMineralHigh(src);
        detectWhiteMineral(src);
        //locateMineralHigh();

    }
}