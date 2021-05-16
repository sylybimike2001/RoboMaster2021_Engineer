#ifndef H_RMSERIAL
#define H_RMSERIAL
#include <datatypes.h>
#include "serial/serial.h"

#include <mutex>
//将收到的数据解析到这个结构体里
struct McuConfig {
    uint8_t state;                  // 当前状态，闪光灯检测，闪光灯对位，精确对位，小资源岛对位
    uint8_t start;
    uint8_t mineral_release;        // 释放的是几号矿石
    uint8_t error_x;                // 水平方向误差
    float curr_yaw;       // 当前云台yaw角度
    float curr_pitch;     // 当前云台pitch角
    float bullet_speed;   // 当前弹速
    int delta_x;          // 能量机关x轴补偿量
    int delta_y;          // 能量机关y轴补偿量
    uint8_t wrong_data;     //如果是１表明是错误数据

};


class RmSerial {
public:
    serial::Serial* active_port;
    ~RmSerial();
    bool init_success;                          //标志串口是否开启成功
    bool thread_running;                        //标志接受线程是否运行中
    bool init();                                //初始化：1开启串口 2清空数据接收结构体,使用默认值 3开启数据接收线程
    bool isConnected() { return active_port->isOpen(); }
    bool send_data(const SendData& data);       //发送数据
    bool send_data(uint8_t* data, size_t size); //被bool send_data(const SendData& data)调用,返回值为1表示发送成功
    void start_thread();                        //开启接受线程
    void stop_thread();                         //停止接受线程
};

extern std::mutex receive_mtx;                  //接收数据的全局锁
extern McuConfig receive_config_data;           //用来存储接收到的数据
#endif