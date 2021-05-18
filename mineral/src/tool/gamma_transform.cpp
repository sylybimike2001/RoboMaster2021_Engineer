#include <mineral.h>

void  Mineral::GammaTransform(Mat &image,Mat &dist)
{
    Mat imageGamma;
    //灰度归一化
    image.convertTo(imageGamma, CV_64F, 1.0 / 255, 0);

    //伽马变换
    double gamma = 1.8;

    pow(imageGamma, gamma, dist);//dist 要与imageGamma有相同的数据类型

    dist.convertTo(dist, CV_8U, 255, 0);
}
