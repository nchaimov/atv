#include "main_window.hpp"
#include "trace_reader.hpp"


#include <glibmm.h>
#include <iostream>
#include <functional>
#include <stdint.h>
#include <sstream>
#include <gtkmm/main.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/combobox.h>

MainWindow::MainWindow(const std::string & filename, const TraceReader::locations_t & locations)
        : trace_area(this), related_list(this), filename(filename),
          locations(locations), redraw_on_scroll(true) {
   set_title("APEX Trace Viewer");
   set_border_width(10);
   set_default_size(800,600);
   last_width=800;
   last_height=600;
   
   add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::PROPERTY_CHANGE_MASK);
   signal_map_event().connect(sigc::mem_fun(*this, &MainWindow::setup_load_traces));
   new_data_event().connect(sigc::mem_fun(related_list, &RelatedList::on_new_data));
   new_data_event().connect(sigc::mem_fun(trace_area, &TraceArea::on_new_data));
   new_data_event().connect(sigc::mem_fun(*this, &MainWindow::on_new_data));
   pane.property_position().signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_pane_resize));
   scrollbar.get_adjustment()->signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_scroll_value_changed));

   add(box);
   box.set_hexpand(true);
   box.set_vexpand(true);
   setup_toolbar();
   box.pack_start(load_progress, Gtk::PACK_SHRINK, 5);
   box.pack_start(sep, Gtk::PACK_SHRINK);
   
   trace_area.set_vexpand(true);
   trace_area.set_hexpand(true);
   trace_area.set_size_request(440, -1);
   related_list.set_size_request(160, -1);
   related_list.set_vexpand(true);
   related_list.set_hexpand(true);
   scroll.add(related_list);
   scroll.set_size_request(160, -1);
   trace_box.set_homogeneous(false);
   trace_box.pack_start(trace_area, Gtk::PACK_EXPAND_WIDGET);
   trace_box.set_vexpand(false);
   trace_box.set_hexpand(false);
   scrollbar.set_slider_size_fixed(false);
   trace_box.pack_start(scrollbar, Gtk::PACK_SHRINK);
   pane.pack1(trace_box, false, false);
   pane.pack2(scroll,false, false );
   pane.set_vexpand(true);
   pane.set_hexpand(true);

   box.pack_start(pane, Gtk::PACK_EXPAND_WIDGET);
   
   if(bottom_bar != nullptr) {
       box.pack_start(*bottom_bar, Gtk::PACK_SHRINK);
   }
   load_progress.set_halign(Gtk::ALIGN_FILL);
   load_progress.set_valign(Gtk::ALIGN_CENTER);
   load_progress.set_show_text(true);

   load_progress.show();
   sep.show();
   trace_area.show();
   scrollbar.show();
   trace_box.show();
   related_list.show();
   scroll.show();
   pane.show();
   box.show();
}


MainWindow::~MainWindow() {

}

