//
//  flow.hpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-07-25.
//  Copyright © 2018 Robert. All rights reserved.
//

#ifndef flow_hpp
#define flow_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "config.hpp"

class Flow {
    static cv::Mat generateOutput(std::vector<cv::Point> points);
public:
    static cv::Mat denseFlow(std::string videoFile, Config config);
    static cv::Mat sparseFlow(std::string videoFile, Config config);
};

#endif /* flow_hpp */
