//
//  main.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 09/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "main-window.hpp"

int main (int argc, char *argv[]) {

	// Initializes the GUI:
	auto app = Gtk::Application::create(argc, argv, "raspberry.pi.fpv.visor");
	
    MainWindow mainWindow;

    // Launches the GUI:
    return app->run(mainWindow);
}
