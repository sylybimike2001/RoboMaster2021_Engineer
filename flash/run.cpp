#include <flash.h>
#include <rmconfig.h>
void Flash::run() {
    initFlash();
    while (keepRunning)
    {
        if (use_cam) {
            cutecap >> src;
            if (src.empty()) break;
            cv::resize(src, src, cv::Size(640, 360));
        }
//        Detect_line(src,cutecap);
//        Select_ROI(src);
        detectFlash(src);
    }
}