//
//  Adaptation from ImageProcessing ROS node originally coded by Brenda Camacho García
//
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


cv::Mat CrossingDetection::crossing_detection(cv::Mat image)
{
    cd_start_time = cv::getTickCount();
    cv::Mat transposed_image;
    int image_height;
    int image_width;

    int row_index, current_column, peak_location;
    std::vector<int> image_column, local_maxima_found;
    std::vector<cv::Point>  line_points;
    cv::Point found_point;
    cv::Vec4f regression_line;
    float calculated_angle;

    // Image shape extraction
    image_height = image.size().height;
    image_width = image.size().width;

    // Image filtering
    medianBlur(image, image, CD_FILTER_KERNEL_SIZE);

    // Transposed image
    transposed_image = image.t();

    // Line detection algorithm
    // Set initial conditions
    row_index = 0;
    current_column = image_width * CD_IMAGE_PERCENTAGE_START;

    // Image scanning by columns
    while (current_column < (image_width * CD_IMAGE_PERCENTAGE_END))
    {
        // Prepare image column vector to scan
        image_column =
                (std::vector<int>) transposed_image.row(current_column).colRange(0, image_height);
        // Search for local maxima
        local_maxima_found =
                LocMax_pw(image_column, CD_MIN_PEAK_HEIGHT, CD_MAX_PEAK_HEIGHT, CD_MIN_PEAK_WIDTH, CD_MAX_PEAK_WIDTH);
        // Local maxima validation (if found)
        if (!(local_maxima_found.empty()))
        {
            // Get location of the last local maxima
            peak_location = local_maxima_found.back();
            // Set the found point
            found_point =
                    cv::Point(current_column, peak_location);
            // Point found validation through distance
            if (abs(row_index - peak_location) < CD_MAX_DIST_ALLOWED)
            {
                // Add found point to line
                line_points.push_back(found_point);
                // Adjust row index accordingly to the found point and
                // a search range value.
                row_index = peak_location;
            }

            // Set the row index to he local minima found
            // (even if it does not belong to the line)
            if (line_points.size() < CD_MIN_LINE_POINTS)
            {
                row_index = peak_location;
            }

        }

        current_column += CD_COLUMN_STEP;

    }

    // Verify the line points size
    if (line_points.size() > CD_LINE_POINTS_REQUIRED)
    {
        // Linear regression from the line points
        cv::fitLine(line_points, regression_line,
                    CV_DIST_L1, 0, 0.01, 0.01);

        // Get the line angle form the line polynom
        calculated_angle =
                ToDegrees(
                        atan(regression_line[1]/regression_line[0]));

        // Validation of the line by the angle
        if ((calculated_angle > -15.0) && (calculated_angle < 15.0))
        {
            // Set the line attributes
            line_angle = calculated_angle;
            dist_to_line =
                    (image_height - regression_line[3]) / PIXEL_CM_RATIO_Y;
        }
        else
        {
            dist_to_line = CD_NO_LINE_DIST;
        }
    }
    else
    {
        dist_to_line = CD_NO_LINE_DIST;
    }

    // Get elapsed time
    cd_end_time = cv::getTickCount();
    cd_elapsed_time = (cd_end_time - cd_start_time) / cv::getTickFrequency();


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

    // Draw linear regression line
    if (dist_to_line != CD_NO_LINE_DIST)
    {
        cv::line(
                image,
                cv::Point(regression_line[2], regression_line[3]),
                cv::Point(regression_line[2] + regression_line[0]*50, regression_line[3] + regression_line[1]*50),
                0);
        cv::circle(
                image,
                cv::Point(regression_line[2], regression_line[3]),
                1,0,-1);
    }

    // Print debug info
    cv::imshow("Crossing Detection", image);
    cv::waitKey(30);
    return image;
}
