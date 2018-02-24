//
//  main.cpp
//  opencv-hello-world
//
//  Created by Jean-Michel Gonet on 09/02/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <iostream>
#include <gtkmm.h>
#include "hello-world.hpp"
#include <gtkmm/application.h>


int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    
    HelloWorld helloworld;
    
    //Shows the window and returns when it is closed.
    return app->run(helloworld);
}
