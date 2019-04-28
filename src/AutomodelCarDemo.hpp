#pragma once

#include <string>
#include <vector>
#include <gflags/gflags.h>
#include <iostream>

static const char help_message[] = "Print a usage message.";

static const char video_message[] = "Optional. Path to an video or image file. Default value is \"cam\" to work with camera.";
DEFINE_string(i, "", video_message);
DEFINE_bool(h, false, help_message);
static void showUsage() {
    std::cout << std::endl;
    std::cout << "Automodelcar demo" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "    -h                         " << help_message << std::endl;
    std::cout << "    -i \"<path>\"                " << video_message << std::endl;
}
