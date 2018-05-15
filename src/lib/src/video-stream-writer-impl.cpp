#include "video-stream-writer-impl.hpp"

using namespace std;
using namespace cv;

const string VideoStreamWriterImpl::fileName = "./live.avi";

VideoStreamWriterImpl::VideoStreamWriterImpl()
:videoWriter() {
	
}
// See example: https://docs.opencv.org/3.4.1/d5/d57/videowriter_basic_8cpp-example.html
void VideoStreamWriterImpl::openStream(Mat image, double fps) {
	int fourcc = CV_FOURCC('M', 'J', 'P', 'G');
	bool isColor = (image.type() == CV_8UC3);
	videoWriter.open(fileName, fourcc, fps, image.size(), isColor);
	addImage(image);
}

void VideoStreamWriterImpl::addImage(Mat image) {
	videoWriter.write(image);
}

void VideoStreamWriterImpl::closeStream() {
	videoWriter.release();
}

string VideoStreamWriterImpl::getFileName() {
	return fileName;
}
