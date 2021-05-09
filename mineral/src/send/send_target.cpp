#include <mineral.h>
#include <datatypes.h>
#include <rmconfig.h>


bool Mineral::sendTarget() {
    SendData data;
    switch (Number) {
        case 1:{
            getSendData(data,1);
            rmSerial.send_data(data);
        }

        case 2: {
            getSendData(data,5);        //这里参数传进来1算的是左侧中心，传进来5算的是右侧中心
            rmSerial.send_data(data);
        }
        default:
                return 0;
    }
    //x方向误差计算

}