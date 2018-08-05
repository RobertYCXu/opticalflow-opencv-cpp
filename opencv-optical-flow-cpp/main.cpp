//
//  main.cpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-07-16.
//  Copyright © 2018 Robert. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "flowutils.hpp"
#include "flow.hpp"
#include "constants.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    //NOTE: For the farneback algorithm all images are rotated
    // iterate through all combinations of algorithm, fps, movement speed and output results in appropriate folder
    string algorithms[] = {StringConst::SPARSE, StringConst::DENSE};
    string speeds[] = {StringConst::VERY_FAST, StringConst::FAST, StringConst::MEDIUM, StringConst::SLOW};
    int fps[] = {NumConst::FPS_240, NumConst::FPS_60};
    
        for (int fps : fps) {
            for (string speed : speeds) {
                Config config {true, speed, fps, StringConst::DENSE, NumConst::RES_480, NumConst::RES_640};
                string videoFile = StringConst::VIDEO_INPUT_DIR + to_string(config.fps) + "-" + config.speed + StringConst::VID_EXT;
                cout << videoFile << endl;

                Mat result = Flow::denseFlow(videoFile, config);
                
                FlowUtils::saveFile(result, config);
                // run algorithm on original sized image (1080p)
                config.resize = false;
                result = Flow::denseFlow(videoFile, config);
                FlowUtils::saveFile(result, config);
            }
        }

    return 0;
}
