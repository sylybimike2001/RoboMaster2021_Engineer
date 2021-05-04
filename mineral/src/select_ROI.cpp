#include <mineral.h>
#include <parameter.h>

void Mineral::Select_ROI(Mat &operand) {
    if(isHorizontal) {
        ROI = Rect(Point(0, 0), Point(operand.size().width, Max_y));
        ROI_possible = true;

#ifdef DEBUG
        Mat show = Mat::zeros(operand.size(), CV_8UC1);
        rectangle(show, ROI, Scalar(100, 100, 0), 2);
        imshow("ROI", show);
        waitKey(1);
#endif
    }
    else ROI_possible= false;
}

