//
// Created by brendacg616 on 27/04/19.
//

#include "LaneDetection.h"
//Version  13/12/17
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <ros/console.h>
#include <iostream>
#include "std_msgs/Int16.h"
#include "cic/Lane.h"
#include <LocalMaximaDetection.cpp>
#include "LaneDetection.h"
#include <math.h>

LaneDetection::LaneDetection()
{

    cv::namedWindow(LANE_DETECTION_WINDOW);
}

LaneDetection::~LaneDetection()
{
    cv::destroyWindow(LANE_DETECTION_WINDOW);

}

cv::Mat LaneDetection::lane_detection(cv::Mat image)
{

    start_time = cv::getTickCount();

    int image_height;
    int image_width;
    std::vector<cv::Point> lane_centers;
    std::vector<cv::Point> left_line_points;
    std::vector<cv::Point> right_line_points;
    bool line_found;
    bool right_line_found;
    bool left_line_found;
    cv::Vec4f line;

    // Image allocator and shape extraction
    image_height = image.size().height;
    image_width = image.size().width;

    // Color transform used to fill black corners
    for (int i = image_height * IMAGE_PERCENTAGE; i < image_height; i++)
    {
        for (int j = 0; j < image_width; j++)
        {
            if (image.at<uchar>(i,j) < GRAY_THRESHOLD)
            {
                image.at<uchar>(i,j) = rand()%6 + 87;
            }
        }
    }

    // Image filtering
    medianBlur(image, image, FILTER_KERNEL_SIZE);

    // Line detection algorithm
    LineDetection(
            image,
            image_height,
            image_width,
            lane_centers,
            right_line_points,
            left_line_points);

    // Curvature degree calculation
    line_found = false;
    right_line_found = false;
    left_line_found = false;
    if (right_line_points.size() > MIN_RIGHT_LINE_POINTS)
    {
        cv::fitLine(
                right_line_points, line,
                CV_DIST_L2, 0, 0.01 ,0.01);
        line_found = true;
        right_line_found = true;
    }
    else if (left_line_points.size() > MIN_LEFT_LINE_POINTS)
    {
        cv::fitLine(
                left_line_points, line,
                CV_DIST_L2, 0, 0.01, 0.01);
        line_found = true;
        left_line_found = true;
    }

    if (line_found == true) {
        center_deviation = int(image_width / 2) - lane_centers[1].x;
        int p1 = line[2];
        int p2 = line[3];
        int p3 = (line[2] + 1) + 100 * line[0];
        int p4 = (line[3] + 1) + 100 * line[1];

        if (left_line_found == true) {
            p3 = left_line_points.back().x;
            p4 = left_line_points.back().y;
        } else if (right_line_found == true) {
            p3 = right_line_points.back().x;
            p4 = right_line_points.back().y;
        }

        float m1 = p4 - p2;
        float m2 = p3 - p1;
        float m = (m2 / m1);

        curvature_degree = SERVO_CENTER + int(atan(m) * (180.0 / M_PI));


        // Draw cord line
        cv::line(image, cv::Point(p1, p2), cv::Point(p3, p4), 100, 3);
        cv::circle(image, cv::Point(p1, p2), 3, 200, -1);
        cv::circle(image, cv::Point(p3, p4), 3, 200, -1);
    }

    // Set last values
    last_center_deviation = center_deviation;

    // Get elapsed time
    end_time = cv::getTickCount();
    elapsed_time = (end_time - start_time)/cv::getTickFrequency();


    cv::imshow(LANE_DETECTION_WINDOW, image);
    cv::waitKey(30);
    return image;


}
