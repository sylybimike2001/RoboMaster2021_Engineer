#include <mineral.h>
#include <rmconfig.h>
#include <uvc_v4l2.h>
void Mineral::run(V4L2Capture & cap) {
    initMineral();
    while (1)
    {
        if (use_cam) {
            //cutecap >> src;
            cap>>src;
            //resize(src,src,Size(src.size().width/2,src.size().height/2));
            if (src.empty()) {
                break;
            }
        }
        detectMineralHigh(src);
        locateMineralHigh();

    }
}