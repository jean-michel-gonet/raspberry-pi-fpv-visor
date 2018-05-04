//
//  pedestrian-detector.cpp
//  fpv
//
//  Created by Jean-Michel Gonet on 03/05/18.
//
//

#include "pedestrian-detector-opencv.hpp"

PedestrianDetectorOpenCv::PedestrianDetectorOpenCv() {
	// Nothing to do.
}

void PedestrianDetectorOpenCv::processImage(cv::Mat image) {
	// Nothing to do (yet).
}

double PedestrianDetectorOpenCv::getPedestrianPosition() {
	return pedestrianPosition;
}

double PedestrianDetectorOpenCv::getPedestrianDistance() {
	return pedestrianDistance;
}
