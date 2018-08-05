//
//  config.hpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-08-04.
//  Copyright © 2018 Robert. All rights reserved.
//

#ifndef config_hpp
#define config_hpp

#include <stdio.h>
#include <string>
#include "constants.hpp"

struct Config {
    bool resize;
    std::string speed;
    int fps;
    std::string algorithm;
    int width;
    int height;
};

#endif /* config_hpp */
