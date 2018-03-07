//
//  viseur.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 19/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "auto-viseur.hpp"

#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
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
}

AutoViseur::~AutoViseur() {
}

void AutoViseur::on_size_allocate (Gtk::Allocation& allocation) {
	// Call the parent to do whatever needs to be done:
	DrawingArea::on_size_allocate(allocation);
	
	// Prepare a Pixbuf with the allocated size:
	a_width = allocation.get_width();
	a_height = allocation.get_height();

	pixbufMat = PixbufMat::PixbufMat(a_width, a_height);
}


void MatToCairo(cv::Mat &MC3,cairo_surface_t *surface)
{
	cv::Mat MC4 = cv::Mat(cairo_image_surface_get_width(surface),
						  cairo_image_surface_get_height(surface),
						  CV_8UC3,
						  cairo_image_surface_get_data(surface),
						  cairo_image_surface_get_stride(surface));
	
	std::vector<cv::Mat> Imgs1;
	std::vector<cv::Mat> Imgs2;
	cv::split(MC4,Imgs1);
	cv::split(MC3,Imgs2);
	for(int i=0;i<3;i++)
	{
		Imgs1[i]=Imgs2[i];
	}
	// Alpha - прозрачность
	Imgs1[3]=255;
	cv::merge(Imgs1,MC4);
}

bool AutoViseur::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

	// Capture from webcam:
	cv::Mat webcam;
	videoCapture.read(webcam);

	// Creates a Mat with same pixels source:
	cv::Mat mat = cv::Mat(a_width,
						  a_height,
						  CV_8UC3);

	// Prepare a Pixbuf with the allocated size:
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data((guint8*)mat.data,
															   Gdk::COLORSPACE_RGB,false,8,mat.cols,mat.rows,mat.step);
	
	cv::resize(webcam, mat, mat.size(), 0, 0, cv::INTER_LINEAR);

	Gdk::Cairo::set_source_pixbuf(cr,
                                  pixbuf,
                                  0,
                                  0);
    cr->paint();
    
    return true;
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

void AutoViseur::capture() {
    cv::Mat webcam;

	// Capture from webcam:
    videoCapture.read(webcam);
	
	// Prepare a Pixbuf with the allocated size:
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create(Gdk::Colorspace::COLORSPACE_RGB,
								 false,
								 8,
								 a_width,
								 a_height);
	
	// Creates a Mat with same pixels source:
	cv::Mat mat = cv::Mat(a_width,
				  a_height,
				  CV_8UC3,
				  pixbuf->get_pixels(),
				  pixbuf->get_rowstride());

	cv::resize(webcam, mat, mat.size(), 0, 0, cv::INTER_LINEAR);

	cv::Mat viseur = pixbufMat.getMat();

	cv::resize(webcam, viseur, viseur.size(), 0, 0, cv::INTER_LINEAR);
}

cv::Mat AutoViseur::resizeWithinTargetSize(const cv::Mat &input, const int targetWidth, const int targetHeight) {
	
	float scaleX = ((float) targetWidth ) / input.cols;
	float scaleY = ((float) targetHeight) / input.rows;
	float scale = scaleX > scaleY ? scaleY : scaleX;

//	printf("Mat:[ %d x %d ] - Target:[ %d x %d ] - Scale: %f", input.cols, input.rows, targetWidth, targetHeight, scale);
	
	int width = input.cols * scale;
	int height = input.rows * scale;

	cv::Mat output;
	resize(input, output, cv::Size(width, height));

	return output;
}
