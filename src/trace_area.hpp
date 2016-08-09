#ifndef TRACE_AREA_HPP
#define TRACE_AREA_HPP

#include <stdint.h>
#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>
#include <cairomm/surface.h>
#include <cairomm/matrix.h>
#include <gtkmm/menu.h>
#include <sigc++/connection.h>

#include "trace_data.hpp"

class MainWindow;

class TraceArea : public Gtk::DrawingArea {
public:
    friend class MainWindow;
    TraceArea(MainWindow * main_window);
    virtual ~TraceArea();

    uint64_t num_locs;
    TraceData * trace_data;

    void redraw();
    void unzoom();
    void zoom_in();
    void zoom_out();

protected:
    static constexpr double height_per_loc = 100.0;
    static constexpr double spacing_between_locs = 10.0;

    MainWindow * main_window;
    Gtk::Menu * menu;

    Cairo::RefPtr<Cairo::ImageSurface> image_surface;

    bool selecting = false;
    bool zoom = false;
    gdouble select_start = 0.0;
    gdouble select_stop = 0.0;
    gdouble zoom_start = 0.0;
    gdouble zoom_stop = 0.0;
    Cairo::Matrix matrix;
    bool should_update_label = false;
    uint64_t selected_loc = TraceData::INVALID_LOCATION_REF;
    const TraceData::Event * selected_event_start = nullptr;
    const TraceData::Event * selected_event_end = nullptr;
        
    void draw_into_local_surface();
    void set_scale(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_separators(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_tasks(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_selection_rect(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_selected_task(const Cairo::RefPtr<Cairo::Context>& cr);
    uint64_t location_for_coord(double y) const;
   
    bool display_popup_menu(GdkEventButton* button_event);  
    void select_event_under_cursor(double x, double y);

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    virtual bool on_button_press_event(GdkEventButton* button_event) override;
    virtual bool on_button_release_event(GdkEventButton* button_event) override;
    virtual bool on_motion_notify_event(GdkEventMotion* motion_event) override;

    void on_new_data(uint64_t num_locs, TraceData * trace_data);

    void set_task_label_for_coord(double x, double y);
};


#endif // TRACE_AREA_HPP
