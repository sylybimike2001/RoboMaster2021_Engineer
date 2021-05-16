#include <barrier.h>
#include <uvc_v4l2.h>
void Barrier::run(V4L2Capture &cap){
    initBarrier();
    while (1)
    {
        if (use_cam) {
            cap >> src;
            resize(src,src,Size(src.size().width/2,src.size().height/2));
            if (src.empty()) {
                break;
            }
        }
        detectBarrierSingle(src,cap);
    }
}
