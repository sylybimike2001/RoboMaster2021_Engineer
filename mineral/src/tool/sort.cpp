#include <mineral.h>

void Mineral::sortPointsVector(vector<cv::Point> &all_fit_points){
    sort(all_fit_points.begin(),all_fit_points.end(),[](cv::Point &a,cv::Point &b){
        return a.x < b.x;
    });
    vector<cv::Point>::iterator new_end;
    new_end = unique(all_fit_points.begin(),all_fit_points.end());
    all_fit_points.erase(new_end,all_fit_points.end());
}