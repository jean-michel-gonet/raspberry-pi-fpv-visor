#include "image-capture-service-from-camera.hpp"
#include "event-bus-service.hpp"

ImageCaptureServiceFromCamera::ImageCaptureServiceFromCamera():
mustStop(false),
separatedThread(nullptr),
configurationMutex(),
videoCapture(0) {
}

void ImageCaptureServiceFromCamera::start() {
	if (!separatedThread) {
		mustStop = false;
		separatedThread = new std::thread([this] { doCapture(); });
	}
}

void ImageCaptureServiceFromCamera::stop() {
	mustStop = true;
	if (separatedThread) {
		separatedThread->join();
	}
}

void ImageCaptureServiceFromCamera::requestSize(int width, int height) {
	std::lock_guard<std::mutex> lock(configurationMutex);
	videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT,height);
	videoCapture.set(CV_CAP_PROP_FRAME_WIDTH,width);
}

cv::Mat ImageCaptureServiceFromCamera::getLastImage() {
	return mat;
}

void ImageCaptureServiceFromCamera::doCapture() {
	while(!mustStop) {
		{
			std::lock_guard<std::mutex> lock(configurationMutex);
			for(int n = 0; n < 2; n++) {
				videoCapture.grab();
			}
			videoCapture.grab();
			videoCapture.read(mat);
		}
		eventBus.propagate(ImageCapturedEvent(mat));
	}
}
