#ifndef AUTO_VISEUR_H
#define AUTO_VISEUR_H

#include "opencv2/highgui.hpp"
#include <gtkmm.h>
#include <thread>
#include <mutex>


class AutoViseurCapture {
public:
	// Starts capturing images from camera.
	void start();
	
	// Stops capturing images from camera.
	void stop();
	
	// Configures the camera's capturing size
	// Depending on hardware, all sizes are not available.
	void setSize(int width, int height);
	
	// Sets the method to receice notifications
	// each time a new image is captured and ready.
	void setNotification(std::function<void (cv::Mat)>);
		
	// Constructor.
	AutoViseurCapture();
	
	// Destructor.
	virtual ~AutoViseurCapture() = default;
	
private:
	bool mustStop;
	std::thread* separatedThread;
	mutable std::mutex configurationMutex;
	cv::Mat mat;
	cv::VideoCapture videoCapture;
	void doCapture();
	std::function<void (cv::Mat)> notifyCapture;
};


class AutoViseur : public Gtk::DrawingArea {
public:
    static const int INITIAL_WIDTH = 480;
    static const int INITIAL_HEIGHT = 320;

	void notifyCapture(cv::Mat mat);
    AutoViseur();
    virtual ~AutoViseur();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	void on_size_allocate (Gtk::Allocation& allocation) override;
	void on_capture();

private:
	AutoViseurCapture autoViseurCapture;
	cv::Mat lastCapture;
	Glib::Dispatcher captureDispatcher;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};


#endif
