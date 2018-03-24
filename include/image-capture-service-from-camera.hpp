#ifndef image_capture_service_from_camera_hpp
#define image_capture_service_from_camera_hpp

#include <thread>

#include "image-capture-service.hpp"

class ImageCaptureServiceFromCamera : public ImageCaptureService {
public:
	ImageCaptureServiceFromCamera();
	virtual ~ImageCaptureServiceFromCamera() = default;
	virtual void start();
	virtual void stop();
	virtual void requestSize(int width, int height);
	virtual cv::Mat getLastImage();
	virtual void setNotificationCallback(std::function<void ()> n);
private:
	bool mustStop;
	std::thread* separatedThread;
	mutable std::mutex configurationMutex;
	cv::Mat mat;
	cv::VideoCapture videoCapture;
	void doCapture();
	std::function<void ()> notifyCapture;
};


#endif
