#include<opencv2/opencv.hpp>
using namespace cv;
//detect line
#define slope_threshold 70
const Scalar Line_finder_low = Scalar(5,43,46);
const Scalar Line_finder_high = Scalar(12,255,255);
#define line_threshold_length 800


//detect flash
#define flash_threshold_scale_low 0.8
#define flash_threshold_scale_high 1.2
#define flash_threshold_area_high 600
#define flash_threshold_area_low 0

//detect mineral
#define mineral_threshold_scale_low 0.8
#define mineral_threshold_scale_high 1.2
#define mineral_threshold_area_low 100//70
#define mineral_threshold_area_high 6400//600

//detect mineral high
#define mineral_high_threshold_scale_low 0.9
#define mineral_high_threshold_scale_high 1.8
#define mineral_high_threshold_area_low 400
#define mineral_high_threshold_area_high 160000
#define mineral_threshold_error 15  //水平方向error小于15认为对位完成

//detect barrier
#define barrier_threshold_scale_low 0.8
#define barrier_threshold_scale_high 1.2
#define barrier_threshold_area_low 100
#define barrier_threshold_area_high 160000
#define barrier_threshold_length 80
#define barrier_threshold_bin 30

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

