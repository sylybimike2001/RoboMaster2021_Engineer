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
#define mineral_threshold_area_low 60
#define mineral_threshold_area_high 600

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

#define __DEBUG__WRITER
