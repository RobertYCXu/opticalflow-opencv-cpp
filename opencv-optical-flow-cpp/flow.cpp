//
//  flow.cpp
//  opencv-optical-flow-cpp
//
//  Created by robert on 2018-07-25.
//  Copyright © 2018 Robert. All rights reserved.
//

#include "flow.hpp"
#include "constants.hpp"
#include "config.hpp"

using namespace std;
using namespace cv;

Mat Flow::denseFlow(std::string videoFile, Config config) {
    Mat flow, frame;
    UMat flowUmat, prevGray;
    Mat output;
    VideoCapture cap(videoFile);
    int numFrames = 0;
    vector<Point> points;
    while (true) {
        bool grabbed = cap.grab();
        
        if (!grabbed) {
            cerr << "Frame grab failed" << endl;
            break;
        }
        
        Mat img;
        Mat original;
        cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
        if (config.resize) resize(img, img, Size(config.width, config.height));
        img.copyTo(original);
        cvtColor(img, img, COLOR_BGR2GRAY);
        if (!prevGray.empty()) {
            calcOpticalFlowFarneback(prevGray, img, flowUmat, 0.4, 1, 12, 2, 8, 1.2, 0);
            flowUmat.copyTo(flow);
            float avgX = 0;
            float avgY = 0;
            int numPoints = 0;
            for (int y = 0; y < original.rows; y += 200) {
                for (int x = 0; x < original.cols; x += 200) {
                    const Point2f flowatxy = flow.at<Point2f>(y, x) * 100;
                    avgY -= flowatxy.y;
                    avgX -= flowatxy.x;
                    numPoints++;
                }
            }
            avgX /= numPoints;
            avgY /= numPoints;
            
            if (points.empty()) {
                points.emplace_back(Point(cvRound(avgX), cvRound(avgY)));
            }
            else {
                points.emplace_back(Point(cvRound(avgX + points[points.size() - 1].x), cvRound(avgY + points[points.size() - 1].y)));
            }
        }
        img.copyTo(prevGray);
        numFrames++;

    }
    return generateOutput(points);
}

Mat Flow::generateOutput(vector<Point> points) {
    Mat output;
    output = Mat::zeros(Size(NumConst::OUTPUT_DIM, NumConst::OUTPUT_DIM), CV_8UC1);
    if (!points.empty()) {
        int p1 = 0;
        int p2 = 1;
        
        while (p2 != points.size()) {

            line(output, Point(points.at(p1).x + 5000, points.at(p1).y + 5000), Point(points.at(p2).x + 5000, points.at(p2).y + 5000), Scalar(255), 1, 8, 0);
            p1++;
            p2++;
        }
    }
    return output;
}

Mat Flow::sparseFlow(std::string videoFile, Config config) {
    Mat flow, frame;
    UMat prevGray;
    Mat output;
    VideoCapture cap(videoFile);
    int numFrames = 0;
    vector<Point> points;
    vector<Point2f> prevFeatures, nextFeatures;
    vector<uchar> status;
    vector<float> err;
    
    
    while (true) {
        bool grabbed = cap.grab();
        
        if (!grabbed) {
            cerr << "Frame grab failed" << endl;
            break;
        }
        
        Mat img;
        cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
        if (config.resize) resize(img, img, Size(config.width, config.height));
        cvtColor(img, img, COLOR_BGR2GRAY);
        double xAvg1 = 0;
        double xAvg2 = 0;
        double yAvg1 = 0;
        double yAvg2 = 0;
        
        if (!prevGray.empty()) {
            if (prevFeatures.size() == 0) {
                int rowStep = 20;
                int colStep = 5;
                int nRows = img.rows / rowStep;
                int nCols = img.cols / colStep;
                for (int i = 0; i <= nRows; i += rowStep) {
                    for (int j = 0; j <= nCols; j += colStep) {
                        prevFeatures.emplace_back(Point(j * colStep, i * rowStep));
                    }
                }
            }
            calcOpticalFlowPyrLK(prevGray, img, prevFeatures, nextFeatures, status, err);
            for (Point2f &p : prevFeatures) {
                xAvg1 += p.x;
                yAvg1 += p.y;
            }
            for (Point2f &p : nextFeatures) {
                xAvg2 += p.x;
                yAvg2 += p.y;
            }
            xAvg1 /= prevFeatures.size();
            yAvg1 /= prevFeatures.size();
            xAvg2 /= prevFeatures.size();
            yAvg2 /= prevFeatures.size();
            double pointX = xAvg1 - xAvg2;
            double pointY = yAvg1 - yAvg2;
            if (points.empty()) {
                points.emplace_back(Point{cvRound(pointX), cvRound(pointY)});
            }
            else {
                Point lastPoint = points.at(points.size() - 1);
                pointX += lastPoint.x;
                pointY += lastPoint.y;
                points.emplace_back(Point{cvRound(pointX), cvRound(pointY)});
            }
        }
        img.copyTo(prevGray);
        numFrames++;

    }
    return generateOutput(points);
}
