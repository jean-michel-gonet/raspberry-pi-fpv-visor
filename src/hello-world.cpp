
#include <iostream>
#include "hello-world.hpp"

HelloWorld::HelloWorld():
m_button("Hello World"),
autoViseur(),
m_box(Gtk::ORIENTATION_VERTICAL) {
    set_border_width(10);
    
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::on_button_clicked));
    m_button.show();
    m_box.pack_start(m_button, Gtk::PACK_SHRINK);
    
    autoViseur.show();
    m_box.pack_start(autoViseur, Gtk::PACK_EXPAND_WIDGET);

    add(m_box);
    m_box.show();
}

HelloWorld::~HelloWorld() {
}

void HelloWorld::on_button_clicked() {
    std::cout << "Hello World" << std::endl;
}

void HelloWorld::setCarService(CarService &carService) {
	this->carService = carService;
}
