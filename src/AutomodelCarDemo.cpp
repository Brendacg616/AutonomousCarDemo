#include <opencv2/opencv.hpp>
#include <AutomodelCarDemo.hpp>
#include <iostream>
#include <chrono>
#include <image_processing.h>
#define OPENCV_WINDOW "Display Window"

bool ParseAndCheckCommandLine(int argc, char *argv[]) {
    // ---------------------------Parsing and validation of input args--------------------------------------
    gflags::ParseCommandLineNonHelpFlags(&argc, &argv, true);
    if (FLAGS_h) {
        showUsage();
        return false;
    }
    std::cout << "Parsing input parameters" << std::endl;

    if (FLAGS_i.empty()) {
        throw std::logic_error("Parameter -i is not set");
    }

    return true;
}
int main(int argc, char *argv[]) {
    try {
        // ---------------------------Parsing and validation of input args--------------------------------------
        if (!ParseAndCheckCommandLine(argc, argv)) {
            return 0;
        }

        // -----------------------------Read input -----------------------------------------------------
        std::cout<< "Reading input" << std::endl;
        cv::VideoCapture cap;

        ImageProcessing ip;
        const bool isCamera = FLAGS_i == "cam";
        if (!(FLAGS_i == "cam" ? cap.open(0) : cap.open(FLAGS_i))) {
            throw std::logic_error("Cannot open input file or camera: " + FLAGS_i);
        }
        const size_t width  = (size_t) cap.get(CV_CAP_PROP_FRAME_WIDTH);
        const size_t height = (size_t) cap.get(CV_CAP_PROP_FRAME_HEIGHT);


        // read input (video) frame
        cv::Mat frame;
        if (!cap.read(frame)) {
            throw std::logic_error("Failed to get frame from cv::VideoCapture");
        }
        std::cout<<"Width: "<< frame.size().width<<std::endl;
        std::cout<<"Height: "<< frame.size().height<<std::endl;
        typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;
        auto wallclock = std::chrono::high_resolution_clock::now();
        cv::namedWindow(OPENCV_WINDOW);
        while (true) {
            /** requesting new frame if any*/
            cap.grab();
            cv::imshow(OPENCV_WINDOW, frame);
            cv::waitKey(30);
            std::cout<<"Displaying Image"<<std::endl;

            ip.process(frame);
            std::cout<<"Image Displayed"<<std::endl;

            // end of file, for single frame file, like image we just keep it displayed to let user check what was shown
            cv::Mat newFrame;
            if (!cap.retrieve(newFrame)) {
                break;
            }else {
            }
            frame = newFrame;  // shallow copy
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
