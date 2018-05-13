#ifndef image_capture_service_hpp
#define image_capture_service_hpp

#include <opencv2/highgui.hpp>

/** @brief Event when a new image is captured.
 * Gives access to the captured image.
 */
class ImageCapturedEvent {
public:
	ImageCapturedEvent(cv::Mat i);
	cv::Mat getCapturedImage();
private:
	cv::Mat capturedImage;
};

/** Interface of an Image capture service.
 * Real implementation can retrieve images from a camera or
 * a video file.
 * Should propagate {@link ImageCapturedEvent} each time an image is captured.
 */
class ImageCaptureService {
public:
	virtual ~ImageCaptureService() = default;
	
	/** Start capturing.*/
	virtual void start() = 0;
	
	/** Stop capturing.*/
	virtual void stop() = 0;
	
	/** Requests a size.
	 * Not all implementation will honor the requested size.
	 * For example, if images are captured from a video file,
	 * they won't be resized.
	 */
	virtual void requestSize(int width, int height) = 0;
	
	/** To retrieve the last captured image.
	 * Call this method after being notified.
	 * @return The last captured image.
	 */
	virtual cv::Mat getLastImage() = 0;
};

#endif
