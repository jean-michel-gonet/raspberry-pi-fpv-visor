#ifndef AUTO_VISEUR_H
#define AUTO_VISEUR_H

#include <opencv2/highgui.hpp>
#include <gtkmm.h>
#include <thread>
#include <mutex>

#include "image-capture-service-from-camera.hpp"


class AutoViseur : public Gtk::DrawingArea {
public:
    static const int INITIAL_WIDTH = 480;
    static const int INITIAL_HEIGHT = 320;

	void notifyCapture();
    AutoViseur();
    virtual ~AutoViseur();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	void on_size_allocate (Gtk::Allocation& allocation) override;
	void on_capture();

private:
	ImageCaptureServiceFromCamera imageCaptureService;
	cv::Mat lastCapture;
	Glib::Dispatcher captureDispatcher;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};


#endif
