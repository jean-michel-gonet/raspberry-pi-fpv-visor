
#include <iostream>
#include "main-window.hpp"

MainWindow::MainWindow():
autoViseur(),
probablyInFullScreen(true) {
	set_border_width(10);    
	add(autoViseur);
	autoViseur.show();
	add_events(Gdk::KEY_PRESS_MASK);
	fullscreen();
}

MainWindow::~MainWindow() {
}

bool MainWindow::on_key_press_event(GdkEventKey* event) {

	switch (event->keyval) {
		// Ctrl + C: Ends the app:
		case GDK_KEY_C:
		case GDK_KEY_c:
			if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {
				get_application()->quit();
			}
			break;
			
		// [F] toggles fullscreen mode:
		case GDK_KEY_F:
		case GDK_KEY_f:
			if (probablyInFullScreen) {
				unfullscreen();
				probablyInFullScreen = false;
			} else {
				fullscreen();
				probablyInFullScreen = true;
			}
			break;
			
		// [esc] exits fullscreen mode:
		case GDK_KEY_Escape:
			unfullscreen();
			probablyInFullScreen = false;
			break;
			
	}

	return true;
}
