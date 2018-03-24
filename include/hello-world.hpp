#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>

#include "auto-viseur.hpp"
#include "car-service.hpp"

class HelloWorld : public Gtk::Window {
    
public:
    HelloWorld();
    virtual ~HelloWorld();
    
protected:
    void on_button_clicked();
    Gtk::Button m_button;
    Gtk::Box m_box;
    AutoViseur autoViseur;
	
private:
	CarService *carService;
};

#endif
