#ifndef PIXBUF_MAT_HPP
#define PIXBUF_MAT_HPP


#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

/**
 * A class to maintain a gtk's Pixbuf and a opencv's Mat in the same
 * memory space.
 */
class PixbufMat {
public:
	PixbufMat();
	PixbufMat(int width, int height);
	virtual ~PixbufMat() = default;
	cv::Mat getMat();
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf();
	
private:
	cv::Mat mat;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};

#endif
