cmake_minimum_required(VERSION 3.7)
project(ToStation)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-O3)
set(SOURCE_FILES main.cpp rmconfig/parameter.h
        com/src/datatypes.cpp com/src/rmserial.cpp com/src/serial.cpp com/include/serial/impl/unix.h com/include/serial/impl/win.h com/src/impl/unix.cpp com/src/impl/list_ports/list_ports_linux.cpp
        com/include/serial/serial.h com/include/serial/v8sydint.h mineral/include/mineral.h  mineral/src/init/init_mineral.cpp rmconfig/rmconfig.h
        mineral/src/send/send_target.cpp flash/include/flash.h flash/src/detect/detect_flash.cpp flash/run.cpp flash/src/init/init_flash.cpp flash/src/init/init_flash.cpp
        mineral/src/get/get_fit_points.cpp mineral/run.cpp mineral/src/detect/detect_mineral.cpp mineral/src/tool/sort.cpp mineral/src/get/get_send_data.cpp rmconfig/parameter.h
        barrier/include/barrier.h barrier/src/detect/detect_single.cpp barrier/src/detect/detect_double.cpp barrier/src/init/init_barrier.cpp barrier/src/run.cpp barrier/src/get/get_fit_points.cpp
        rmconfig/uvc_v4l2.h barrier/uvc_v4l2.cpp mineral/src/detect/detect_mineral_high.cpp mineral/src/mor/mor_of_mineral_high.cpp)

add_executable(ToStation ${SOURCE_FILES})
include_directories(${PROJECT_SOURCE_DIR}/flash/include)
include_directories(${PROJECT_SOURCE_DIR}/mineral/include)
include_directories(${PROJECT_SOURCE_DIR}/com/include)
include_directories(${PROJECT_SOURCE_DIR}/com/include/serial)
include_directories(${PROJECT_SOURCE_DIR}/rmconfig)
include_directories(${PROJECT_SOURCE_DIR}/barrier/include)
#include_directories(${PROJECT_SOURCE_DIR}/barrier/include)
find_package(OpenCV 4 REQUIRED)

link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(ToStation ${OpenCV_LIBS} -lpthread)







