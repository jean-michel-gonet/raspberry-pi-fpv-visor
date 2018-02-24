#ifndef AUTO_VISEUR_H
#define AUTO_VISEUR_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

class AutoViseur : public Gtk::DrawingArea
{
public:
    static const int INITIAL_WIDTH = 480;
    static const int INITIAL_HEIGHT = 320;
    
    AutoViseur();
    virtual ~AutoViseur();
    
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();
    Glib::RefPtr<Gdk::Pixbuf> capture(int width, int height);
};

#endif
