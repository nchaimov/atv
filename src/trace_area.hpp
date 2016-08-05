#ifndef TRACE_AREA_HPP
#define TRACE_AREA_HPP

#include <stdint.h>
#include <gtkmm/drawingarea.h>
#include <sigc++/sigc++.h>

#include "trace_data.hpp"

class MainWindow;

class TraceArea : public Gtk::DrawingArea {
public:
    friend class MainWindow;
    TraceArea();
    virtual ~TraceArea();

    uint64_t num_locs;
    TraceData * trace_data;

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    void on_new_data(uint64_t num_locs, TraceData * trace_data);
};


#endif // TRACE_AREA_HPP
