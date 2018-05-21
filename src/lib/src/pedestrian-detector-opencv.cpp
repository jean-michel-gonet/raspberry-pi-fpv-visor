#include "pedestrian-detector-opencv.hpp"
#include <math.h>

using namespace std;
using namespace cv;

const double PedestrianDetectorOpenCv::WEIGHT_DETECTION_THRESHOLD = 1.5;

PedestrianDetectorOpenCv::PedestrianDetectorOpenCv()
:hogDescriptor() {
	hogDescriptor.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

void PedestrianDetectorOpenCv::processImage(Mat image) {
	vector<Rect> foundLocations;
	vector<double> foundWeights;
	hogDescriptor.detectMultiScale(image, foundLocations, foundWeights);
	
	Rect pedestrianRectangle = findLargestRectangle(foundLocations, foundWeights);
	
	computePedestrianSize(image.size(), pedestrianRectangle);
	computePedestrianPosition(image.size(), pedestrianRectangle);

	// displayDebugInformation(foundLocations, foundWeights, pedestrianRectangle, image);
}

void PedestrianDetectorOpenCv::displayDebugInformation(vector<Rect> foundPedestrians, vector<double> weights, Rect largestPedestrian, Mat image) {
	
	vector<Rect>::iterator i;
	for (unsigned int i = 0; i < foundPedestrians.size(); i++) {
		if (weights[i] > WEIGHT_DETECTION_THRESHOLD) {
			Rect foundPedestrian = foundPedestrians[i];
			rectangle(image,
					  foundPedestrian.tl(),
					  foundPedestrian.br(),
					  Scalar(0, 255, 0),
					  2);
		}
	}
	rectangle(image,
			  largestPedestrian.tl(),
			  largestPedestrian.br(),
			  Scalar(0, 0, 255),
			  2);
	imshow("People detector", image);
	waitKey(0);
}

Rect PedestrianDetectorOpenCv::findLargestRectangle(vector<Rect> foundLocations, vector<double> weights) {
	
	Rect largestRectangle = Rect(0, 0, 0, 0);
	
	for (unsigned int i = 0; i < foundLocations.size(); i++) {
		if (weights[i] > WEIGHT_DETECTION_THRESHOLD) {
			Rect foundLocation = foundLocations[i];
			if (foundLocation.area() > largestRectangle.area()) {
				largestRectangle = foundLocation;
			}
		}
	}
	return largestRectangle;
}

void PedestrianDetectorOpenCv::computePedestrianPosition(Size imageSize, Rect pedestrianRectangle) {

	if (pedestrianRectangle.width == 0) {
		pedestrianPosition = 0;
	} else {
		double middle = pedestrianRectangle.x + pedestrianRectangle.width / 2;
		pedestrianPosition = -1 + 2 * middle / imageSize.width;
		pedestrianPosition = roundWithTwoDecimals(pedestrianPosition);
	}
}

void PedestrianDetectorOpenCv::computePedestrianSize(Size imageSize, Rect pedestrianRectangle) {

	if (pedestrianRectangle.width == 0) {
		pedestrianSize = 0;
	} else {
		pedestrianSize = pedestrianRectangle.height + pedestrianRectangle.width;
		pedestrianSize /= imageSize.height + imageSize.width;
		pedestrianSize = roundWithTwoDecimals(pedestrianSize);
	}
}

double PedestrianDetectorOpenCv::roundWithTwoDecimals(double value) {
	return round(value * 100) / 100;
}

double PedestrianDetectorOpenCv::getPedestrianPosition() {
	return pedestrianPosition;
}

double PedestrianDetectorOpenCv::getPedestrianSize() {
	return pedestrianSize;
}
