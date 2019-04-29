cmake_minimum_required(VERSION 2.8)
project(AutomodelCar)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(include)

add_library(ImageProcessing SHARED
        include/image_processing.cpp
        include/image_processing.h
        )

add_library(LocalMaximaDetection SHARED
        include/LocalMaximaDetection.h
        include/LocalMaximaDetection.cpp)

add_library(CrossingDetection SHARED
        include/CrossingDetection.cpp
        include/CrossingDetection.h)

add_library(LaneDetection SHARED
        include/LaneDetection.cpp
        include/LaneDetection.h)

find_package(OpenCV 3.4.2 REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OPENCV is enabled")
    message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
    message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
else()
    message(STATUS "OPENCV is disabled or not found, " ${TARGET_NAME} " skiped")
    return()
endif()
find_package(gflags REQUIRED)

add_executable(AutomodelCar
        src/AutomodelCarDemo.cpp
        src/AutomodelCarDemo.hpp )
target_link_libraries(AutomodelCar ${gflags_LIBRARIES} ${OpenCV_LIBS} ImageProcessing CrossingDetection LocalMaximaDetection LaneDetection)
