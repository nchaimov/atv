#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <gtkmm/treeselection.h>
#include <glibmm.h>
#include "idle_list.hpp"
#include "idle_detector.hpp"
#include "main_window.hpp"

IdleList::IdleList(MainWindow * main_window) : Gtk::TreeView(),
          main_window(main_window), idle_detector(nullptr) {
    append_column("ID", columns.col_id);
    append_column("Name", columns.col_start);
    append_column("Length", columns.col_prop);
    show_all_children();
    Glib::RefPtr<Gtk::TreeSelection> tree_selection = get_selection();
    tree_selection->signal_changed().connect(sigc::mem_fun(*this, &IdleList::on_selection_changed));

}

IdleList::~IdleList() {
    if(idle_detector != nullptr) {
        delete idle_detector;
    }
}

void IdleList::update_model() {
    if(idle_detector != nullptr) {
        tree_store = Gtk::TreeStore::create(columns);
        set_model(tree_store);
        
        idle_detector->analyze();

        const auto & idle_regions  = idle_detector->get_idle_regions();
        const auto & end_events    = idle_detector->get_region_end_events();
        const double interval_sec  = idle_detector->get_interval_sec();
        const uint64_t num_regions = idle_regions.size();
        for(uint64_t region = 0; region < num_regions; ++region) {
            Gtk::TreeModel::Row row = *(tree_store->append());
            row[columns.col_id] = region;
            row[columns.col_start] = end_events[region]->get_object().get_name();
            const auto & idle_region = idle_regions[region];
            const double start =  (std::get<0>(idle_region) * interval_sec);
            const double end =  (std::get<1>(idle_region) * interval_sec);
            const double len = end - start;
            std::stringstream ss;
            ss << std::fixed << std::setprecision(3) << len;
            row[columns.col_prop] = ss.str();
        }

        show_all_children();
        expand_all();
        Glib::RefPtr<Gtk::TreeSelection> tree_selection = get_selection();
        tree_selection->unselect_all();
        }
}

void IdleList::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    (void)num_locs; //unused
    this->trace_data = trace_data;
    if(idle_detector != nullptr) {
        delete idle_detector;
    }
    idle_detector = new IdleDetector{trace_data, 0.0001, 3, 2};
    update_model();
}

void IdleList::on_selection_changed() {
    Glib::RefPtr<Gtk::TreeSelection> tree_selection = get_selection();
    if(first) {
        first = false;
        tree_selection->set_mode(Gtk::SELECTION_NONE);
        return;
    }
    Gtk::TreeModel::iterator iter = tree_selection->get_selected();
    if(iter) {
        Gtk::TreeModel::Row row = *iter;
        uint64_t id = row[columns.col_id];
        const IdleDetector::event_list_t & connections = idle_detector->get_connections_at(id);
        main_window->set_selected_connections(connections);
    } else {
        main_window->clear_selected_connections();
    }
}

bool IdleList::on_button_press_event(GdkEventButton* button_event) {
    if(!clicked) {
        clicked = true;
        Glib::RefPtr<Gtk::TreeSelection> tree_selection = get_selection();
        tree_selection->set_mode(Gtk::SELECTION_SINGLE);
    }
    return Gtk::TreeView::on_button_press_event(button_event);
}
