#include <set>
#include <sstream>
#include "related_list.hpp"

RelatedList::RelatedList() : Gtk::TreeView() {
    append_column("Name", columns.col_name);
    show_all_children();
}

RelatedList::~RelatedList() {
}

void RelatedList::update_model() {
    if(trace_data != nullptr) {
        tree_store = Gtk::TreeStore::create(columns);
        set_model(tree_store);
        
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
                            std::stringstream ss;
                            ss << db_guid << " size: " << event_ptr->get_size();
                            acquire_row[columns.col_name] = ss.str();
                        }
                    }
                    break;

                    case TraceData::EventType::DataCreate: {
                        std::string db_guid = event_ptr->get_object().get_guid();
                        if(block_creates_seen.count(db_guid) == 0) {
                            block_creates_seen.insert(db_guid);
                            Gtk::TreeModel::Row create_row = *(tree_store->append(data_created_row.children()));
                            create_row[columns.col_id] = next_id++;
                            std::stringstream ss;
                            ss << db_guid << " size: " << event_ptr->get_size();
                            create_row[columns.col_name] = ss.str();
                        }
                    }
                    break;

                    case TraceData::EventType::DataDestroy: {
                        std::string db_guid = event_ptr->get_subject().get_guid();
                        if(block_destroys_seen.count(db_guid) == 0) {
                            block_destroys_seen.insert(db_guid);
                            Gtk::TreeModel::Row destroy_row = *(tree_store->append(data_destroyed_row.children()));
                            destroy_row[columns.col_id] = next_id++;
                            std::stringstream ss;
                            ss << db_guid << " size: " << event_ptr->get_size();
                            destroy_row[columns.col_name] = ss.str();
                        }
                    }
                    break;

                    case TraceData::EventType::TaskCreate: {
                        std::string task_guid = event_ptr->get_object().get_guid();
                        if(event_ptr->get_parent().get_guid() != task_guid) {
                            break;
                        }
                        if(task_creates_seen.count(task_guid) == 0) {
                            task_creates_seen.insert(task_guid);
                            Gtk::TreeModel::Row create_row = *(tree_store->append(tasks_created_row.children()));
                            create_row[columns.col_id] = next_id++;
                            std::stringstream ss;
                            ss << task_guid << " " << event_ptr->get_object().get_name();
                            create_row[columns.col_name] = ss.str();
                        }
                    }
                    break;

                    case TraceData::EventType::TaskDestroy: {
                        std::string task_guid = event_ptr->get_object().get_guid();
                        if(event_ptr->get_parent().get_guid() != task_guid) {
                            break;
                        }
                        if(task_destroys_seen.count(task_guid) == 0) {
                            task_destroys_seen.insert(task_guid);
                            Gtk::TreeModel::Row destroy_row = *(tree_store->append(tasks_destroyed_row.children()));
                            destroy_row[columns.col_id] = next_id++;
                            std::stringstream ss;
                            ss << task_guid << " " << event_ptr->get_object().get_name();
                            destroy_row[columns.col_name] = ss.str();
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
    update_model();
}
