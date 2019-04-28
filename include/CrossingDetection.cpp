//
// Created by brendacg616 on 27/04/19.
//

#include "CrossingDetection.h"
#include <opencv2/opencv.hpp>


CrossingDetection::CrossingDetection()
{
    cv::namedWindow("Crossing Detection");
}

CrossingDetection::~CrossingDetection()
{
    cv::destroyWindow("Crossing Detection");
}


cv::Mat CrossingDetection::detection(cv::Mat image)
{
    start_time = cv::getTickCount();
    cv::Mat transposed_image;
    int image_height;
    int image_width;

    int row_index, current_column, peak_location;
    std::vector<int> image_column, local_maxima_found;
    std::vector<cv::Point>  line_points;
    cv::Point found_point;
    cv::Vec4f line_polynom;
    float calculated_angle;

    // Image allocator and shape extraction
    image_height = image.size().height;
    image_width = image.size().width;

    // Image filtering
    medianBlur(image, image, FILTER_KERNEL_SIZE);

    // Transposed image
    transposed_image = image.t();

    // Line detection algorithm
    // Set initial conditions
    row_index = 0;
    current_column = image_width * IMAGE_PERCENTAGE_START;

    // Image scanning by columns
    while (current_column < (image_width * IMAGE_PERCENTAGE_END))
    {
        // Prepare image column vector to scan
        image_column =
                (std::vector<int>) transposed_image.row(current_column).colRange(0, image_height);
        // Search for local maxima
        local_maxima_found =
                LocMax_pw(image_column, MIN_PEAK_HEIGHT, MAX_PEAK_HEIGHT, MIN_PEAK_WIDTH, MAX_PEAK_WIDTH);
        // Local maxima validation (if found)
        if (!(local_maxima_found.empty()))
        {
            // Get location of the last local maxima
            peak_location = local_maxima_found.back();
            // Set the found point
            found_point =
                    cv::Point(current_column, peak_location);
            // Point found validation through distance
            if (abs(row_index - peak_location) < MAX_DIST_ALLOWED)
            {
                // Add found point to line
                line_points.push_back(found_point);
                // Adjust row index accordingly to the found point and
                // a search range value.
                row_index = peak_location;
            }

            // Set the row index to he local minima found
            // (even if it does not belong to the line)
            if (line_points.size() < MIN_LINE_POINTS)
            {
                row_index = peak_location;
            }

        }

        current_column += COLUMN_STEP;

    }

    // Verify the line points size
    if (line_points.size() > LINE_POINTS_REQUIRED)
    {
        // Linear regression from the line points
        cv::fitLine(line_points, line_polynom,
                    CV_DIST_L1, 0, 0.01, 0.01);

        // Get the line angle form the line polynom
        calculated_angle =
                ToDegrees(
                        atan(line_polynom[1]/line_polynom[0]));

        // Validation of the line by the angle
        if ((calculated_angle > -15.0) && (calculated_angle < 15.0))
        {
            // Set the line attributes
            line_angle = calculated_angle;
            dist_to_line =
                    (image_height - line_polynom[3]) / PIXEL_CM_RATIO_Y;
        }
        else
        {
            dist_to_line = NO_LINE_DIST;
        }
    }
    else
    {
        dist_to_line = NO_LINE_DIST;
    }

    // Get elapsed time
    end_time = cv::getTickCount();
    elapsed_time = (end_time - start_time) / cv::getTickFrequency();

    // Print debug information

    // Print line points
    if (!(line_points.empty()))
    {
        // Draw initial point
        cv::circle(image, cv::Point(line_points.front()),
                   3, 255, -1);

        // Draw the line points rest found
        for (std::vector<cv::Point>::iterator point =
                line_points.begin() ;
             point != line_points.end(); ++point)
            cv::circle(image, *point, 1, 255, -1);
    }

    // Print the line polynom paramtrization
    if (dist_to_line != NO_LINE_DIST)
    {
        cv::line(
                image,
                cv::Point(line_polynom[2], line_polynom[3]),
                cv::Point(line_polynom[2] + line_polynom[0]*50, line_polynom[3] + line_polynom[1]*50),
                0);
        cv::circle(
                image,
                cv::Point(line_polynom[2], line_polynom[3]),
                1,0,-1);
    }

    // Print debug info
    cv::imshow("Crossing Detection", image);
    cv::waitKey(30);
    return image;
}
