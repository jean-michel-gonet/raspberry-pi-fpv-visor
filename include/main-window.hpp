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
    void on_button_clicked();
    Gtk::Button m_button;
    Gtk::Box m_box;
    AutoViseur autoViseur;
};

#endif
