#include "main_window.hpp"
#include "trace_reader.hpp"


#include <glibmm.h>
#include <iostream>
#include <functional>
#include <stdint.h>
#include <sstream>
#include <gtkmm/main.h>
#include <gtkmm/toolbar.h>

MainWindow::MainWindow(const std::string & filename, const TraceReader::locations_t & locations)
        : filename(filename), locations(locations) {
   set_title("APEX Trace Viewer");
   set_border_width(10);
   set_default_size(800,600);
   last_width=800;
   last_height=600;
   
   add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
   signal_map_event().connect(sigc::mem_fun(*this, &MainWindow::setup_load_traces));
   new_data_event().connect(sigc::mem_fun(trace_area, &TraceArea::on_new_data));

   add(box);
   box.set_hexpand(true);
   box.set_vexpand(true);
   setup_toolbar();
   box.pack_start(load_progress, Gtk::PACK_SHRINK, 5);
   box.pack_start(sep, Gtk::PACK_SHRINK);
   box.pack_start(trace_area, Gtk::PACK_EXPAND_WIDGET);
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

void MainWindow::setup_toolbar() {
    builder = Gtk::Builder::create();
    add_action("unzoom", sigc::mem_fun(trace_area, &TraceArea::unzoom));
    const Glib::ustring ui_info =
        "<!-- Generated with glade 3.18.3 -->"
        "<interface>"
        "  <requires lib='gtk+' version='3.4'/>"
        "  <object class='GtkToolbar' id='toolbar'>"
        "    <property name='visible'>True</property>"
        "    <property name='can_focus'>False</property>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_unzoom'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>Original Size</property>"
        "        <property name='action_name'>win.unzoom</property>"
        "        <property name='icon_name'>zoom-original</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_zoom_in'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>Zoom In</property>"
        "        <property name='action_name'>win.zoom_in</property>"
        "        <property name='icon_name'>zoom-in</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_zoom_out'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>Zoom Out</property>"
        "        <property name='action_name'>wout.zoom_out</property>"
        "        <property name='icon_name'>zoom-out</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "  </object>"
        "</interface>";
    builder->add_from_string(ui_info);
    Gtk::Toolbar* toolbar = nullptr;
    builder->get_widget("toolbar", toolbar);
    if(toolbar == nullptr) {
        std::cerr << "No toolbar found??" << std::endl;
        return;
    }         
    box.pack_start(*toolbar, Gtk::PACK_SHRINK);   
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


bool MainWindow::on_configure_event(GdkEventConfigure* configure_event) {
    if(configure_event->width != last_width || configure_event->height != last_height) {
        trace_area.redraw();    
        last_width = configure_event->width;
        last_height = configure_event->height;
    }
    return false;
}
