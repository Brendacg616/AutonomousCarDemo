//
//  Adaptation from CrossingDetection ROS node originally coded by Brenda Camacho García
//  Perfoms a column based search of the crossing line points.
//
//  The steps to perform the Crossing Line Detection are the following:
//  1. Transpose the image (It was easier to get rows than columns)
//  2. Iterate over the image "columns" from CD_IMAGE_PERCENTAGE_START to CD_IMAGE_PERCENTAGE_END
//      2.1. Get the current column
//      2.2. Find line point with LocMax_pw() function
//      2.3. Append the found points
//  3. Calculate linear regression of the line points
//  4. Get the angle and the distance from the car to the line
//  5. Display and return the image

#pragma once

#ifndef AUTOMODELCAR_CROSSINGDETECTION_H
#define AUTOMODELCAR_CROSSINGDETECTION_H
#include <LocalMaximaDetection.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <numeric>

short int PIXEL_CM_RATIO_Y = 2;

/* Global constants initialization */
short int const CD_NO_LINE_DIST = -1;
short int const CD_FILTER_KERNEL_SIZE = 5;
short int const CD_COLUMN_STEP = 2;
float const CD_IMAGE_PERCENTAGE_START = 0.33;
float const CD_IMAGE_PERCENTAGE_END = 0.7;
short int const CD_MIN_PEAK_HEIGHT = 50;
short int const CD_MAX_PEAK_HEIGHT = 150;
short int const CD_MIN_PEAK_WIDTH = 9;
short int const CD_MAX_PEAK_WIDTH = 15;
short int const CD_SEARCH_RANGE = 15;
short int const CD_LINE_POINTS_REQUIRED = 15;
short int const CD_MIN_LINE_POINTS = 3;
short int const CD_MAX_DIST_ALLOWED = 7;

//Global variables initialization
short int dist_to_line = CD_NO_LINE_DIST;
float line_angle = 0.0;
int cd_start_time, cd_end_time;
float cd_elapsed_time;

// Transforms radians to degrees function

int ToDegrees(
        float radians)
{
    return (radians*180.0) / M_PI;
}

class CrossingDetection
{
public:

    CrossingDetection();
    ~CrossingDetection();

    cv::Mat crossing_detection(cv::Mat);

};

#endif //AUTOMODELCAR_CROSSINGDETECTION_H
