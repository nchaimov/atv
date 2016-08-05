#include "trace_area.hpp"
#include <iostream>

#include <cairomm/context.h>

TraceArea::TraceArea() : num_locs(0), trace_data(nullptr) {

}

TraceArea::~TraceArea() {

}

bool TraceArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if(trace_data == nullptr) {
        return false;
    }
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();


    return false;
}

void TraceArea::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    this->num_locs = num_locs;
    this->trace_data = trace_data;
    const double dat_h = (100.0*num_locs) + (10.0*(num_locs-1.0)); 
    const double dat_w = (double)trace_data->get_trace_length();
    std::cerr << "I got trace data: " << num_locs << " " << trace_data << std::endl;
    std::cerr << "height: " << dat_h << " width: " << dat_w << std::endl;
    queue_draw();
}

