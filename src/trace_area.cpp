#include "trace_area.hpp"
#include "colors.hpp"
#include <iostream>

#include <cairomm/context.h>
#include <cairomm/surface.h>

TraceArea::TraceArea() : num_locs(0), trace_data(nullptr) {
    set_hexpand(true);
    set_vexpand(true);
}

TraceArea::~TraceArea() {

}

void TraceArea::redraw() {
    image_surface.clear();
    queue_resize();
}

void TraceArea::draw_separators(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    cr->set_line_width(1.0);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    double const width = trace_data->get_trace_length();
    for(uint64_t loc = 1; loc < num_locs; ++loc) {
        double const y_pos = (loc*height_per_loc) + ((loc-1.0)*spacing_between_locs) + 5.0;
        cr->move_to(0.0, y_pos);
        cr->line_to(width, y_pos);
        cr->stroke();
    }
    cr->restore();
}

void TraceArea::draw_tasks(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    const uint64_t global_offset = trace_data->get_global_offset();
    for(uint64_t loc = 0; loc < num_locs; ++loc) {
        uint64_t last_enter = 0;
        const double top_of_row = (loc*height_per_loc) + ((loc-1.0)*spacing_between_locs)  + 10.0;
        const auto & events = trace_data->get_compute_events(loc);
        for(const TraceData::Event & event : events) {
            switch(event.get_event_type()) {
                case TraceData::EventType::Enter: {
                    last_enter = event.get_time() - global_offset;                                  
                };
                break;
                case TraceData::EventType::Leave: {
                    const uint64_t this_end = event.get_time() - global_offset;
                    const double rect_width = this_end - last_enter;
                    Colors::set_color(cr, event.get_seq_entry_id());
                    cr->rectangle(last_enter, top_of_row, rect_width, height_per_loc);
                    cr->fill();
                };
                break;
                default:
                continue;
            }
        }
    }
    cr->restore();
}

void TraceArea::draw_into_local_surface() {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    image_surface = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, width, height);
    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(image_surface);

    cr->save();

    double logical_height = (height_per_loc*num_locs) + ((spacing_between_locs)*(num_locs-1.0));
    double logical_width  = trace_data->get_trace_length();
    double x_scale = (double)width/logical_width;
    double y_scale = (double)height/logical_height;
    cr->scale(x_scale, y_scale);

    cr->set_source_rgb(1.0, 1.0, 1.0); // white background
    cr->set_antialias(Cairo::ANTIALIAS_NONE);
    cr->paint();

    draw_separators(cr);
    draw_tasks(cr);
    cr->restore();
}

bool TraceArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if(trace_data == nullptr) {
        return false;
    }
    if(!image_surface) {
        draw_into_local_surface();
    }
    cr->save();
    cr->set_antialias(Cairo::ANTIALIAS_NONE);
    cr->set_source(image_surface, 0, 0);
    cr->paint();
    return false;
}

void TraceArea::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    this->num_locs = num_locs;
    this->trace_data = trace_data;
    queue_draw();
}

