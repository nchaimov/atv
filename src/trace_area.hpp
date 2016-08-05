#ifndef TRACE_AREA_HPP
#define TRACE_AREA_HPP

#include <stdint.h>
#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>
#include <cairomm/surface.h>

#include "trace_data.hpp"

class MainWindow;

class TraceArea : public Gtk::DrawingArea {
public:
    friend class MainWindow;
    TraceArea();
    virtual ~TraceArea();

    uint64_t num_locs;
    TraceData * trace_data;

    void redraw();

protected:
    static constexpr double height_per_loc = 100.0;
    static constexpr double spacing_between_locs = 10.0;

    Cairo::RefPtr<Cairo::ImageSurface> image_surface;
        
    void draw_into_local_surface();
    void draw_separators(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_tasks(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;



    void on_new_data(uint64_t num_locs, TraceData * trace_data);
};


#endif // TRACE_AREA_HPP
