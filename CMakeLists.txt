#
#cmake_minimum_required(VERSION 3.7)
#project(ToStation)
#
#set(CMAKE_CXX_STANDARD 14)
#add_compile_options(-O3)
#set(SOURCE_FILES main.cpp headers/parameter.h  mineral/src/detect_mineral.cpp headers/options.h
#        com/src/datatypes.cpp com/src/rmserial.cpp com/src/serial.cpp com/include/serial/impl/unix.h com/include/serial/impl/win.h com/src/impl/unix.cpp com/src/impl/list_ports/list_ports_linux.cpp
#        com/include/serial/serial.h com/include/serial/v8sydint.h mineral/include/mineral.h mineral/src/detect_line.cpp mineral/src/select_ROI.cpp mineral/src/init/init_mineral.cpp rmconfig/rmconfig.h
#        mineral/src/run.cpp mineral/src/send/send_target.cpp flash/include/flash.h flash/src/detect/detect_flash.cpp flash/run.cpp flash/src/init/init_flash.cpp flash/src/init/init_flash.cpp tools/sort/sort_points_vector.cpp
#        mineral/src/get/get_fit_points.cpp)
#
#add_executable(ToStation ${SOURCE_FILES})
#
#find_package(OpenCV 4 REQUIRED)
#
#target_link_libraries(ToStation ${OpenCV_LIBS} -lpthread)
#
#
#
#
#
#
#

cmake_minimum_required(VERSION 3.7)
project(ToStation)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-O3)
set(SOURCE_FILES main.cpp headers/parameter.h  headers/options.h
        com/src/datatypes.cpp com/src/rmserial.cpp com/src/serial.cpp com/include/serial/impl/unix.h com/include/serial/impl/win.h com/src/impl/unix.cpp com/src/impl/list_ports/list_ports_linux.cpp
        com/include/serial/serial.h com/include/serial/v8sydint.h mineral/include/mineral.h mineral/src/detect_line.cpp mineral/src/select_ROI.cpp mineral/src/init/init_mineral.cpp rmconfig/rmconfig.h
        mineral/src/send/send_target.cpp flash/include/flash.h flash/src/detect/detect_flash.cpp flash/run.cpp flash/src/init/init_flash.cpp flash/src/init/init_flash.cpp tools/sort/sort_points_vector.cpp
        mineral/src/get/get_fit_points.cpp mineral/run.cpp mineral/src/detect/detect_mineral.cpp)

add_executable(ToStation ${SOURCE_FILES})
include_directories(${PROJECT_SOURCE_DIR}/flash/include)
include_directories(${PROJECT_SOURCE_DIR}/mineral/include)
include_directories(${PROJECT_SOURCE_DIR}/com/include)
include_directories(${PROJECT_SOURCE_DIR}/com/include/serial)
include_directories(${PROJECT_SOURCE_DIR}/headers)
include_directories(${PROJECT_SOURCE_DIR}/rmconfig)
find_package(OpenCV 4 REQUIRED)

link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(ToStation ${OpenCV_LIBS} -lpthread)







