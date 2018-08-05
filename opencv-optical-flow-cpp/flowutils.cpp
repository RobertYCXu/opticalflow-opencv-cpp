//
//  flowutils.cpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-07-25.
//  Copyright © 2018 Robert. All rights reserved.
//

#include <string>
#include "flowutils.hpp"
#include "constants.hpp"
#include "config.hpp"

using namespace std;

int FlowUtils::saveFile(cv::Mat &mat, Config config) {
    string curTime = timePointAsString(chrono::system_clock::now());
    try {
        string res = config.resize ? to_string(config.width) + "x" + to_string(config.height) : "original";
        string outputFile =
            StringConst::OUTPUT_DIR +
            config.algorithm + "/" +
            to_string(config.fps) + "/" +
            res + "-" +
            config.speed + "-" + 
            curTime +
            ".png";

        imwrite(outputFile, mat);
    }
    catch (runtime_error& ex) {
        cerr << "Exception converting image to PNG format: " << ex.what() << endl;
        return 1;
    }
    cout << "Saved PNG file" << endl;
    return 0;
}

string FlowUtils::timePointAsString(const chrono::system_clock::time_point& tp) {
    time_t t = chrono::system_clock::to_time_t(tp);
    string ts = ctime(&t);
    ts.resize(ts.size()-1);
    replace(ts.begin(), ts.end(), ' ', '-');
    return ts;
}
