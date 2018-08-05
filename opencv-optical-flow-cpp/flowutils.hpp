//
//  flowutils.hpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-07-25.
//  Copyright © 2018 Robert. All rights reserved.
//

#ifndef flowutils_hpp
#define flowutils_hpp

#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "config.hpp"

class FlowUtils {
public:
    static int saveFile(cv::Mat &mat, Config config);
    static std::string timePointAsString(const std::chrono::system_clock::time_point& tp);
};


#endif /* flowutils_hpp */
