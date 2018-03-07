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

	// Creates a Mat with the requested size:
	mat = cv::Mat(height, width, CV_8UC3);
	
	// Prepare a Pixbuf with the same size:
	pixbuf = Gdk::Pixbuf::create_from_data((guint8*)mat.data,
										   Gdk::COLORSPACE_RGB,
										   false,
										   8,
										   mat.cols,
										   mat.rows,
										   mat.step);
}

cv::Mat PixbufMat::getMat() {
	return mat;
}

Glib::RefPtr<Gdk::Pixbuf> PixbufMat::getPixbuf() {
	return pixbuf;
}


