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

AutoViseur::AutoViseur() {
    set_size_request(INITIAL_WIDTH, INITIAL_HEIGHT);
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &AutoViseur::on_timeout), 100);
}

AutoViseur::~AutoViseur() {
}

bool AutoViseur::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    
    Glib::RefPtr<Gdk::Pixbuf> m_image = capture(width, height);
    Gdk::Cairo::set_source_pixbuf(cr,
                                  m_image,
                                  0,
                                  0);
    cr->paint();
    
    return true;
}

bool AutoViseur::on_timeout()
{
    auto win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                         get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}

Glib::RefPtr<Gdk::Pixbuf> AutoViseur::capture(int width, int height) {
    static cv::VideoCapture cap(0);
    cv::Mat webcam, viseur;
    
    cap.read(webcam);
	
    
    viseur = resizeWithinTargetSize(webcam, width, height);

    // Write over
    putText(viseur,
            "OpenCV",
            cv::Point(10,10),
            cv::FONT_HERSHEY_SIMPLEX,
            4,
            cv::Scalar(255, 255, 255),
            2,
            cv::LINE_AA);
    
    // Display on a window:
    return Gdk::Pixbuf::create_from_data(viseur.data,
                                         Gdk::COLORSPACE_RGB,
                                         false,
                                         8,
                                         viseur.cols,
                                         viseur.rows,
                                         viseur.step);

}

cv::Mat AutoViseur::resizeWithinTargetSize(const cv::Mat &input, const int targetWidth, const int targetHeight) {
	
	float scaleX = ((float) targetWidth ) / input.cols;
	float scaleY = ((float) targetHeight) / input.rows;
	float scale = scaleX > scaleY ? scaleY : scaleX;

	int width = input.cols * scale;
	int height = input.rows * scale;

	cv::Mat output;
	resize(input, output, cv::Size(width, height));

	return output;
}
