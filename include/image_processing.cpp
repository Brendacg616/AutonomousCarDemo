//
// Created by brendacg616 on 27/04/19.
//

#include <image_processing.h>
#include <opencv2/opencv.hpp>
//using namespace ImageProcessing;

ImageProcessing::ImageProcessing(){
    p1 = P1;
    p2 = P2;
    p3 = P3;
    p4 = P4;
    pixel_cm_ratio_x = PIXEL_CM_RATIO_X;
    pixel_cm_ratio_y = P1XEL_CM_RATIO_Y;
    scale_x = SCALE_X;
    scale_y = SCALE_Y;
    cv::namedWindow("ImageProcessing");
}
ImageProcessing::~ImageProcessing(){
    cv::destroyWindow("ImageProcessing");
}
cv::Mat ImageProcessing::process(cv::Mat image)
{
    int e1 = cv::getTickCount();

    // OpenCV Mat files declaration
    cv::Mat croped_image,
            scaled_image,
            gray_scale_image,
            lambda_image,
            wrapped_image;

    // 1. Region Of Interest cropping
    cv::Rect ROI(0,90,640,350);
    croped_image = image(ROI);

    // 2. Image Resizing
    cv::resize(croped_image, scaled_image,
               cv::Size(), scale_x, scale_y, CV_INTER_LINEAR);

    // 3. To gray scale color transform
    cv::cvtColor(scaled_image, gray_scale_image,
                 CV_BGR2GRAY);

    // Points used for homology
    cv::Point2f image_points[4], object_points[4];

    // Ger image size
    int image_width = gray_scale_image.size().width;
    int image_height = gray_scale_image.size().height;

    object_points[0].x = image_width/2 - p1;
    object_points[0].y = 0;
    object_points[1].x = image_width/2 + p2;
    object_points[1].y = 0;
    object_points[2].x = 0;
    object_points[2].y = image_height;
    object_points[3].x = image_width;
    object_points[3].y = image_height;

    image_points[0].x = 0;
    image_points[0].y = 0;
    image_points[1].x = image_width;
    image_points[1].y = 0;
    image_points[2].x = image_width/2 - p3;
    image_points[2].y = image_height;
    image_points[3].x = image_width/2 + p4;
    image_points[3].y = image_height;

    lambda_image =
            cv::getPerspectiveTransform(object_points, image_points);

    // Image wrapping
    cv::warpPerspective(
            gray_scale_image, wrapped_image,
            lambda_image, gray_scale_image.size());

    // Node execution time calculation and publication
    int e2 = cv::getTickCount();
    float t = (e2-e1) / cv::getTickFrequency();
    std::cout<<"  Elapsed time: " << t << std::endl;
    cv::imshow("ImageProcessing", wrapped_image);
    cv::waitKey(30);
    return wrapped_image;
}


