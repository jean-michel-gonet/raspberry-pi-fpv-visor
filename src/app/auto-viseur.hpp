#ifndef AUTO_VISEUR_H
#define AUTO_VISEUR_H

#include <opencv2/highgui.hpp>
#include <gtkmm.h>
#include <thread>
#include <mutex>

#include "image-capture-service.hpp"
#include "car-service.hpp"
#include "event-bus-service.hpp"

class MakeVideoStreamEvent {
public:
	MakeVideoStreamEvent(bool doIt) {
		this->doIt = doIt;
	}
	bool getDoIt() {
		return doIt;
	}
private:
	bool doIt;
};

class AutoViseur :
public Subscriptor<ImageCapturedEvent>,
public Subscriptor<MakeVideoStreamEvent>,
public Gtk::DrawingArea {
public:
    static const int INITIAL_WIDTH = 480;
    static const int INITIAL_HEIGHT = 320;
	void receive(ImageCapturedEvent imageCapturedEvent) override;
	void receive(MakeVideoStreamEvent makeVideoStreamEvent) override;
    AutoViseur();
    virtual ~AutoViseur();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	void on_size_allocate (Gtk::Allocation& allocation) override;
	void on_capture();

private:
	int width;
	int height;
	EventBusService<ImageCapturedEvent> imageCapturedBus;
	EventBusService<MakeVideoStreamEvent> makeVideoStreamBus;
	bool makingVideoStream;
	Pango::FontDescription fontDescription;
	ImageCaptureService* imageCaptureService;
	CarService* carService;
	cv::Mat lastCapture;
	Glib::Dispatcher captureDispatcher;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
	void displayRec(const Cairo::RefPtr<Cairo::Context>& cr);
	void displayTextTopLeft(const Cairo::RefPtr<Cairo::Context>& cr, char *text);
	void displayTextBottomLeft(const Cairo::RefPtr<Cairo::Context>& cr, char *text);
	void displayTextTopRight(const Cairo::RefPtr<Cairo::Context>& cr, char *text);
	void displayCross(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y);
};


#endif
