#include <mineral.h>

void Mineral::MorWhiteMineral(Mat & operand,Mat &output){
    vector<Mat> hsvSplit;
    cvtColor(operand,output, COLOR_BGR2HSV);
    split(output, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, output);



    //形态学操作，有改进的空间，可以调这部分

    cvtColor(src,output,COLOR_BGR2GRAY);
    blur(output,output,Size(3,3));

    Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3));
    Mat kernel_large = getStructuringElement(MORPH_RECT,Size(9,9));

    GammaTransform(output,output);
    erode(output,output,kernel);
    //erode(dst,dst,kernel);
    //erode(dst,dst,kernel);
    dilate(output,output,kernel_large);
    //morphologyEx(dst,dst,MORPH_CLOSE,kernel);
    threshold(output,output,80,255,THRESH_BINARY);
}