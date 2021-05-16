#include "../serial/v8sydint.h"
#include <thread>
#include <iostream>
#include <rmserial.h>
using namespace std;
using namespace serial;
// receive data

std::mutex receive_mtx;
McuConfig receive_config_data;
std::string uart_port = "/dev/ttyUSB0";


RmSerial::~RmSerial() { stop_thread(); }

bool RmSerial::send_data(uint8_t* data, size_t size) {
    return active_port->write(data, size) == size;
}

bool RmSerial::send_data(const SendData& data) {
    return send_data((uint8_t*)(&data), sizeof(SendData));
}

void proccess_data(uint8_t* s, uint8_t* e) {        //参数：头指针，尾指针
    if (e - s != sizeof(McuData)) {
        return;
    }
    McuData mcu_data;
    memcpy(&mcu_data, s, sizeof(McuData));
    if (mcu_data.start_flag != 's') {
        cout<<"Not Started with 's' "<<endl;
        return;
    }
    receive_mtx.lock();
#define BARRICADE_AUTO_RUN 1
#define BIG_RESOURCE_ISLAND_AUTO_RUN 2
#define SMALL_RESOURCE_ISLAND_AUTO_RUN 3
#define Engineer_TYPE 4

    receive_config_data.state = mcu_data.state;
    receive_config_data.start = mcu_data.start;
    receive_config_data.barrier_ok = mcu_data.barrier_ok;
    receive_config_data.wrong_data = mcu_data.wrong_data;

    receive_mtx.unlock();
}

void recieve_data(RmSerial* rm_serial) {
    static uint8_t buff[100];
    uint8_t* buffer_tail = buff;
    serial::Serial* port = rm_serial->active_port;
    while (rm_serial->thread_running) {
        size_t wait_in_buffer = port->available();
        if (wait_in_buffer) {
            port->read(buffer_tail, wait_in_buffer);
            buffer_tail += wait_in_buffer;
            if (buffer_tail[-1] == 'e') {
                *buffer_tail = 0;
                proccess_data(buff, buffer_tail);
                buffer_tail = buff;
            }
        }
    }
}

//
void RmSerial::start_thread() {
    if (init_success) {
        thread_running = true;
        std::thread task(recieve_data, this);
        task.detach();
    }
}

void RmSerial::stop_thread() {
    if (init_success) {
        thread_running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


bool RmSerial::init() {
    active_port = new Serial(uart_port, 115200,
                                     serial::Timeout::simpleTimeout(1000));
    init_success = true;
    //初始化数据

    //开启数据接受线程
    start_thread();
    if (active_port->isOpen()) {
        cout << "Successfully initialized port " << uart_port;
        return true;
    } else {
        cout << "failed to initialize port " <<uart_port;
        return false;
    }
}
