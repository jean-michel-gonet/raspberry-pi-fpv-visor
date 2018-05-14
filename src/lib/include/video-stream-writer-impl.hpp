#ifndef video_stream_writer_impl_hpp
#define video_stream_writer_impl_hpp

#include "video-stream-writer.hpp"

/**
 * Implementation of the interface.
 */
public VideoStreamWriterImpl : public VideoStreamWriter {
public:
	virtual VideoStreamWriterImpl();
	virtual ~VideoStreamWriterImpl() = default;
	virtual void openStream() override;
	virtual void addImage(cv::Mat image) override;
	virtual void closeStream() override;
}

#endif