#include <mineral.h>
#include <datatypes.h>
#include <rmconfig.h>


bool Mineral::sendTarget() {
    SendData data;
//    if(receive_config_data.state == BIG_RESOURCE_ISLAND_AUTO_RUN){
//    switch(TargetNumber) {
//        case 1:{
//            getSendData(data,1);
//            rmSerial.send_data(data);
//        }
//
//        case 2: {
//            getSendData(data,2);
//            rmSerial.send_data(data);
//        }
//        case 3: {
//            getSendData(data,3);
//            rmSerial.send_data(data);
//        }
//        case 4: {
//            getSendData(data,4);
//            rmSerial.send_data(data);
//        }
//        case 5: {
//            getSendData(data,5);
//            rmSerial.send_data(data);
//        }
//        default:
//                return 0;
//    }}
//    if(receive_config_data.state == SMALL_RESOURCE_ISLAND_AUTO_RUN){
        getSendData(data);
//    }
    //x方向误差计算

}