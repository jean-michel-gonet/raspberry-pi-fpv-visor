#ifndef main_window_hpp
#define main_window_hpp

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>

#include "auto-viseur.hpp"

class MainWindow : public Gtk::Window {
    
public:
	MainWindow();
	virtual ~MainWindow();
    
protected:
	bool on_key_press_event(GdkEventKey* event) override;
	bool probablyInFullScreen;
	AutoViseur autoViseur;
};

#endif
