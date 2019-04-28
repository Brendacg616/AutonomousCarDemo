#pragma once

#include <string>
#include <gflags/gflags.h>
#include <iostream>

/*Definition of messages that will be displayed by showUsage() function*/
static const char project_message[] = "Automodelcar Demo: this project shows the image processing of a RGB video file to get Lane and Crossing lines of a road";
static const char help_message[] = "Print a usage message.";
static const char video_message[] = "Required. Path to a video file.";
/* Parameter definition and its default values*/
DEFINE_string(i, "", video_message);
DEFINE_bool(h, false, help_message);

static void showUsage() {
    /*Prints parameters usage*/
    std::cout << std::endl;
    std::cout << project_message << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "    -h                         " << help_message << std::endl;
    std::cout << "    -i \"<path>\"                " << video_message << std::endl;
}

bool ParseAndCheckCommandLine(int argc, char *argv[]) {
    /*Parsing and validation of input args*/
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