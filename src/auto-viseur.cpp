//
//  viseur.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 19/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "auto-viseur.hpp"
#include "service-locator.hpp"

AutoViseur::AutoViseur():
imageCaptureService(ServiceLocator::newImageCaptureService()) {
    set_size_request(INITIAL_WIDTH, INITIAL_HEIGHT);
	imageCaptureService->setNotificationCallback(std::bind(&AutoViseur::notifyCapture, this));
	captureDispatcher.connect(sigc::mem_fun(*this, &AutoViseur::on_capture));
	imageCaptureService->start();
}

AutoViseur::~AutoViseur() {
	imageCaptureService->stop();
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
	imageCaptureService->requestSize(allocation.get_width(), allocation.get_width());
}

void AutoViseur::notifyCapture() {
	lastCapture = imageCaptureService->getLastImage();
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

