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
				REQUIRE( pedestrianDetector.getPedestrianPosition() == -0.29);
				REQUIRE( pedestrianDetector.getPedestrianSize() == 0.39);
			}
		}
		
		WHEN( "Shown with two pedestrians" ) {
			string oneSinglePedestrian = string(pathToPedestrianFolder);
			oneSinglePedestrian.append("/two-pedestrians.jpg");

			mat = imread(oneSinglePedestrian, CV_LOAD_IMAGE_COLOR);
			pedestrianDetector.processImage(mat);
			
			THEN( "Position and size of the largest is found" ) {
				REQUIRE( pedestrianDetector.getPedestrianPosition() == -0.38);
				REQUIRE( pedestrianDetector.getPedestrianSize() == 0.47);
			}
		}
		
		WHEN( "Shown with no pedestrians" ) {
			string oneSinglePedestrian = string(pathToPedestrianFolder);
			oneSinglePedestrian.append("/no-pedestrians.jpg");
			
			mat = imread(oneSinglePedestrian, CV_LOAD_IMAGE_COLOR);
			pedestrianDetector.processImage(mat);
			
			THEN( "Size of the pedestrian is 0" ) {
				REQUIRE( pedestrianDetector.getPedestrianSize() == 0);
			}
		}
	}
}
