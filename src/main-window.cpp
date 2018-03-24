
#include <iostream>
#include "main-window.hpp"
#include "service-locator.hpp"

MainWindow::MainWindow():
m_button("Hello World"),
autoViseur(),
carService(ServiceLocator::newCarService()),
m_box(Gtk::ORIENTATION_VERTICAL) {
    set_border_width(10);
    
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));
    m_button.show();
    m_box.pack_start(m_button, Gtk::PACK_SHRINK);
    
    autoViseur.show();
    m_box.pack_start(autoViseur, Gtk::PACK_EXPAND_WIDGET);

    add(m_box);
    m_box.show();
}

MainWindow::~MainWindow() {
}

void MainWindow::on_button_clicked() {
    std::cout << "Hello World" << std::endl;
}

