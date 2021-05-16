#ifndef H_RM_SERIAL_DATA_TYPES
#define H_RM_SERIAL_DATA_TYPES
#include <stdint.h>
#pragma pack(push, 1)       //????

//*************************************************************************
//**
//         **         **         **          **          **
//      ********** ********** ********** *********** ***********
//      *        * *        * *        * *         * *         *
//      *        * *        * *        * *         * *         *
//从左到右分别是1-5号矿石（不论红方蓝方）

//发出去的结构体
typedef struct _SendData {
    uint8_t start_flag;                         //帧头是‘s’
    uint16_t error_x;                           //矿石中间点和图像中心点（车正中心）的偏差
    uint8_t direction_x;                        //‘l’表示在图像视野左侧，‘r’表示图像在视野右侧
    uint8_t number_to_release;                  //标志哪个矿石即将掉落
    uint8_t is_error_data;                      //标志本次是否为错误数据
    uint8_t is_standard;                         //图像x方向是否对齐（线是否水平)
    uint8_t end_flag;                           //帧尾是‘e’
} SendData;
#define BARRICADE_AUTO_RUN 1
#define BIG_RESOURCE_ISLAND_AUTO_RUN 2
#define SMALL_RESOURCE_ISLAND_AUTO_RUN 3
#define Engineer_TYPE 4
//接受的数据类型

struct McuData {
    uint8_t start_flag;
    uint8_t state;                  // 当前状态，闪光灯检测，闪光灯对位，精确对位，小资源岛对位
    uint8_t start;                  // 是否启动该状态
    uint8_t barrier_ok;             // 操作手发来的信号，开始返回error并接管底盘速度
    uint8_t wrong_data;             // 如果是１表明是错误数据
    uint8_t end_flag;
};

typedef struct _PanData {
    uint8_t start_flag;
    uint8_t type;
    float yaw;
    float pitch;
    uint8_t end_flag;
} PanData;

typedef struct _ConfigData {
    uint8_t start_flag;
    uint8_t type;
    uint8_t state;
    uint8_t anti_top;
    uint8_t enemy_color;
    uint8_t empty_buff[5];
    uint8_t end_flag;
} ConfigData;

typedef struct _EnergyData {
    uint8_t start_flag;
    uint8_t type;
    int delta_x;
    int delta_y;
    uint8_t end_flag;
} EnergyData;

typedef struct _SpeedData {
    uint8_t start_flag;
    uint8_t type;
    float speed;
    float empty_buff;
    uint8_t end_flag;
} SpeedData;

#pragma pack(pop)



#endif

/*
 * typedef struct _McuData {
    uint8_t start_flag;
    uint8_t type;
    uint8_t start;
//    uint32_t x;
//    uint32_t y;
    uint8_t end_flag;
} McuData;
 */