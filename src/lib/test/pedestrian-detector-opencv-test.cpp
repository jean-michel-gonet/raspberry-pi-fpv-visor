#include <cstring>

#include "catch.hpp"
#include "pedestrian-detector-opencv.hpp"
#include "test-config.h"

using namespace std;
using namespace cv;

SCENARIO("Can detect pedestrians in an image") {
	Mat mat;
	string pathToPedestrianFolder = PATH_TO_TEST_DATA;
	pathToPedestrianFolder.append("/pedestrians");
	
	GIVEN( "An initialized pedestrian detector") {
		PedestrianDetectorOpenCv pedestrianDetector;

		WHEN( "Shown with one pedestrian") {
			string oneSinglePedestrian = string(pathToPedestrianFolder);
			oneSinglePedestrian.append("/one-single-pedestrian.png");
			
			mat = imread(oneSinglePedestrian, CV_LOAD_IMAGE_COLOR);
			pedestrianDetector.processImage(mat);
			
			THEN ( "Then its position and size is found ") {
				REQUIRE( pedestrianDetector.getPedestrianPosition() == 0.1 );
				REQUIRE( pedestrianDetector.getPedestrianDistance() == 0.1 );
			}
		}
		
	}
}
