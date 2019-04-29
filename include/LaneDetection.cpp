//
// Adaptation from LaneDetection ROS node originally coded by Esteban Rojas Hernández
//  Perfoms a row based search of the lane line points.
//
//  The steps to perform the Lane Line Detection are the following:
//  1. Fill the black space in both sides of the image with gray points
//  2. Get Lane line points of both right and left sides of the image (continuous and dashed lines of the road respectively)
//  3. Calculate linear regression of both lines points
//  4. Display and return the image


#include <LaneDetection.h>
#include <opencv2/opencv.hpp>
#include <iostream>
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
////  1. Fill the black space in both sides of the image with gray points
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
////  2. Get Lane line points of both right and left sides of the image (continuous and dashed lines of the road respectively)
    // Line detection algorithm, get line points from right and left road lines.
    LineDetection(
            image,
            image_height,
            image_width,
            lane_centers,
            right_line_points,
            left_line_points);

    // Linear regression calculation from the points found
    line_found = false;
    right_line_found = false;
    left_line_found = false;
////  3. Calculate linear regression of both lines points
    //Linear regression for right points
    if (right_line_points.size() > MIN_RIGHT_LINE_POINTS)
    {
        cv::fitLine(
                right_line_points, line,
                CV_DIST_L2, 0, 0.01 ,0.01);
        line_found = true;
        right_line_found = true;
    }
    //Linear regression for right points
    else if (left_line_points.size() > MIN_LEFT_LINE_POINTS)
    {
        cv::fitLine(
                left_line_points, line,
                CV_DIST_L2, 0, 0.01, 0.01);
        line_found = true;
        left_line_found = true;
    }

////  4. Display and return the image

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
