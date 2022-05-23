#include <mineral.h>
#include <datatypes.h>
#include <rmconfig.h>
/*
 * 函数说明：
 * 1、功能说明：给主控板通过串口通讯发送数据
 * 2、参数说明：无
 * 3、状态说明：      障碍块BARRICADE_AUTO_RUN 1
                    大资源岛 BIG_RESOURCE_ISLAND_AUTO_RUN 2
                    小资源岛 SMALL_RESOURCE_ISLAND_AUTO_RUN 3
                    悬空 FREE_MODE 4
 */

bool Mineral::sendTarget() {
    SendData data;
    if(receive_config_data.state == BIG_RESOURCE_ISLAND_AUTO_RUN) {
        getSendData(data,1);
        rmSerial.send_data(data);
    }
    if(receive_config_data.state == SMALL_RESOURCE_ISLAND_AUTO_RUN){
        getSendData(data);
        rmSerial.send_data(data);
    }
}