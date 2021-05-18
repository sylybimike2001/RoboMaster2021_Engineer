#include <mineral.h>
#include <rmconfig.h>
bool Mineral::initMineral() {
//    cutecap  = VideoCapture(capture_index);
//    if(cutecap.isOpened()) std::cout<<"open camera"<<std::endl;
    //rmSerial.init();
    Max_y = 0;
    Min_y = 0;
    Number = 0;
    isHorizontal = false;
    all_fit_rects.clear();
    all_fit_points.clear();
    TargetNumber = 0;
}