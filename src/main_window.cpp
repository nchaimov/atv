#include "main_window.hpp"
#include "trace_reader.hpp"


#include <glibmm.h>
#include <iostream>
#include <functional>
#include <stdint.h>
#include <sstream>
#include <gtkmm/main.h>

MainWindow::MainWindow(const std::string & filename, const TraceReader::locations_t & locations)
        : filename(filename), locations(locations) {
   set_title("APEX Trace Viewer");
   set_border_width(10);
   set_default_size(800,600);
   
   signal_map_event().connect(sigc::mem_fun(*this, &MainWindow::setup_load_traces));
   new_data_event().connect(sigc::mem_fun(trace_area, &TraceArea::on_new_data));

   add(box);
   box.pack_start(load_progress, Gtk::PACK_SHRINK, 5);
   box.pack_start(sep, Gtk::PACK_SHRINK);
   box.pack_start(trace_area);
   load_progress.set_halign(Gtk::ALIGN_FILL);
   load_progress.set_valign(Gtk::ALIGN_CENTER);
   load_progress.set_show_text(true);

   load_progress.show();
   sep.show();
   trace_area.show();
   box.show();
}


MainWindow::~MainWindow() {

}

bool MainWindow::setup_load_traces(GdkEventAny * event) {
    sigc::slot<void> my_slot = sigc::mem_fun(*this, &MainWindow::load_traces);
    Glib::signal_timeout().connect_once(my_slot, 50);
    return false;
}

void MainWindow::load_traces() {
    using namespace std::placeholders;
    TraceReader reader{filename, locations, &callbacks};
    reader.read_traces(std::bind(&MainWindow::update_status, this, _1));
    //TODO handle errors
}


void MainWindow::update_status(uint64_t num_locs) {
    static const uint64_t max_loc = locations.size();
    const double frac = (double)num_locs / (double)max_loc;
    load_progress.set_fraction(frac);
    std::stringstream ss;
    ss << "Location " << num_locs << " of " << max_loc;
    load_progress.set_text(ss.str());
    std::cerr << ss.str() << std::endl;
    if(num_locs == max_loc) {
        load_progress.hide();
        sep.hide();
        Gtk::Main::iteration(true);
        new_data_signal.emit(num_locs, callbacks.get_trace_data());
    }
    Gtk::Main::iteration(true);
}


MainWindow::new_data_signal_t MainWindow::new_data_event() const {
    return new_data_signal;
}
