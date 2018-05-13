#include "image-capture-service.hpp"

ImageCapturedEvent::ImageCapturedEvent(cv::Mat i) {
	capturedImage = i;
}

cv::Mat ImageCapturedEvent::getCapturedImage() {
	return capturedImage;
}
