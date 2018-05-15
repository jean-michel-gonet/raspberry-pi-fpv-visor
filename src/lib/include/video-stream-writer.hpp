#ifndef video_stream_writer_hpp
#define video_stream_writer_hpp

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

/** @brief Describes an interface to create a video stream image per image.
 */
class VideoStreamWriter {
public:
	/** @brief Default destructor.
	 */
	virtual ~VideoStreamWriter() = default;

	/** @brief Opens the stream.
	 * Call this method first.
	 * @param image The first image of the video, to extract the size
	 *        and color.
	 * @param fps The frame rate.
	 */
	virtual void openStream(Mat image, double fps = 25.0) = 0;
	
	/** @brief Append the image to the stream.
	 * Append as much images as required.
	 */
	virtual void addImage(Mat image) = 0;
	
	/** @brief Close the stream.
	 * Call this method when all images have been added.
	 */
	virtual void closeStream() = 0;
};

#endif
