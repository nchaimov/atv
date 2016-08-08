#ifndef TRACE_AREA_HPP
#define TRACE_AREA_HPP

#include <stdint.h>
#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>
#include <cairomm/surface.h>
#include <cairomm/matrix.h>

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
    void unzoom();

protected:
    static constexpr double height_per_loc = 100.0;
    static constexpr double spacing_between_locs = 10.0;

    Cairo::RefPtr<Cairo::ImageSurface> image_surface;

    bool selecting = false;
    bool zoom = false;
    gdouble select_start = 0.0;
    gdouble select_stop = 0.0;
    Cairo::Matrix matrix;
        
    void draw_into_local_surface();
    void draw_separators(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_tasks(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_selection_rect(const Cairo::RefPtr<Cairo::Context>& cr);

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    virtual bool on_button_press_event(GdkEventButton* button_event) override;
    virtual bool on_button_release_event(GdkEventButton* button_event) override;
    virtual bool on_motion_notify_event(GdkEventMotion* motion_event) override;

    void on_new_data(uint64_t num_locs, TraceData * trace_data);
};


#endif // TRACE_AREA_HPP
