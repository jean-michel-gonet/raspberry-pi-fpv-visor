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

AutoViseur::AutoViseur(): videoCapture(0) {
    set_size_request(INITIAL_WIDTH, INITIAL_HEIGHT);
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &AutoViseur::on_timeout), 100);
	videoCapture.set(CV_CAP_PROP_BUFFERSIZE, 3);
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
	videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT,allocation.get_height());
	videoCapture.set(CV_CAP_PROP_FRAME_WIDTH,allocation.get_width());
}

/**
 * Invalidates the whole widget rectangle, to force a complete redraw.
 */
bool AutoViseur::on_timeout() {
	auto win = get_window();
	if (win) {
		Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                         get_allocation().get_height());
		win->invalidate_rect(r, false);
    }
	return true;
}

/**
 * Called every time the widget needs to be redrawn.
 */
bool AutoViseur::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	
	// Reads an image from video capture:
	videoCapture.read(mat);

	// Initializes a pixbuf sharing the same data as the mat:
	pixbuf = Gdk::Pixbuf::create_from_data((guint8*)mat.data,
										   Gdk::COLORSPACE_RGB,
										   false,
										   8,
										   mat.cols,
										   mat.rows,
										   mat.step);

	// Request to copy the pixbuf over the Cairo context:
	Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
	
	// Refresh the Cairo context:
	cr->paint();
	
	// Call me next time.
	return true;
}
