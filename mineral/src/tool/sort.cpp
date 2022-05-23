#include <mineral.h>
/*
 * 函数说明：
 * 1、功能说明：对传入的容器进行排序和剔除重复元素，参数为1升序，参数为-1降序
 * 2、参数说明：vector<cv::Point> &all_fit_points 需要进行排序+剔除重复元素的容器
 *            int flag                          参数为1升序，参数为-1降序
 * 3、版本：V2.0 （效率最大化）
 */
void Mineral::sortPointsVector(vector<cv::Point> &all_fit_points,int flag){
    if(flag==1) {
        sort(all_fit_points.begin(), all_fit_points.end(), [](cv::Point &a, cv::Point &b) {
            return a.x < b.x;
        });
    }
    else if(flag ==-1){
        sort(all_fit_points.begin(), all_fit_points.end(), [](cv::Point &a, cv::Point &b) {
            return a.x > b.x;
        });
    }

    vector<cv::Point>::iterator new_end;
    new_end = unique(all_fit_points.begin(),all_fit_points.end());
    all_fit_points.erase(new_end,all_fit_points.end());
}