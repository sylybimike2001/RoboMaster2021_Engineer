#include <mineral.h>
#include <parameter.h>
#include <vector>
using namespace std;
void Mineral::Detect_line(Mat &operand,VideoCapture &capture){
    Max_y = 0;
    Min_y = 0;
    //操作对象，不会改变operand
    Mat dst(operand.size(),CV_8UC3);

#ifdef DEBUG
    imshow("current image",operand);
    waitKey(1);
    Mat BackGround = Mat::zeros(operand.size(),CV_8UC3);
#endif

    //在HSV空间下分离颜色
    cvtColor(operand,dst,COLOR_RGB2HSV);
    inRange(dst,Line_finder_low,Line_finder_high,dst);
    imshow("after HSV",dst);
    waitKey(1);
    //形态学操作
    Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3));
    GaussianBlur(dst,dst,Size(3,3),3,3);
    erode(dst,dst,kernel);
    erode(dst,dst,kernel);
    erode(dst,dst,kernel);
#ifdef __DEBUG__WRITER
    //imshow("line detect after Mor",dst);
#endif
    //寻找边缘
    vector<vector<Point>> Contours;
    vector<Vec4i> hierarchy;
    Canny(dst,dst,50,70);
    findContours(dst,Contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(0,0));


    for(int i=0;i<Contours.size();i++)
        if (arcLength(Contours[i],false)>line_threshold_length){                    //长度筛选直线

#ifdef DEBUG
            drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
            //遍历所有点，找出y坐标差值的最大值
            sort(Contours[i].begin(),Contours[i].end(),[](Point A,Point B){
                return A.y<B.y;
            });
            Max_y=Contours[i].end()->y;
            Min_y=Contours[i].begin()->y;
#ifdef DEBUG
            cout<<"Max: y"<<Max_y<<endl;
            cout<<"Min: y"<<Min_y<<endl;
//            for(int j=0;j<Contours[i].size();j++){
//                std::cout<<Contours[i][j].y<<std::endl;
//            }
#endif
//            for(int j =0;j<Contours[i].size();j++){
//                if (Contours[i][j].y>Max_y) {Max_y = Contours[i][j].y;Min_y = Contours[i][j].y;}
//                if (Contours[i][j].y<Min_y) Min_y = Contours[i][j].y;
//            }


            //通过限制y方向差值判定直线水平
            //70是阈值 在parameter中约束
            //找到直线说明可以框选感兴趣的ROI区域
            if (abs(Max_y-Min_y)<slope_threshold) {
                isHorizontal = true;
            }
            else {                              //if line is not horizontal , search in the whole image
                Max_y = operand.size().height;
                isHorizontal = false;
            }
        }

    //DEBUG
    cout<<"FindLine:"<<ROI_possible<<endl;
    cout<<"Horizontal:"<<isHorizontal<<endl;
#ifdef DEBUG
    imshow("result",BackGround);
    waitKey(1);
#endif
}
