#include "trace_area.hpp"
#include "colors.hpp"
#include <iostream>
#include <cmath>

#include <cairomm/context.h>
#include <cairomm/surface.h>

TraceArea::TraceArea() : num_locs(0), trace_data(nullptr) {
    set_hexpand(true);
    set_vexpand(true);
    add_events(Gdk::BUTTON_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

TraceArea::~TraceArea() {

}

void TraceArea::redraw() {
    image_surface.clear();
    queue_resize();
}

void TraceArea::unzoom() {
    zoom = false;
    select_start = 0.0;
    select_stop = trace_data->get_trace_length();
    redraw();
}

void TraceArea::draw_separators(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    double line_width = 1.0;
    double unused = 0.0;
    // convert desired line_width in pixels to user space
    cr->device_to_user_distance(unused, line_width);
    cr->set_line_width(line_width);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    for(uint64_t loc = 1; loc < num_locs; ++loc) {
        double  y_pos = (loc*height_per_loc) + ((loc-1.0)*spacing_between_locs) + 5.0;
        double unused = 0.0;
        // round up in device space then convert back so we get a 1-pixel line
        cr->user_to_device(unused, y_pos);
        y_pos = std::ceil(y_pos);
        cr->device_to_user(unused, y_pos);
        cr->move_to(select_start, y_pos);
        cr->line_to(select_stop + select_start,  y_pos);
        cr->stroke();
    }
    cr->restore();
}

void TraceArea::draw_tasks(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    uint64_t global_offset = trace_data->get_global_offset();
    for(uint64_t loc = 0; loc < num_locs; ++loc) {
        uint64_t last_enter = 0;
        const double top_of_row = (loc*height_per_loc) + ((loc-1.0)*spacing_between_locs)  + 10.0;
        const auto & events = trace_data->get_compute_events(loc);
        auto start_iterator = zoom ? trace_data->get_compute_event_at_time(loc, select_start+global_offset) : events.begin();
        auto stop_iterator = zoom ? trace_data->get_compute_event_at_time(loc, select_stop+global_offset) : events.end();
        for(auto & it = start_iterator; it != stop_iterator; ++it) {
            const auto & event = *it;
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
    double logical_width;
         
    if(zoom) {
        std::cerr << "Zoom requested between " << select_start << " and " << select_stop << std::endl;
        logical_width = select_stop - select_start;
        std::cerr << "Width = " << logical_width << std::endl;
    } else {
        logical_width = trace_data->get_trace_length();
    }

    // Scale so right of selected area is offscreen
    // logical select_stop == physical width
    const double x_scale = (double)width/logical_width;
    const double y_scale = (double)height/logical_height;
    cr->scale(x_scale, y_scale);
    // Move origin so left of selected area is offscreen
    // logical select_start == 0
    if(zoom) {
        cr->translate(-select_start, 0.0);
    }

    cr->get_matrix(matrix);
    matrix.invert();

    cr->set_source_rgb(1.0, 1.0, 1.0); // white background
    cr->set_antialias(Cairo::ANTIALIAS_NONE);
    cr->paint();

    draw_separators(cr);
    draw_tasks(cr);
    cr->restore();
}


void TraceArea::draw_selection_rect(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int height = allocation.get_height();
    cr->save();
    cr->set_source_rgba(0.0,1.0,0.3,0.4);
    cr->rectangle(select_start, 0.0, select_stop-select_start, height);
    cr->fill();
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
    cr->set_source(image_surface, 0, 0);
    cr->paint();
    if(selecting) {
        draw_selection_rect(cr);
    }
    cr->restore();
    return false;
}

void TraceArea::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    this->num_locs = num_locs;
    this->trace_data = trace_data;
    this->select_start = 0.0;
    this->select_stop = this->trace_data->get_trace_length();
    queue_draw();
}


bool TraceArea::on_button_press_event(GdkEventButton* button_event) {
    select_start = button_event->x;
    select_stop = button_event->x;
    selecting = true;
    queue_draw();
    return false;
}

bool TraceArea::on_button_release_event(GdkEventButton* button_event) {
    select_stop = button_event->x;
    selecting = false;
    if(select_start != select_stop) {
        if(select_start > select_stop) {
            std::swap(select_start, select_stop);
        }
        double unused = 0.0; // transform_point needs a y coord
        matrix.transform_point(select_start, unused);
        matrix.transform_point(select_stop, unused);
        zoom = true;
        redraw();
    }
    queue_draw();
    return false;
}

bool TraceArea::on_motion_notify_event(GdkEventMotion* motion_event) {
    if(selecting) {
        select_stop = motion_event->x;
        queue_draw();
    }
    return false;
}
