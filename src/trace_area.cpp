#include "trace_area.hpp"
#include "colors.hpp"
#include <iostream>

#include <cairomm/context.h>

TraceArea::TraceArea() : num_locs(0), trace_data(nullptr) {

}

TraceArea::~TraceArea() {

}

void TraceArea::draw_separators(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    cr->set_line_width(1.0);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    double const width = trace_data->get_trace_length();
    for(uint64_t loc = 1; loc < num_locs; ++loc) {
        double const y_pos = (loc*height_per_loc) + ((loc-1.0)*spacing_between_locs) + 5.0;
        std::cerr << "Separator at " << y_pos << std::endl;
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
        std::cerr << "Loc: " << loc << " top: " << top_of_row << std::endl;
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

bool TraceArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if(trace_data == nullptr) {
        return false;
    }
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    cr->save();
    double logical_height = (height_per_loc*num_locs) + ((spacing_between_locs)*(num_locs-1.0));
    double logical_width  = trace_data->get_trace_length();
    double x_scale = (double)width/logical_width;
    double y_scale = (double)height/logical_height;
    cr->scale(x_scale, y_scale);

    draw_separators(cr);
    draw_tasks(cr);
        
    cr->restore();
    return false;
}

void TraceArea::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    this->num_locs = num_locs;
    this->trace_data = trace_data;
    queue_draw();
}

