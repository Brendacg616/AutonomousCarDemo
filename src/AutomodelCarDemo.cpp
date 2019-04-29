//  AutomodelCar Demo
//  This project shows the image processing implemented to detect the Lane and Crossing Lines of a road
//  It is a demo based on the ROS project AutomodelCar: https://github.com/Conilo/automodelcar-cic-ipn.git
//  The algorithm design was developed by César Gerardo Bravo Conejo
//  The original C++ ROS nodes were coded by Esteban Iván Rojas Hernandéz and Brenda Camacho García


#include <opencv2/opencv.hpp>
#include <AutomodelCarDemo.hpp>
#include <iostream>
#include <chrono>
#include <image_processing.h>
#include <CrossingDetection.h>
#include <LaneDetection.h>

#define OPENCV_WINDOW "Display Window"


int main(int argc, char *argv[]) {
    try {
        /** Parameter Validation and initializations*/
        // Parsing and validation of input args
        if (!ParseAndCheckCommandLine(argc, argv)) {
            return 0;
        }

        // Read input
        std::cout<< "Reading input" << std::endl;
        cv::VideoCapture cap;
        //
        ImageProcessing ip;
        CrossingDetection cd;
        LaneDetection ld;
        //Open camera or video file (-i parameter)
        const bool isCamera = FLAGS_i == "cam";
        if (!(isCamera ? cap.open(0) : cap.open(FLAGS_i))) {
            throw std::logic_error("Cannot open input file or camera: " + FLAGS_i);
        }
        // Read and save input (video) frame
        cv::Mat frame;
        if (!cap.read(frame)) {
            throw std::logic_error("Failed to get frame from cv::VideoCapture");
        }
        cv::namedWindow(OPENCV_WINDOW); //OpenCV Window for image display
        /** Main Loop*/
        while (true) {
            //Displaying video frame on OpenCV window
            cv::imshow(OPENCV_WINDOW, frame);
            cv::waitKey(30);
            ////Start image processing
            cv::Mat processedImage = ip.process(frame);
            ////Start Crossing Line Detection
            cv::Mat crossingDetectionImage = cd.crossing_detection(processedImage);
            ////Start Lane Line Detection
            cv::Mat laneDetectionImage = ld.lane_detection(processedImage);
            //Requesting new frame if any
            cap.grab();
            cv::Mat newFrame;
            if (!cap.retrieve(newFrame)) { // if it is video's EOF breaks the loop
                break;
            }else {
                frame = newFrame;
            }

        }
    }
    catch (const std::exception& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cout << "Unknown/internal exception happened." << std::endl;
        return 1;
    }

}
