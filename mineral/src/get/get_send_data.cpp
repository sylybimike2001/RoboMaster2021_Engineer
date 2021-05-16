#include <mineral.h>
#include <datatypes.h>
/*
 * 函数说明：
 * １、功能：获得发送数据的结构体
 * ２、参数：　SendData &data　发送数据
 *          　int index      第index个数据
*/
void Mineral::getSendData(SendData &data,int index){

    int error_x =all_fit_points[index-1].x-(float)src.size().width/2;
    int threshold = src.size().width/2;
    if(error_x<0) {
        data.direction_x = 'l';
        data.error_x = 0-error_x;
        if(data.error_x>threshold) data.error_x = threshold;
    }
    else {
        data.direction_x = 'r';
        data.error_x = error_x;
        if(data.error_x>threshold) data.error_x = threshold;
    }


    //采用默认值
    data.start_flag='s';
    data.isStandard = 1;
    data.isVertical = 1;
    data.Errordata = 0;
    data.end_flag = 'e';

    if(0) {
#ifdef DEBUG
        std::cout<<"Wrong Data"<<std::endl;
#endif
        data.Errordata = 1;
    }
}