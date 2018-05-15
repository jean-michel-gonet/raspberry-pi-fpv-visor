//
//  viseur.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 19/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "auto-viseur.hpp"
#include "service-locator.hpp"



AutoViseur::AutoViseur():
makingVideoStream(false),
fontDescription(),
videoStreamWriter(nullptr),
imageCaptureService(ServiceLocator::newImageCaptureService()),
carService(ServiceLocator::newCarService()) {
	fontDescription.set_family("Monospace");
	fontDescription.set_weight(Pango::WEIGHT_BOLD);
	fontDescription.set_size(10 * Pango::SCALE);
	
    set_size_request(INITIAL_WIDTH, INITIAL_HEIGHT);

	imageCapturedBus.subscribe(this);
	makeVideoStreamBus.subscribe(this);
	
	captureDispatcher.connect(sigc::mem_fun(*this, &AutoViseur::on_capture));
	imageCaptureService->start();
}

AutoViseur::~AutoViseur() {
	imageCapturedBus.unsubscribe(this);
	makeVideoStreamBus.unsubscribe(this);
	imageCaptureService->stop();
}

/**
 * Called every time the widget has its allocation changed.
 */
void AutoViseur::on_size_allocate (Gtk::Allocation& allocation) {
	// Call the parent to do whatever needs to be done:
	DrawingArea::on_size_allocate(allocation);

	// Remembers the new allocated size for future operations.
	width = allocation.get_width();
	height = allocation.get_height();

	// Configures the video port to use allocated size:
	// The viewport doesn't resize to all precise values; it
	// simplifies to the nearest power of 2.
	imageCaptureService->requestSize(width, height);
}
/**
 * Switches on/off the making of video stream with captured images.
 */
void AutoViseur::receive(MakeVideoStreamEvent event) {
	if (event.getDoIt()) {
		makingVideoStream = true;
	} else {
		makingVideoStream = false;
	}
}

void AutoViseur::receive(ImageCapturedEvent imageCapturedEvent) {
	lastCapture = imageCapturedEvent.getCapturedImage();
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

		// If requested, saves the image to a video stream:
		if (makingVideoStream) {
			if (videoStreamWriter == nullptr) {
				videoStreamWriter = ServiceLocator::newVideoStreamWriter();
				videoStreamWriter->openStream(lastCapture);
			} else {
				videoStreamWriter->addImage(lastCapture);
			}
		}
		
		// Resizes the captured image to the allocation:
		cv::Mat mat;
		resize(lastCapture,
			   mat,
			   cv::Size(width, height),
			   cv::INTER_AREA);
		
		// Initializes a pixbuf sharing the same data as the mat:
		pixbuf = Gdk::Pixbuf::create_from_data((guint8*)mat.data,
											   Gdk::COLORSPACE_RGB,
											   false,
											   8,
											   mat.cols,
											   mat.rows,
											   (int) mat.step);
		
		// Request to copy the pixbuf over the Cairo context:
		Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
		cr->paint();
		
		// Display some text:
		CarStatus carStatus = carService->getLastStatus();
		cr->set_source_rgb(1.0, 1.0, 1.0);
		char buffer[50];

		sprintf(buffer, "%.1f km/h", carStatus.currentSpeed);
		displayTextTopLeft(cr, buffer);

		sprintf(buffer, "%.1f V", carStatus.accumulatorCharge);
		displayTextBottomLeft(cr, buffer);

		sprintf(buffer, "PWM %.1f V", carStatus.pwm);
		displayTextTopRight(cr, buffer);
		
		displayCross(cr, carStatus.positionSteering, carStatus.positionAccelerator);
		
		if (makingVideoStream) {
			cr->set_source_rgb(1.0, 0.1, 0.1);
			displayRec(cr);
		}
	}
	
	// Call me next time.
	return true;
}

void AutoViseur::displayRec(const Cairo::RefPtr<Cairo::Context>& cr) {
	double radius = 7;
	double x = width / 2;
	double y = height - radius;
	cr->arc(x, y, radius, 0, 2 * M_PI);
	cr->fill();
}

void AutoViseur::displayCross(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y) {
	double rectangleWidth = 40;
	double rectangleHeight = 40;
	double rectangleX = width - rectangleWidth;
	double rectangleY = height - rectangleHeight;
	
	cr->set_line_width(1.0);
	cr->rectangle(rectangleX, rectangleY, rectangleWidth, rectangleHeight);
	cr->stroke();
	
	double positionX = rectangleX + rectangleWidth * x / 255;
	double positionY = rectangleY + rectangleHeight * y / 255;

	cr->move_to(positionX, rectangleY);
	cr->line_to(positionX, height);
	
	cr->move_to(rectangleX, positionY);
	cr->line_to(width, positionY);
	cr->stroke();
}

void AutoViseur::displayTextTopLeft(const Cairo::RefPtr<Cairo::Context>& cr, char *text) {
	auto layout = create_pango_layout(text);
	layout->set_font_description(fontDescription);
	cr->move_to(0, 20);
	layout->show_in_cairo_context(cr);
}

void AutoViseur::displayTextBottomLeft(const Cairo::RefPtr<Cairo::Context>& cr, char *text) {
	auto layout = create_pango_layout(text);
	layout->set_font_description(fontDescription);
	
	int textWidth, textHeight;
	layout->get_pixel_size(textWidth, textHeight);

	cr->move_to(0, height - textHeight);
	layout->show_in_cairo_context(cr);
}

void AutoViseur::displayTextTopRight(const Cairo::RefPtr<Cairo::Context>& cr, char *text) {
	auto layout = create_pango_layout(text);
	layout->set_font_description(fontDescription);

	int textWidth, textHeight;
	layout->get_pixel_size(textWidth, textHeight);
	
	cr->move_to(width - textWidth, 20);
	layout->show_in_cairo_context(cr);
}
