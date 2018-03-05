#ifndef AUTO_VISEUR_H
#define AUTO_VISEUR_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "opencv2/core.hpp"


class AutoViseur : public Gtk::DrawingArea {
public:
    static const int INITIAL_WIDTH = 480;
    static const int INITIAL_HEIGHT = 80;
    
    AutoViseur();
    virtual ~AutoViseur();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	void on_size_allocate (Gtk::Allocation& allocation) override;
    bool on_timeout();
    Glib::RefPtr<Gdk::Pixbuf> capture(int width, int height);
	cv::Mat resizeWithinTargetSize(const cv::Mat &input, const int targetWidth, const int targetHeight);
};

#endif
