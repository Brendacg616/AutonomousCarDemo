//
// Adaptation from ImageProcessing ROS node originally coded by Esteban Rojas Hernández and Brenda Camacho García
//  In this node it's carried out the image processing in order to get a bird-eye view, gray scaled image
//  from BGR images. The output is used by LaneDetection and CrossingDetection classes.
//
//  For the image processing, were followed this steps:
//  1. Get the region of interest of the image
//  2. Resize the image:  narrower in x, larger in y
//  3. Transform from BGR to Gray scale
//  4. Perspective transformation
//  5. Display and return processed image

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
    float scale_x, scale_y;

public:

    ImageProcessing();
    ~ImageProcessing();

    cv::Mat process(cv::Mat);
};


#endif //AUTOMODELCAR_IMAGE_PROCESSING_H
