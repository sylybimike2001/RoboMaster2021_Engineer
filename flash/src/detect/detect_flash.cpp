//用于识别远处的频闪灯光
//工程车低速或静止时适用
//思路1：先检测挂在高处的矿石块，在其上方小区域内搜索目标
//思路2：两帧相减，通过比例识别，大能量机关的转动会干扰
#include "flash.h"
#include "parameter.h"
#include <vector>
using namespace std;
void Flash::detectFlash(cv::Mat &operand) {

    VideoCapture cap1("/home/ayb/CLionProjects/Engineer/0B1EF747FBFC236580288881B08CA01E.mp4");

    Mat first_flash_frame,second_flash_frame,frame;
    Mat first_shade = Mat::zeros(first_flash_frame.size(),CV_8UC3);
    Mat second_shade,shade;

    while(!AboutToRelease){
        if(first_flash_frame.empty()){
            cap1.read(first_flash_frame);

        }
        cap1.read(second_flash_frame);
        resize(first_flash_frame,first_flash_frame,Size(640,640));
        resize(second_flash_frame,second_flash_frame,Size(640,640));

        Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5));
        frame = second_flash_frame;

        GaussianBlur(first_flash_frame,first_flash_frame,Size(15,15),3,3);
        GaussianBlur(second_flash_frame,second_flash_frame,Size(15,15),3,3);

        imshow("st",first_flash_frame);
        waitKey(1);
        imshow("second",second_flash_frame);
        waitKey(1);

        if(first_shade.empty()){
            absdiff(first_flash_frame,second_flash_frame,first_shade);

        }

        absdiff(first_flash_frame,second_flash_frame,second_shade);
        absdiff(first_shade,second_shade,shade);



        //处理和检测
        cvtColor(shade,shade,COLOR_BGR2GRAY);

        dilate(shade,shade,kernel);
        erode(shade,shade,kernel);
        dilate(shade,shade,kernel);dilate(shade,shade,kernel);
        imshow("shade",shade);
        waitKey(0);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
//
        //Canny(shade,shade,30,30);
        findContours(shade,contours,hierarchy,RETR_LIST,CHAIN_APPROX_SIMPLE,Point(0,0));
        cout<<contours.size()<<endl;
        bool scale_fit,area_fit;

        for(int index=0;index<contours.size();index++){
            Mat back = Mat::ones(first_flash_frame.size(),CV_8UC3);
            Rect operand = boundingRect(contours[index]);
            scale_fit = float(operand.width)/operand.height<flash_threshold_scale_high&&
                        (float)operand.width/operand.height>flash_threshold_scale_low;
            area_fit = arcLength(contours[index],false)>flash_threshold_area_low&&
                       arcLength(contours[index],false)<flash_threshold_area_high;

            if(1) rectangle(back,operand, Scalar(0, 255, 0), 3);
            imshow("result of detection",back);
            waitKey(0);

        }

        frame.copyTo(first_flash_frame);
        second_shade.copyTo(first_shade);
    }
}


/*
 * cap1.read(first_flash_frame);


        cap1.read(second_flash_frame);


        //shade = first_flash_frame-second_flash_frame;   //将前后读取的两帧作差

        absdiff(first_flash_frame,second_flash_frame,shade);
        imshow("shade",shade);
        waitKey(10);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        cvtColor(shade,shade,COLOR_BGR2GRAY);
        Canny(shade,shade,30,30);
        findContours(shade,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(0,0));
        cout<<contours.size()<<endl;
        if(contours.size()==0) continue;
        for(int i=0;i<contours.size();i++) {
            //DEBUG
            Mat back = Mat::zeros(shade.size(),CV_8UC3);

            //用于处理大风车转动的干扰，还未完善

            //矩形拟合，通过长宽比例筛选，参数要调
            Rect fit = boundingRect(contours[i]);
            bool scale_fit = float(fit.width)/fit.height<flash_threshold_high&&
                    (float)fit.width/fit.height>flash_threshold_low;

            if(1) {
                Rects_flash.push_back(fit);
                //DEBUG
                rectangle(back, fit, Scalar(255, 0, 0), 1);
                imshow("back",back);
                waitKey(10);
            }
        }
        if (Rects_flash.size()!=0) {
            AboutToRealse=true;
            cout<<"ready"<<endl;
            Rects_flash.clear();
        }
 */