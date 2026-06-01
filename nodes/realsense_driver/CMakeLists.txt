cmake_minimum_required(VERSION 3.14)
project(RealSenseDriverNode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

add_executable(realsense_driver 
    main.cpp 
    realsense_driver.cpp
)

target_include_directories(realsense_driver PRIVATE ${REALSENSE2_INCLUDE_DIRS})

target_link_libraries(realsense_driver 
    PRIVATE 
        ${REALSENSE2_LIBRARIES}
        msg_headers
)

target_compile_options(realsense_driver PRIVATE ${REALSENSE2_CFLAGS_OTHER})