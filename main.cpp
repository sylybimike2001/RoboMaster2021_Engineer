#include <iostream>
#include "mineral/include/mineral.h"
#include "./com/include/rmserial.h"
using namespace std;
using namespace cv;
using namespace std;
using namespace cv;

int main()
{
    /*
    uint8_t start_flag;                     //帧头是‘s’，帧尾是‘e’
    float error;                            //矿石中间点和图像中心点（车正中心）的偏差
    uint8_t Vertical;                       //图像y方向是否对齐
    uint8_t Standard;                       //图像x方向是否对齐（线是否水平）
    uint8_t end_flag;
    */

    Mineral MINERAL_DETECTOR;
    MINERAL_DETECTOR.run();
    cout<<"project start"<<endl;
}


