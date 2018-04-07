#ifndef image_capture_service_hpp
#define image_capture_service_hpp

#include <opencv2/highgui.hpp>

#include "notifier.hpp"

/** Interface of an Image capture service.
 * Real implementation can retrieve images from a camera or
 * a video file.
 */
class ImageCaptureService : public Notifier {
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
