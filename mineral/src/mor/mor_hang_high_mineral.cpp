#include <mineral.h>

void Mineral::MorMineral(Mat & operand,Mat &output){

    blur(operand,output,Size(9,9));
    vector<Mat> hsvSplit;
    cvtColor(output,output, COLOR_BGR2HSV);
    split(output, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, output);

    Mat kernel_small = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat kernel_middle = getStructuringElement(MORPH_RECT, Size(5, 5));
    //Mat kernel_large = getStructuringElement(MORPH_RECT, Size(9, 9));

    inRange(output, Scalar(15, 80, 80), Scalar(34, 255, 255), output);//全距离
    erode(output,output, kernel_middle);
    erode(output,output, kernel_small);
    dilate(output,output, kernel_small);
}