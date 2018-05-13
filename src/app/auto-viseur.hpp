#ifndef AUTO_VISEUR_H
#define AUTO_VISEUR_H

#include <opencv2/highgui.hpp>
#include <gtkmm.h>
#include <thread>
#include <mutex>

#include "image-capture-service.hpp"
#include "car-service.hpp"
#include "event-bus-service.hpp"

class AutoViseur : public Subscriptor<ImageCapturedEvent>, public Gtk::DrawingArea {
public:
    static const int INITIAL_WIDTH = 480;
    static const int INITIAL_HEIGHT = 320;
	void receive(ImageCapturedEvent imageCapturedEvent) override;
    AutoViseur();
    virtual ~AutoViseur();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	void on_size_allocate (Gtk::Allocation& allocation) override;
	void on_capture();

private:
	int width;
	int height;
	EventBusService<ImageCapturedEvent> eventBusService;
	Pango::FontDescription fontDescription;
	ImageCaptureService* imageCaptureService;
	CarService* carService;
	cv::Mat lastCapture;
	Glib::Dispatcher captureDispatcher;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
	void displayTextTopLeft(const Cairo::RefPtr<Cairo::Context>& cr, char *text);
	void displayTextBottomLeft(const Cairo::RefPtr<Cairo::Context>& cr, char *text);
	void displayTextTopRight(const Cairo::RefPtr<Cairo::Context>& cr, char *text);
	void displayCross(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y);
};


#endif
