#ifndef video_stream_writer_hpp
#define video_stream_writer_hpp

#include <opencv2/highgui.hpp>

/** @brief Describes an interface to create a video stream image per image.
 */
class VideoStreamWriter {
public:
	/** @brief Default destructor.
	 */
	virtual ~VideoStreamWriter() = default;

	/** @brief Opens the stream.
	 * Call this method first.
	 */
	virtual void openStream() = 0;
	
	/** @brief Append the image to the stream.
	 * Append as much images as required.
	 */
	virtual void addImage(cv::Mat image) = 0;
	
	/** @brief Close the stream.
	 * Call this method when all images have been added.
	 */
	virtual void closeStream() = 0;
}

#endif
