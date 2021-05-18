#include <mineral.h>
#include <datatypes.h>
#include <parameter.h>
/*
 * 函数说明：
 * １、功能：获得发送数据的结构体
 * ２、参数：　SendData &data　发送数据
 *          　int index      第几个矿石
*/
void Mineral::getSendData(SendData &data,int index){
    //传进来的是矿石的编号，调用数组中的元素时-1
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
    data.is_standard = 0;
    data.is_error_data = 0;
    data.end_flag = 'e';
    data.number_to_release = index;

    //留给调车的时候发现干扰项
    if(0) {
#ifdef DEBUG
        std::cout<<"Wrong Data"<<std::endl;
#endif
        data.is_error_data = 1;
    }
    if(data.error_x<mineral_threshold_error) data.is_standard =1;
}

void Mineral::getSendData(SendData &data){
    int error_x;
    if(Number_white==1){
        data.is_error_data = 1;
        error_x = all_fit_points[0].x-(float)src.size().width/2;
    }
    else if(Number_white==3){
        error_x = all_fit_points[1].x-(float) src.size().width / 2;
    }
    else {
        data.is_error_data = 1;
        cout<<"Wrong Data"<<endl;
        return;
    }

        int threshold = src.size().width / 3;
        if (error_x < 0) {
            data.direction_x = 'l';
            data.error_x = 0 - error_x;
            if (data.error_x > threshold) data.error_x = threshold;     //输出限幅
        } else {
            data.direction_x = 'r';
            data.error_x = error_x;
            if (data.error_x > threshold) data.error_x = threshold;     //输出限幅
        }
        data.start_flag = 's';
        data.is_standard = 0;
        data.is_error_data = 0;
        data.end_flag = 'e';
        data.number_to_release = 0;
        if (data.error_x < mineral_threshold_error) data.is_standard = 1;
        cout<<"Data sent: "<<data.error_x<<endl;

        //卡尔曼滤波
}