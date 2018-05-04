//
//  pedestrian-detector-opencv.hpp
//  fpv
//
//  Created by Jean-Michel Gonet on 03/05/18.
//
//

#ifndef pedestrian_detector_opencv_h
#define pedestrian_detector_opencv_h

#include "pedestrian-detector.hpp"

class PedestrianDetectorOpenCv : public PedestrianDetector {
public:
	PedestrianDetectorOpenCv();
	virtual ~PedestrianDetectorOpenCv() = default;
	
	virtual void processImage(cv::Mat image) override;
	virtual double getPedestrianPosition() override;
	virtual double getPedestrianDistance() override;
	
private:
	double pedestrianPosition;
	double pedestrianDistance;
};

#endif
