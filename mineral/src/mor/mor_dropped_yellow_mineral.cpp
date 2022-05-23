//
// Created by ayb on 2021/5/20.
//

#include <mineral.h>
void Mineral::MorYellowMineral(Mat & operand,Mat &output){
    vector<Mat> hsvSplit;
    cvtColor(operand,output, COLOR_BGR2HSV);
    split(output, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, output);


    //形态学操作，有改进的空间，可以调这部分
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    GaussianBlur(output, output, Size(5, 5), 3, 3);
    //inRange(dst, Scalar(20, 40, 70), Scalar(34, 255, 255), dst);   //78,99
    //inRange(dst, Scalar(20, 80, 100), Scalar(34, 255, 255), dst);   //近距离
    inRange(output, Scalar(18, 80, 80), Scalar(34, 255, 255),output);//全距离
    //inRange(dst, Scalar(20, 70, 100), Scalar(34, 255, 255), dst);//全距离
    erode(output,output, kernel);
    erode(output, output, kernel);
    dilate(output,output, kernel);
}