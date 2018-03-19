//
//  viseur.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 19/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "auto-viseur.hpp"

#include "opencv2/highgui.hpp"

#include <ctime>
#include <glibmm/main.h>
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>

#include <iostream>
#include <stdio.h>

AutoViseur::AutoViseur():
autoViseurCapture() {
    set_size_request(INITIAL_WIDTH, INITIAL_HEIGHT);
	autoViseurCapture.setNotification(std::bind(&AutoViseur::notifyCapture, this, std::placeholders::_1));
	captureDispatcher.connect(sigc::mem_fun(*this, &AutoViseur::on_capture));
	autoViseurCapture.start();
}

AutoViseur::~AutoViseur() {
}

/**
 * Called every time the widget has its allocation changed.
 */
void AutoViseur::on_size_allocate (Gtk::Allocation& allocation) {
	// Call the parent to do whatever needs to be done:
	DrawingArea::on_size_allocate(allocation);
	
	// Configures the video port to use allocated size:
	// The viewport doesn't resize to all precise values; it
	// simplifies to the nearest power of 2.
	autoViseurCapture.setSize(allocation.get_width(), allocation.get_width());
}

void AutoViseur::notifyCapture(cv::Mat mat) {
	lastCapture = mat;
	captureDispatcher.emit();
}

/**
 * Invalidates the whole widget rectangle, to force a complete redraw.
 */
void AutoViseur::on_capture() {
	auto win = get_window();
	if (win) {
		Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                         get_allocation().get_height());
		win->invalidate_rect(r, false);
    }
}

/**
 * Called every time the widget needs to be redrawn.
 */
bool AutoViseur::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	if (!lastCapture.empty()) {
		// Initializes a pixbuf sharing the same data as the mat:
		pixbuf = Gdk::Pixbuf::create_from_data((guint8*)lastCapture.data,
											   Gdk::COLORSPACE_RGB,
											   false,
											   8,
											   lastCapture.cols,
											   lastCapture.rows,
											   lastCapture.step);
		
		// Request to copy the pixbuf over the Cairo context:
		Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
		
		// Refresh the Cairo context:
		cr->paint();
	}
	
	// Call me next time.
	return true;
}

AutoViseurCapture::AutoViseurCapture():
videoCapture(0),
configurationMutex(),
separatedThread(nullptr),
mustStop(false) {
}

// Starts capturing images from camera.
void AutoViseurCapture::start() {
	if (!separatedThread) {
		separatedThread = new std::thread([this] { doCapture(); });
	}
}

// Stops capturing images from camera.
void AutoViseurCapture::stop() {
	mustStop = true;
	if (separatedThread) {
		separatedThread->join();
	}
}

// Configures the camera's capturing size
// Depending on hardware, all sizes are not available.
void AutoViseurCapture::setSize(int width, int height) {
	videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT,height);
	videoCapture.set(CV_CAP_PROP_FRAME_WIDTH,width);
}

// Sets the method to receice notifications
// each time a new image is captured and ready.
void AutoViseurCapture::setNotification(std::function<void (cv::Mat)> n) {
	notifyCapture = n;
}


void AutoViseurCapture::doCapture() {
	while(!mustStop) {
		for(int n = 0; n < 3; n++) {
			videoCapture.grab();
		}
		videoCapture.grab();
		videoCapture.read(mat);
		notifyCapture(mat);
	}
}
