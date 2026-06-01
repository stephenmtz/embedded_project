cmake_minimum_required(VERSION 3.14)
project(EmbeddedRoboticsSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(msgs)

add_subdirectory(nodes/realsense_driver)