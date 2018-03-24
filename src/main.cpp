//
//  main.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 09/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <iostream>
#include <gtkmm.h>
#include <gtkmm/application.h>

#include "main-window.hpp"
#include "car-service.hpp"

int main (int argc, char *argv[]) {

	// Initializes services:
	CarService carService;
	Glib::signal_timeout().connect( sigc::mem_fun(&carService, &CarService::refreshStatus), 1000);

	// Initializes the GUI:
	auto app = Gtk::Application::create(argc, argv, "raspberry.pi.fpv.visor");
	
    MainWindow mainWindow;

    // Launches the GUI:
    return app->run(mainWindow);
}
