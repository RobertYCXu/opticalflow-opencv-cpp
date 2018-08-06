//
//  constants.hpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-07-26.
//  Copyright © 2018 Robert. All rights reserved.
//

#ifndef constants_hpp
#define constants_hpp

#include <stdio.h>
#include <string>

namespace NumConst {
    const int OUTPUT_DIM = 15000;
    const int FPS_240 = 240;
    const int FPS_60 = 60;
    const int RES_480 = 480;
    const int RES_640 = 640;
}

namespace StringConst {
    const std::string VIDEO_INPUT_DIR = "video_input_directory/";
    const std::string OUTPUT_DIR = ".../flowimages/";
    const std::string VERY_FAST = "vfast";
    const std::string FAST = "fast";
    const std::string MEDIUM = "med";
    const std::string SLOW = "slow";
    const std::string DENSE = "farneback";
    const std::string SPARSE = "lucas-kanade";
    const std::string VID_EXT = ".mp4";
}

#endif /* constants_hpp */
