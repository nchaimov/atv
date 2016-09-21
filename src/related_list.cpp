#include <set>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <gtkmm/treeselection.h>
#include "related_list.hpp"
#include "main_window.hpp"

RelatedList::RelatedList(MainWindow * main_window) : Gtk::TreeView(),
          main_window(main_window), selected_event(nullptr) {
    append_column("GUID", columns.col_name);
    append_column("Property", columns.col_prop);
    show_all_children();
    Glib::RefPtr<Gtk::TreeSelection> tree_selection = get_selection();
    tree_selection->set_select_function(sigc::mem_fun(*this, &RelatedList::select_function));
    tree_selection->signal_changed().connect(sigc::mem_fun(*this, &RelatedList::on_selection_changed));
    set_fixed_height_mode(true);

}

RelatedList::~RelatedList() {
}

void RelatedList::update_model() {
    if(trace_data != nullptr) {
        unset_model();
        tree_store = Gtk::TreeStore::create(columns);
        tree_store->unset_default_sort_func();
        
        Gtk::TreeModel::Row data_acquired_row = *(tree_store->append());
        data_acquired_row[columns.col_id] = 1;
        data_acquired_row[columns.col_name] = "Datablocks Acquired";

        Gtk::TreeModel::Row data_created_row = *(tree_store->append());
        data_created_row[columns.col_id] = 2;
        data_created_row[columns.col_name] = "Datablocks Created";

        Gtk::TreeModel::Row data_destroyed_row = *(tree_store->append());
        data_destroyed_row[columns.col_id] = 3;
        data_destroyed_row[columns.col_name] = "Datablocks Destroyed";

        Gtk::TreeModel::Row tasks_created_row = *(tree_store->append());
        tasks_created_row[columns.col_id] = 4;
        tasks_created_row[columns.col_name] = "Tasks Created";

        Gtk::TreeModel::Row tasks_destroyed_row = *(tree_store->append());
        tasks_destroyed_row[columns.col_id] = 5;
        tasks_destroyed_row[columns.col_name] = "Tasks Destroyed";

        Gtk::TreeModel::Row events_created_row = *(tree_store->append());
        events_created_row[columns.col_id] = 6;
        events_created_row[columns.col_name] = "Events Created";

        Gtk::TreeModel::Row events_destroyed_row = *(tree_store->append());
        events_destroyed_row[columns.col_id] = 7;
        events_destroyed_row[columns.col_name] = "Events Destroyed";

        if(selected_event != nullptr) {
            const std::string guid = selected_event->get_object().get_guid();
            const auto & related_events = trace_data->get_events_for_guid(guid);
            std::set<std::string> block_acquires_seen;
            std::set<std::string> block_creates_seen;
            std::set<std::string> block_destroys_seen;
            std::set<std::string> task_creates_seen;
            std::set<std::string> task_destroys_seen;
            std::set<std::string> event_creates_seen;
            std::set<std::string> event_destroys_seen;
            int next_id = 8;
            for(const auto event_ptr : related_events) {
                switch(event_ptr->get_event_type()) {
                    case TraceData::EventType::DataAcquire: {
                        std::string db_guid = event_ptr->get_subject().get_guid();
                        if(block_acquires_seen.count(db_guid) == 0) {
                            block_acquires_seen.insert(db_guid);
                            Gtk::TreeModel::Row acquire_row = *(tree_store->append(data_acquired_row.children()));
                            acquire_row[columns.col_id] = next_id++;
                            acquire_row[columns.col_name] = db_guid;
                            std::stringstream ss;
                            ss << event_ptr->get_size();
                            acquire_row[columns.col_prop] = ss.str();
                        }
                    }
                    break;

                    case TraceData::EventType::DataCreate: {
                        std::string db_guid = event_ptr->get_object().get_guid();
                        if(block_creates_seen.count(db_guid) == 0) {
                            block_creates_seen.insert(db_guid);
                            Gtk::TreeModel::Row create_row = *(tree_store->append(data_created_row.children()));
                            create_row[columns.col_id] = next_id++;
                            create_row[columns.col_name] = db_guid;
                            std::stringstream ss;
                            ss << event_ptr->get_size();
                            create_row[columns.col_prop] = ss.str();
                        }
                    }
                    break;

                    case TraceData::EventType::DataDestroy: {
                        std::string db_guid = event_ptr->get_object().get_guid();
                        if(block_destroys_seen.count(db_guid) == 0) {
                            block_destroys_seen.insert(db_guid);
                            Gtk::TreeModel::Row destroy_row = *(tree_store->append(data_destroyed_row.children()));
                            destroy_row[columns.col_id] = next_id++;
                            destroy_row[columns.col_name] = db_guid;
                            destroy_row[columns.col_prop] = "";
                        }
                    }
                    break;

                    case TraceData::EventType::TaskCreate: {
                        std::string task_guid = event_ptr->get_object().get_guid();
                        if(event_ptr->get_parent().get_guid() != guid) {
                            break;
                        }
                        if(task_creates_seen.count(task_guid) == 0) {
                            task_creates_seen.insert(task_guid);
                            Gtk::TreeModel::Row create_row = *(tree_store->append(tasks_created_row.children()));
                            create_row[columns.col_id] = next_id++;
                            create_row[columns.col_name] = task_guid;
                            create_row[columns.col_prop] = event_ptr->get_object().get_name();
                        }
                    }
                    break;

                    case TraceData::EventType::TaskDestroy: {
                        std::string task_guid = event_ptr->get_object().get_guid();
                        if(event_ptr->get_parent().get_guid() != guid) {
                            break;
                        }
                        if(task_destroys_seen.count(task_guid) == 0) {
                            task_destroys_seen.insert(task_guid);
                            Gtk::TreeModel::Row destroy_row = *(tree_store->append(tasks_destroyed_row.children()));
                            destroy_row[columns.col_id] = next_id++;
                            destroy_row[columns.col_name] = task_guid;
                            destroy_row[columns.col_prop] = event_ptr->get_object().get_name();
                        }
                    }
                    break;

                    case TraceData::EventType::EventCreate: {
                        std::string event_guid = event_ptr->get_object().get_guid();
                        if(event_creates_seen.count(event_guid) == 0) {
                            event_creates_seen.insert(event_guid);
                            Gtk::TreeModel::Row create_row = *(tree_store->append(events_created_row.children()));
                            create_row[columns.col_id] = next_id++;
                            create_row[columns.col_name] = event_guid;
                        }
                    }
                    break;

                    case TraceData::EventType::EventDestroy: {
                        std::string event_guid = event_ptr->get_object().get_guid();
                        if(event_destroys_seen.count(event_guid) == 0) {
                            event_destroys_seen.insert(event_guid);
                            Gtk::TreeModel::Row destroy_row = *(tree_store->append(events_destroyed_row.children()));
                            destroy_row[columns.col_id] = next_id++;
                            destroy_row[columns.col_name] = event_guid;
                        }
                    }
                    break;


                    default:
                    break;
                }
            }
        }

        set_model(tree_store);
        show_all_children();
        expand_all();
    }
}

void RelatedList::set_selected_task(const TraceData::Event * event) {
    selected_event = event;
    update_model();
}

void RelatedList::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    (void)num_locs; //unused
    this->trace_data = trace_data;
    selected_event = nullptr;
    update_model();
}


bool RelatedList::select_function(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::Path& path, bool path_currently_selected) {
    const Gtk::TreeModel::iterator iter = model->get_iter(path);
    Gtk::TreeModel::Row row = *iter;
    if(row[columns.col_id] < 8) {
        return false;
    } else {
        return true;
    }
}

void RelatedList::on_selection_changed() {
    Gtk::TreeModel::iterator iter = get_selection()->get_selected();
    if(iter) {
        Gtk::TreeModel::Row row = *iter;
        Glib::ustring name = row[columns.col_name];
        std::string guid = name.raw();
        main_window->set_selected_related_guid(guid);
    } else {
        main_window->set_selected_related_guid("");
    }

}
