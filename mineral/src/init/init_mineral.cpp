#include <mineral.h>
#include <rmconfig.h>
/*
 * 函数说明：
 * 1、函数功能：初始化对象
 */
bool Mineral::initMineral() {
    isHorizontal = false;
    all_fit_rects.clear();
    all_fit_points.clear();
    TargetNumber = 0;
    Number = 0;
    Number_white = 0;
    Number_high = 0;
}