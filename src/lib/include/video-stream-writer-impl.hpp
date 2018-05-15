#ifndef video_stream_writer_impl_hpp
#define video_stream_writer_impl_hpp


#include <opencv2/videoio.hpp>

#include "video-stream-writer.hpp"


using namespace cv;
using namespace std;

/**
 * Implementation of the interface.
 */
class VideoStreamWriterImpl : public VideoStreamWriter {
public:
	VideoStreamWriterImpl();
	virtual ~VideoStreamWriterImpl() = default;
	virtual void openStream(Mat image, double fps = 25.0) override;
	virtual void addImage(Mat image) override;
	virtual void closeStream() override;
	virtual string getFileName();
private:
	VideoWriter videoWriter;
	static const string fileName;
};

#endif
