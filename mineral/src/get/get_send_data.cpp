#include <mineral.h>
#include <datatypes.h>

void Mineral::getSendData(SendData &data,int index){


    int error_x =all_fit_points[index].x-(float)src.size().width/2;
    if(error_x<0) {
        data.direction_x = 'l';
        data.error_x = 0-error_x;
        if(data.error_x>120) data.error_x = 120;
    }
    else {
        data.direction_x = 'r';
        data.error_x = error_x;
        if(data.error_x>120) data.error_x = 120;
    }


    //y方向误差计算
    data.error_y=0;
    int error_y =all_fit_points[index].y-(float)src.size().height/2;
    if(error_y<0) data.direction_y = 'u';
    else data.direction_y = 'd';
    data.error_y =error_y;
    if(data.error_y>120) data.error_y = 120;

    //采用默认值
    data.start_flag='s';
    data.Standard = 1;
    data.Vertical = 1;
    data.Errordata = 0;
    data.end_flag = 'e';

    if(all_fit_points.size()!=3&&all_fit_points.size()!=7) {
#ifdef DEBUG
        std::cout<<"Wrong Data"<<std::endl;
#endif
        data.Errordata = 1;
    }
}