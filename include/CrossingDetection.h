//
// Created by brendacg616 on 27/04/19.
//
#pragma once

#ifndef AUTOMODELCAR_CROSSINGDETECTION_H
#define AUTOMODELCAR_CROSSINGDETECTION_H
#include <LocalMaximaDetection.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <numeric>

short int PIXEL_CM_RATIO_Y = 2;

/* Global constants initialization */
short int const NO_LINE_DIST = -1;
short int const FILTER_KERNEL_SIZE = 5;
short int const COLUMN_STEP = 2;
float const IMAGE_PERCENTAGE_START = 0.33;
float const IMAGE_PERCENTAGE_END = 0.7;
short int const MIN_PEAK_HEIGHT = 50;
short int const MAX_PEAK_HEIGHT = 150;
short int const MIN_PEAK_WIDTH = 9;
short int const MAX_PEAK_WIDTH = 15;
short int const SEARCH_RANGE = 15;
short int const LINE_POINTS_REQUIRED = 15;
short int const MIN_LINE_POINTS = 3;
short int const MAX_DIST_ALLOWED = 7;

/* Global variables initialization */
short int dist_to_line = NO_LINE_DIST;
float line_angle = 0.0;
int start_time, end_time;
float elapsed_time;

/*
 * Transforms radians to degrees function
 */
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

    cv::Mat detection(cv::Mat);

};

#endif //AUTOMODELCAR_CROSSINGDETECTION_H
