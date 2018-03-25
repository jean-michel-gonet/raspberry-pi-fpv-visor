
#include <iostream>
#include "main-window.hpp"

MainWindow::MainWindow():
m_button("Hello World"),
autoViseur(),
probablyInFullScreen(false),
m_box(Gtk::ORIENTATION_VERTICAL) {
    set_border_width(10);
    
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));
    m_button.show();
    m_box.pack_start(m_button, Gtk::PACK_SHRINK);
    
    autoViseur.show();
    m_box.pack_start(autoViseur, Gtk::PACK_EXPAND_WIDGET);

    add(m_box);
    m_box.show();
	
	add_events(Gdk::KEY_PRESS_MASK);
}

MainWindow::~MainWindow() {
}

void MainWindow::on_button_clicked() {
    std::cout << "Hello World" << std::endl;
}

bool MainWindow::on_key_press_event(GdkEventKey* event) {
//	fullscreen();

	// Ctrl + C: Ends the app:
	
	// [F] toggles fullscreen mode:
	if( (event->keyval == GDK_KEY_F) ||
	   (event->keyval == GDK_KEY_f) ) {
		if (probablyInFullScreen) {
			unfullscreen();
			probablyInFullScreen = false;
		} else {
			fullscreen();
			probablyInFullScreen = true;
		}
	}
	
	// [esc] exits fullscreen mode:
	if(event->keyval == GDK_KEY_Escape) {
		unfullscreen();
		probablyInFullScreen = false;
	}

	return true;
}
