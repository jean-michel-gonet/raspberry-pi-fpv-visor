//
//  pedestrian-detector.hpp
//  fpv
//
//  Created by Jean-Michel Gonet on 03/05/18.
//
//

#ifndef pedestrian_detector_h
#define pedestrian_detector_h

#include <opencv2/highgui.hpp>

class PedestrianDetector {
public:
	virtual ~PedestrianDetector() = default;
	virtual void processImage(cv::Mat image) = 0;
	virtual double getPedestrianPosition() = 0;
	virtual double getPedestrianDistance() = 0;
};


#endif
