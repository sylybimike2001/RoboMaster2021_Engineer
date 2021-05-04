#include <flash.h>
#include <rmconfig.h>
bool Flash::initFlash() {
    Rects_flash.clear();
    cutecap = VideoCapture(capture_index);

    rmSerial.init();

    keepRunning = true;
    AboutToRelease = false;
}