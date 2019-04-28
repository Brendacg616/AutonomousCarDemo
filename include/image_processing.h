//
// Created by brendacg616 on 27/04/19.
//
#pragma once
#ifndef AUTOMODELCAR_IMAGE_PROCESSING_H
#define AUTOMODELCAR_IMAGE_PROCESSING_H
#include <opencv2/opencv.hpp>
#define P1  45
#define P2  50
#define P3  45
#define P4  50
#define PIXEL_CM_RATIO_X    3
#define P1XEL_CM_RATIO_Y    8
#define SCALE_X 0.4
#define SCALE_Y 1.2

class ImageProcessing
{
    int p1, p2, p3, p4;
    int pixel_cm_ratio_x, pixel_cm_ratio_y;
    float scale_x, scale_y;

public:

    ImageProcessing();
    ~ImageProcessing();

    cv::Mat process(cv::Mat);
};


#endif //AUTOMODELCAR_IMAGE_PROCESSING_H
