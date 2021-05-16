#include <mineral.h>
/*
 * 函数说明
 * 功能：与电控通信，收发数据，定位高处即将掉落的矿石
 */
void Mineral::locateMineralHigh() {
    sendTarget();
}