cmake_minimum_required(VERSION 3.14)
project(EmbeddedMessages LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(FLATBUFFERS_FLATC_EXECUTABLE flatc REQUIRED)

set(FBS_SCHEMAS
    # colored_point_cloud.fbs
    # depth_frame.fbs
    # imu_frame.fbs
    # latency_stats.fbs
    # lidar_scan.fbs
    rgb_frame.fbs
)

set(GENERATED_HEADERS "")
foreach(SCHEMA ${FBS_SCHEMAS})
    get_filename_component(SCHEMA_NAME ${SCHEMA} NAME_WE)
    
    set(OUTPUT_HEADER "${CMAKE_CURRENT_BINARY_DIR}/${SCHEMA_NAME}_generated.h")
    list(APPEND GENERATED_HEADERS ${OUTPUT_HEADER})

    add_custom_command(
        OUTPUT ${OUTPUT_HEADER}
        COMMAND ${FLATBUFFERS_FLATC_EXECUTABLE} --cpp -o "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/${SCHEMA}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${SCHEMA}"
        COMMENT "Compiling FlatBuffer schema: ${SCHEMA}"
    )
endforeach()

add_custom_target(generate_fbs_headers DEPENDS ${GENERATED_HEADERS})

add_library(msg_headers INTERFACE)
add_dependencies(msg_headers generate_fbs_headers)

target_include_directories(msg_headers INTERFACE ${CMAKE_CURRENT_BINARY_DIR})