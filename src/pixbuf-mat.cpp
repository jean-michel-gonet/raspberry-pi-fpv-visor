//
//  pixbuf-mat.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 06/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "pixbuf-mat.hpp"

PixbufMat::PixbufMat() {
	// Nothing to do.
}

PixbufMat::PixbufMat(int width, int height) {
	// Prepare a Pixbuf with the allocated size:
	pixbuf = Gdk::Pixbuf::create(Gdk::Colorspace::COLORSPACE_RGB,
		   false,
		   8,
		   width,
		   height);
	
	// Creates a Mat with same pixels source:
	mat = cv::Mat(width,
				  height,
				  CV_8UC3,
				  pixbuf->get_pixels(),
				  pixbuf->get_rowstride());
}

cv::Mat PixbufMat::getMat() {
	return mat;
}

Glib::RefPtr<Gdk::Pixbuf> PixbufMat::getPixbuf() {
	return pixbuf;
}


