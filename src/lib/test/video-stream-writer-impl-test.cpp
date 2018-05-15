#include "video-stream-writer-impl.hpp"
#include "catch.hpp"
#include "test-config.h"


using namespace std;
using namespace cv;

SCENARIO("Can make a video stream") {
	Mat mat;
	string pathToImagesFolder = PATH_TO_TEST_DATA;
	pathToImagesFolder.append("/3-images");
	
	GIVEN( "An initialized video stream writer") {
		VideoStreamWriterImpl videoStreamWriter;
		
		WHEN( "Fed with some images") {

			mat = imread(string(pathToImagesFolder).append("/abc-a.png"), CV_LOAD_IMAGE_COLOR);
			Size size = mat.size();
			videoStreamWriter.openStream(mat);
			mat = imread(string(pathToImagesFolder).append("/abc-b.png"), CV_LOAD_IMAGE_COLOR);
			videoStreamWriter.addImage(mat);
			mat = imread(string(pathToImagesFolder).append("/abc-c.png"), CV_LOAD_IMAGE_COLOR);
			videoStreamWriter.addImage(mat);
			
			videoStreamWriter.closeStream();
			
			THEN ( "Can make a readable video with all of them") {
				VideoCapture videoCapture(videoStreamWriter.getFileName());

				REQUIRE(videoCapture.read(mat) == true);
				REQUIRE(mat.size() == size);
				REQUIRE(videoCapture.read(mat) == true);
				REQUIRE(mat.size() == size);
				REQUIRE(videoCapture.read(mat) == true);
				REQUIRE(mat.size() == size);

				REQUIRE(videoCapture.read(mat) == false);

				videoCapture.release();
			}
		}
	}
}
