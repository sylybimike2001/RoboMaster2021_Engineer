#include <mineral.h>

void Mineral::getFitPoints(std::vector<Rect> &fitRects,std::vector<Point> &fitPoints){
    for(int k=1;k<all_fit_rects.size();k++){
        Point center;
        center.x=(all_fit_rects[k].x+   all_fit_rects[k-1].x)/2+(all_fit_rects[k].width+all_fit_rects[k-1].width)/4;
        center.y = (all_fit_rects[k].y+all_fit_rects[k-1].y)/2+(all_fit_rects[k].height+all_fit_rects[k-1].height)/4;
        all_fit_points.push_back(center);
    }
}