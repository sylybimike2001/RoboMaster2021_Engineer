#include <mineral.h>
/*
 * 函数说明：
 * 1、功能说明:gamma变换
 * 2、参数说明：Mat &image 原图像
 *            Mat &dist 输出图像
 * 3、版本 V1.0
 */
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