void MainWindow::setup_toolbar() {
    builder = Gtk::Builder::create();
    add_action("unzoom", sigc::mem_fun(trace_area, &TraceArea::unzoom));
    add_action("zoom_in", sigc::mem_fun(trace_area, &TraceArea::zoom_in));
    add_action("zoom_out", sigc::mem_fun(trace_area, &TraceArea::zoom_out));
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
        "        <property name='action_name'>win.zoom_out</property>"
        "        <property name='icon_name'>zoom-out</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkSeparatorToolItem' id='tool_sep'>"
        "        <property name='draw'>False</property>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>True</property>"
        "        <property name='homogeneous'>False</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkToolItem' id='toolbox_view'>"
        "        <property name='visible'>True</property>"
        "        <child>"
        "          <object class='GtkComboBox' id='toolbox_combo'>"
        "            <property name='visible'>True</property>"
        "          </object>"
        "        </child>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>False</property>"
        "      </packing>"
        "    </child>"
        "  </object>"
        "</interface>";
    builder->add_from_string(ui_info);
    builder->get_widget("toolbar", top_bar);
    if(top_bar == nullptr) {
        std::cerr << "No toolbar found??" << std::endl;
        throw std::runtime_error("Unable to create toolbar");
    }         
    combobox = nullptr;
    builder->get_widget("toolbox_combo", combobox);
    if(combobox == nullptr) {
        std::cerr << "No combo box found??" << std::endl;
    }
    else {
        list_store = Gtk::ListStore::create(columns);
        combobox->set_model(list_store);
        Gtk::TreeModel::Row row = *(list_store->append());
        row[columns.view_num]  = 1;
        row[columns.view_name] = "Task Execution";
        Gtk::TreeModel::Row row2 = *(list_store->append());
        row2[columns.view_num]  = 2;
        row2[columns.view_name] = "Concurrency";
        combobox->set_active(row);
        combobox->pack_start(columns.view_name);
        combobox->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_view_changed));
    }
    box.pack_start(*top_bar, Gtk::PACK_SHRINK);   

    // Bottom bar
    const Glib::ustring bottom_bar_ui_info =
        "<interface>"
        "  <requires lib='gtk+' version='3.4'/>"
        "  <object class='GtkToolbar' id='bottom_toolbar'>"
        "    <property name='visible'>True</property>"
        "    <property name='can_focus'>False</property>"
        "    <child>"
        "      <object class='GtkToolItem' id='label_holder'>"
        "        <property name='visible'>True</property>"
        "        <child>"
        "          <object class='GtkLabel' id='task_label'>"
        "            <property name='visible'>True</property>"
        "            <property name='label'></property>"
        "          </object>"
        "        </child>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>False</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkSeparatorToolItem' id='bot_tool_sep'>"
        "        <property name='draw'>False</property>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>True</property>"
        "        <property name='homogeneous'>False</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkToolItem' id='right_label_holder'>"
        "        <property name='visible'>True</property>"
        "        <child>"
        "          <object class='GtkLabel' id='time_label'>"
        "            <property name='visible'>True</property>"
        "            <property name='label'></property>"
        "          </object>"
        "        </child>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>False</property>"
        "      </packing>"
        "    </child>"
        "  </object>"
        "</interface>";
    builder->add_from_string(bottom_bar_ui_info);
    builder->get_widget("bottom_toolbar", bottom_bar);
    if(bottom_bar == nullptr) {
        std::cerr << "No toolbar found??" << std::endl;
        throw std::runtime_error("Unable to create toolbar");
    }         
    builder->get_widget("task_label", task_label);
    if(task_label == nullptr) {
        std::cerr << "No task label found??" << std::endl;
        throw std::runtime_error("Unable to create task label");
    }
    builder->get_widget("time_label", time_label);
    if(time_label == nullptr) {
        std::cerr << "No time label found??" << std::endl;
        throw std::runtime_error("Unable to create time label");
    } else {
        time_label->set_justify(Gtk::JUSTIFY_RIGHT);
    }
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
    while(Gtk::Main::events_pending()) {
        Gtk::Main::iteration(true);
    }
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

void MainWindow::on_view_changed() {
    if(combobox != nullptr)  {
        Gtk::TreeModel::iterator iter = combobox->get_active();
        if(iter) {
            Gtk::TreeModel::Row row = *iter;
            if(row) {
                int id = row[columns.view_num];
                switch(id) {
                    case 1: trace_area.set_mode(TraceArea::Mode::TaskExecution); break;
                    case 2: trace_area.set_mode(TraceArea::Mode::Concurrency); break;
                    default: std::cerr << "Invalid mode" << std::endl;
                }
            }
        }
    }
}

void MainWindow::set_task_label_text(const Glib::ustring& str) {
    if(task_label != nullptr) {
        task_label->set_markup(str);
    }
}

void MainWindow::set_time_label_text(const Glib::ustring& str) {
    if(time_label != nullptr) {
        time_label->set_markup(str);
    }
}

void MainWindow::set_selected_event(const TraceData::Event * event) {
    related_list.set_selected_task(event);
}


void MainWindow::on_pane_resize() {
    trace_area.redraw();
}

void MainWindow::set_scroll_range(const double min, const double max) {
    max_time = max;
    Glib::RefPtr<Gtk::Adjustment> adj = scrollbar.get_adjustment();
    adj->set_lower(min);
    adj->set_upper(max);
}

void MainWindow::set_scroll_page_size(const double page_size) {
    scrollbar.set_increments(page_size / 4.0, page_size);
    Glib::RefPtr<Gtk::Adjustment> adj = scrollbar.get_adjustment();
    adj->set_page_size(page_size);
    adj->set_page_increment(page_size/4.0);
    adj->set_upper(max_time + page_size);
}

void MainWindow::set_scroll_position(const double position, const bool should_redraw) {
    redraw_on_scroll = should_redraw;
    Glib::RefPtr<Gtk::Adjustment> adj = scrollbar.get_adjustment();
    adj->set_value(position);
}

void MainWindow::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    const double length = (double)trace_data->get_trace_length();
    set_scroll_range(0.0, length);
    set_scroll_page_size(length);
    set_scroll_position(length / 2.0);
}

void MainWindow::on_scroll_value_changed() {
    if(redraw_on_scroll) {
        Glib::RefPtr<Gtk::Adjustment> adj = scrollbar.get_adjustment();
        trace_area.set_position(adj->get_value());
    } else {
        redraw_on_scroll = true;
    }
}

void MainWindow::set_scroll_allowed(const bool allowed) {
    scrollbar.set_sensitive(allowed);
}

void MainWindow::set_selected_related_guid(const std::string & guid) {
    trace_area.set_selected_related_guid(guid);
}

