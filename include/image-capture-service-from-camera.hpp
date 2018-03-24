#ifndef image_capture_service_from_camera_hpp
#define image_capture_service_from_camera_hpp

#include <thread>
#include <mutex>

#include "image-capture-service.hpp"

class ImageCaptureServiceFromCamera : public ImageCaptureService {
public:
	ImageCaptureServiceFromCamera();
	virtual ~ImageCaptureServiceFromCamera() = default;
	virtual void start() override;
	virtual void stop() override ;
	virtual void requestSize(int width, int height) override;
	virtual cv::Mat getLastImage() override;
	virtual void setNotificationCallback(std::function<void ()> n) override;
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
