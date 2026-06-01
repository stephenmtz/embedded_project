cmake_minimum_required(VERSION 3.14)
project(RealSenseDriverNode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(realsense2 REQUIRED)

add_executable(realsense_driver
    main.cpp
    realsense_driver.cpp
)

target_link_libraries(realsense_driver PRIVATE
    realsense2::realsense2
    msg_headers
)