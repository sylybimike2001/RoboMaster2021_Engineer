#include<opencv2/opencv.hpp>
using namespace cv;
/*
 * 参数说明：用于检测闪光灯，参考北部赛区结果后，废弃
 */
//detect flash
#define flash_threshold_scale_low 0.8
#define flash_threshold_scale_high 1.2
#define flash_threshold_area_high 600
#define flash_threshold_area_low 0

/*
 * 参数说明：用于检测黄色矿石
 * 1、检测黄色矿石所使用的比例约束和面积约束
 * 2、比例约束：近距离基本不会出现干扰，比例容忍度较高
 * 3、面积约束：工程贴近资源岛时，黑色标志点面积很大，面积上限较高
 */
//detect mineral
#define mineral_threshold_scale_low 0.8
#define mineral_threshold_scale_high 1.2
#define mineral_threshold_area_low 400//70
#define mineral_threshold_area_high 10000//600
#define mineral_threshold_canny_low 30
#define mineral_threshold_canny_high 100
/*
 * 参数说明：
 * 1、用于检测高处矿石，粗对位，不建议使用
 * 2、仰角看矿石会扁，长宽比例阈值放大
 */
//detect mineral high
#define mineral_high_threshold_scale_low 0.9
#define mineral_high_threshold_scale_high 1.8
#define mineral_high_threshold_area_low 400
#define mineral_high_threshold_area_high 160000
#define mineral_threshold_error 15  //水平方向error小于15认为对位完成
/*
 * 参数说明：
 * 1、用于检测障碍块
 */
//detect barrier
#define barrier_threshold_scale_low 0.8
#define barrier_threshold_scale_high 1.2
#define barrier_threshold_area_low 100
#define barrier_threshold_area_high 160000
#define barrier_threshold_length 80
#define barrier_threshold_bin 30

/*
 * 参数说明：
 * 1、用于检测小资源岛上白色矿石
 * 2、比例条件和面积条件比较苛刻
 * 3、二值化阈值说明：待补充
 */
//detect white mineral
#define mineral_white_threshold_scale_low 0.9
#define mineral_white_threshold_scale_high 1.1
#define mineral_white_threshold_area_low 1600
#define mineral_white_threshold_area_high 10000
#define mineral_white_threshold_length 150
#define mineral_white_threshold_bin 30

#ifdef DEBUG
#include <iostream>
#endif

