//
//  pedestrian-detector-opencv.hpp
//  fpv
//
//  Created by Jean-Michel Gonet on 03/05/18.
//
//

#ifndef pedestrian_detector_opencv_h
#define pedestrian_detector_opencv_h

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include "pedestrian-detector.hpp"

/**
 * Pedestrian detector implemented with OpenCV.
 * @author jean-michel-gonet
 */
class PedestrianDetectorOpenCv : public PedestrianDetector {
public:
	PedestrianDetectorOpenCv();
	virtual ~PedestrianDetectorOpenCv() = default;
	virtual void processImage(cv::Mat image) override;
	virtual double getPedestrianPosition() override;
	virtual double getPedestrianSize() override;
	
private:
	static const double WEIGHT_DETECTION_THRESHOLD;
	cv::HOGDescriptor hogDescriptor;
	double pedestrianPosition;
	double pedestrianSize;
	cv::Rect findLargestRectangle(std::vector<cv::Rect> rect, std::vector<double> weights);
	void computePedestrianPosition(cv::Size imageSize, cv::Rect rect);
	void computePedestrianSize(cv::Size imageSize, cv::Rect rect);
	double roundWithTwoDecimals(double value);
	void displayDebugInformation(std::vector<cv::Rect> foundPedestrians, std::vector<double> weights, cv::Rect largestPedestrian, cv::Mat image);
};

#endif
