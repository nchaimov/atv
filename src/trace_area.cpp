#include "trace_area.hpp"
#include "main_window.hpp"
#include "colors.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

#include <cairomm/context.h>
#include <cairomm/surface.h>

#include <glibmm.h>
#include <gtkmm/builder.h>
#include <gtkmm/menu.h>
#include <giomm/menu.h>

TraceArea::TraceArea(MainWindow * main_window) : num_locs(0), trace_data(nullptr), main_window(main_window), menu(nullptr) {
    set_hexpand(true);
    set_vexpand(true);
    add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_MOTION_MASK 
            | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

TraceArea::~TraceArea() {

}

void TraceArea::set_create_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(1.0, 0.0, 0.0, 1.0);
}

void TraceArea::set_destroy_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgb(0.8, 0.8, 0.2);
}

void TraceArea::set_outgoing_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(0.0, 1.0, 0.0, 1.0);
}

void TraceArea::set_incoming_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(0.0, 1.0, 0.0, 1.0);
}

void TraceArea::set_acquire_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(0.4, 1.0, 0.0, 1.0);
}

void TraceArea::set_release_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(1.0, 0.0, 1.0, 1.0);
}

void TraceArea::set_runnable_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(0.0, 0.0, 1.0, 1.0);
}

void TraceArea::set_satisfy_color(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgba(0.5, 0.3, 0.9, 1.0);
}

void TraceArea::redraw(const bool should_scroll) {
    image_surface.clear();
    if(should_scroll) {
        main_window->set_scroll_allowed(zoom);
        const double page_size = zoom_stop - zoom_start;
        const double position = (zoom_start + zoom_stop) / 2.0;
        main_window->set_scroll_page_size(page_size);
        main_window->set_scroll_position(position, false);
    }
    queue_resize();
}

void TraceArea::unzoom() {
    zoom = false;
    zoom_start = 0.0;
    zoom_stop = trace_data->get_trace_length();
    redraw();
}

void TraceArea::zoom_in() {
    // Zoom in on center
    const double center = (zoom_start + zoom_stop) / 2.0;
    zoom_start = (zoom_start + center) / 2.0;
    zoom_stop = (center + zoom_stop) / 2.0;
    zoom = true;
    redraw();
}

void TraceArea::zoom_out() {
    if(zoom) {
        const double center = (zoom_start + zoom_stop) / 2.0;
        zoom_start = (2*zoom_start) - center;
        zoom_stop  = (2*zoom_stop) - center;
        if(zoom_start <= 0 || zoom_stop >= trace_data->get_trace_length()) {
            unzoom();
        } else {
            redraw();
        }
    }
}

uint64_t TraceArea::location_for_coord(double y) const {
    for(uint64_t loc = 0; loc < num_locs; ++loc) {
        const double top_of_row = (loc*height_per_loc) + ((loc-1.0)*spacing_between_locs)  + 10.0;
        const double bot_of_row = ((loc+1.0)*height_per_loc) + (loc*spacing_between_locs)  + 10.0;
        if(y >= top_of_row && y <= bot_of_row) {
            return loc;
        }
    }
    return TraceData::INVALID_LOCATION_REF;
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
        cr->move_to(zoom_start, y_pos);
        cr->line_to(zoom_stop + zoom_start,  y_pos);
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
        const auto & events = trace_data->get_events(loc);
        auto start_iterator = zoom ? trace_data->get_compute_event_at_time(loc, zoom_start+global_offset) : events.begin();
        auto stop_iterator = zoom ? trace_data->get_compute_event_at_time(loc, zoom_stop+global_offset) : events.end();
        // We want to go one back and one forward so that we draw an event
        // even if we are zoomed in so far that the start is before the
        // zoom region and the end is after the zoom region
        while(start_iterator != events.begin() && start_iterator->get_event_type() != TraceData::EventType::Enter) {
            start_iterator = std::prev(start_iterator, 1);
        }    
        while(stop_iterator != events.end() && stop_iterator->get_event_type() != TraceData::EventType::Leave) {
            stop_iterator = std::next(stop_iterator, 1);
        }
        if(stop_iterator != events.end()) {
            stop_iterator = std::next(stop_iterator, 1);
        }
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
                    int seq_id = event.get_seq_entry_id();
                    Colors::set_color(cr, seq_id);
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

void TraceArea::set_scale(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    double logical_height = (height_per_loc*num_locs) + ((spacing_between_locs)*(num_locs-1.0));
    double logical_width;
    if(zoom) {
        logical_width = zoom_stop - zoom_start;
    } else {
        logical_width = trace_data->get_trace_length();
    }

    // Scale so right of selected area is offscreen
    // logical zoom_stop == physical width
    const double x_scale = (double)width/logical_width;
    const double y_scale = (double)height/logical_height;
    cr->scale(x_scale, y_scale);
    // Move origin so left of selected area is offscreen
    // logical select_start == 0
    if(zoom) {
        cr->translate(-zoom_start, 0.0);
    }
}

void TraceArea::draw_into_local_surface() {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    image_surface = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, width, height);
    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(image_surface);

    cr->save();

    set_scale(cr);
    cr->get_matrix(matrix);
    matrix.invert();

    cr->set_source_rgb(1.0, 1.0, 1.0); // white background
    cr->set_antialias(Cairo::ANTIALIAS_NONE);
    cr->paint();

    if(mode == Mode::TaskExecution) {
        draw_separators(cr);
        draw_tasks(cr);
        if(!selected_related_guid.empty()) {
            draw_selected_guid_events(cr);
        }
    } else if(mode == Mode::Concurrency) {
        draw_concurrency(cr);
    }
    cr->restore();
}

void TraceArea::draw_concurrency(const Cairo::RefPtr<Cairo::Context>& cr) {
    // This doesn't work yet
#if 0
    uint64_t bins = (trace_data->get_trace_length() / trace_data->get_timer_resolution()) * 10;
    std::cerr << bins << std::endl;
    // divide into bins
    uint64_t bin_width = trace_data->get_trace_length() / bins;
    // get EDTs in each category 
    std::vector<double> created(bins);
    std::vector<double> eligible(bins);
    std::vector<double> running(bins);
    for(OTF2_LocationRef loc = 0; loc < num_locs; ++loc) {
        std::cerr << "Concurrency for loc " << loc << std::endl;
        const auto & compute_events = trace_data->get_compute_events(loc);
        const auto & other_events = trace_data->get_other_events(loc);
        auto compute_iter = compute_events.begin();
        auto other_iter = other_events.begin();
        int64_t bin_created = 0;
        int64_t bin_eligible = 0;
        int64_t bin_running = 0;
        bool compute_done = false;
        bool other_done = false;
        uint64_t current_bin = 0;
        OTF2_TimeStamp end_time = compute_iter->get_time() + bin_width;
        while(!compute_done || !other_done) {
            OTF2_TimeStamp current_time = 0;
            // Process compute events, if there are still any
            if(!compute_done) {
                switch(compute_iter->get_event_type()) {
                    case TraceData::EventType::Enter:
                        --bin_eligible;
                        ++bin_running;
                        break;
                    case TraceData::EventType::Leave:
                        --bin_running;
                        break;
                    default:
                        break;
                }
                current_time = compute_iter->get_time();
                ++compute_iter;
                if(compute_iter == compute_events.end()) {
                    compute_done = true;
                }
            }

            // Process other events, if there are still any
            if(!other_done) {
                switch(other_iter->get_event_type()) {
                    case TraceData::EventType::TaskCreate:
                        ++bin_created;
                        break;
                    case TraceData::EventType::TaskRunnable:
                        --bin_created;
                        ++bin_eligible;
                        break;
                    default:
                        break;
                }
                current_time = std::max(current_time, other_iter->get_time());
                ++other_iter;
                if(other_iter == other_events.end()) {
                    other_done = true;
                }
            }

            if(current_time >= end_time) {
                // End of a bin
                // Store results
                created[current_bin] += bin_created;
                eligible[current_bin] += bin_eligible;
                running[current_bin] += bin_running;
                end_time += bin_width;
                ++current_bin;
            }

        } // end while loop processing events

    } // end for loop processing locations

    std::cout << std::setw(12) << "Bin" << std::setw(12) << "Created" << std::setw(12) << "Eligible" << std::setw(12) << "Running" << std::endl; 
    for(uint64_t bin = 0; bin < bins; ++bin) {
        std::cout << std::setw(12) << bin;
        std::cout << std::setw(12) << created[bin];
        std::cout << std::setw(12) << eligible[bin];
        std::cout << std::setw(12) << running[bin];
        std::cout << std::endl; 
    }
#endif
} // end draw_concurrency


void TraceArea::draw_selection_rect(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int height = allocation.get_height();
    cr->save();
    cr->set_source_rgba(0.0,1.0,0.3,0.4);
    cr->rectangle(select_start, 0.0, select_stop-select_start, height);
    cr->fill();
    cr->restore();
}

void TraceArea::draw_selected_task(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    if(selected_event_start != nullptr && selected_event_end != nullptr) {
        set_scale(cr);
        const double top_of_row = (selected_loc*height_per_loc) + ((selected_loc-1.0)*spacing_between_locs)  + 10.0;
        uint64_t global_offset = trace_data->get_global_offset();
        const OTF2_TimeStamp enter = selected_event_start->get_time() - global_offset;      
        const OTF2_TimeStamp leave = selected_event_end->get_time() - global_offset;   
        const double rect_width = leave - enter;
        cr->set_source_rgba(1.0, 1.0, 1.0, 0.3);
        cr->rectangle(enter, top_of_row, rect_width, height_per_loc);
        cr->fill();
        cr->set_source_rgb(0.0, 1.0, 0.3);
        double unused = 0.0;
        double line_width = 2.0;
        cr->device_to_user_distance(unused, line_width);
        // convert desired line_width in pixels to user space
        cr->set_line_width(line_width);
        cr->rectangle(enter, top_of_row, rect_width, height_per_loc);
        cr->stroke();
        line_width = 2.0;
        cr->device_to_user_distance(line_width, unused);
        cr->rectangle(enter, top_of_row, line_width, height_per_loc);
        cr->fill();
        cr->rectangle(leave, top_of_row, line_width, height_per_loc);
        cr->fill();
        draw_selected_task_dependencies(cr);
    }
    cr->restore();
}


void TraceArea::draw_selected_task_dependencies(const Cairo::RefPtr<Cairo::Context>&cr) {
    if(selected_event_start == nullptr) {
        return;
    }
    const std::string guid = selected_event_start->get_object().get_guid();
    TraceData::event_ptr_list_t related_events(trace_data->get_events_for_guid(guid));
    std::sort(related_events.begin(), related_events.end(), TraceData::timestamp_ptr_compare());
    for(const auto event_ptr : related_events) {
        bool draw = false;
        cr->save();
        switch(event_ptr->get_event_type()) {
            case TraceData::EventType::TaskCreate: {
                set_create_color(cr);
                draw = true;
            };
            break;
            case TraceData::EventType::AddDependence: {
                if(event_ptr->get_object().get_guid() != selected_event_start->get_object().get_guid()) {
                    // Outgoing dependency
                    set_outgoing_color(cr);
                } else {
                    set_incoming_color(cr);
                }
                draw = true;
            };
            break;
            case TraceData::EventType::TaskRunnable: {
                set_runnable_color(cr);
                draw = true;
            };
            break;
            case TraceData::EventType::SatisfyDependence: {
                set_satisfy_color(cr);
                draw = true;
            };
            break;

            default:
            break;
        }
        if(draw) {
            // Draw from bottom of beginning of selected enter event to center of task create
            const uint64_t global_offset = trace_data->get_global_offset();
            const double enter_time = selected_event_start->get_time() - global_offset;
            const uint64_t enter_loc = selected_event_start->get_loc();
            const double enter_loc_pos = (enter_loc*height_per_loc) + ((enter_loc-1.0)*spacing_between_locs)  + 10.0 + (height_per_loc * 0.5);
            const double evt_time = event_ptr->get_time() - global_offset;
            const uint64_t evt_loc = event_ptr->get_loc();
            const double evt_loc_pos = (evt_loc*height_per_loc) + ((evt_loc-1.0)*spacing_between_locs)  + 10.0 + (height_per_loc * 0.5);
            cr->move_to(enter_time, enter_loc_pos);
            cr->line_to(evt_time, evt_loc_pos);
            cr->save();
            cr->set_identity_matrix();
            cr->set_line_width(1.0);
            cr->stroke();
            cr->restore();
        }
        cr->restore();
    }
}

void TraceArea::draw_selected_guid_events(const Cairo::RefPtr<Cairo::Context>&cr) {
    cr->save();
    TraceData::event_ptr_list_t related_events(trace_data->get_events_for_guid(selected_related_guid));
    std::sort(related_events.begin(), related_events.end(), TraceData::timestamp_ptr_compare());
    for(const auto event_ptr : related_events) {
        const uint64_t global_offset = trace_data->get_global_offset();
        const double evt_time = event_ptr->get_time() - global_offset;
        if(evt_time < zoom_start || evt_time > zoom_stop) {
            continue;
        }
        bool draw = false;
        cr->save();
        switch(event_ptr->get_event_type()) {
            case TraceData::EventType::TaskCreate:
            case TraceData::EventType::EventCreate:
            case TraceData::EventType::DataCreate: {
                set_create_color(cr);
                draw = true;
            };
            break;

            case TraceData::EventType::TaskDestroy:
            case TraceData::EventType::EventDestroy:
            case TraceData::EventType::DataDestroy: {
                set_destroy_color(cr);
                draw = true;
            };
            break;

            case TraceData::EventType::DataAcquire: {
                set_acquire_color(cr);
                draw = true;
            };
            break;

            case TraceData::EventType::DataRelease: {
                set_release_color(cr);
                draw = true;
            };
            break;

            case TraceData::EventType::AddDependence: {
                set_incoming_color(cr);
                draw = true;
            };
            break;

            case TraceData::EventType::SatisfyDependence: {
                set_satisfy_color(cr);
                draw = true;
            };                                            
            break;

            case TraceData::EventType::TaskRunnable: {
                set_runnable_color(cr);
                draw = true;
            };
            break;
            
            default:
            break;
        }
        if(draw) {
            const uint64_t evt_loc = event_ptr->get_loc();
            const double evt_loc_pos = (evt_loc*height_per_loc) + ((evt_loc-1.0)*spacing_between_locs)  + 10.0 + (height_per_loc * 0.4);
            const double evt_loc_pos_bot = (evt_loc*height_per_loc) + ((evt_loc-1.0)*spacing_between_locs)  + 10.0 + (height_per_loc * 0.6);
            cr->save();
            cr->move_to(evt_time, evt_loc_pos);
            cr->line_to(evt_time, evt_loc_pos_bot);
            cr->set_identity_matrix();
            cr->set_line_width(5.0);
            cr->stroke();
            cr->restore();
        }
        cr->restore();
    }
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
    if(mode == Mode::TaskExecution) {
        if(selecting) {
            draw_selection_rect(cr);
        }
        if(selected_event_start != nullptr) {
            draw_selected_task(cr);
        }
    }
    cr->restore();
    return false;
}

void TraceArea::on_new_data(uint64_t num_locs, TraceData * trace_data) {
    this->num_locs = num_locs;
    this->trace_data = trace_data;
    unzoom();
}
    
bool TraceArea::display_popup_menu(GdkEventButton* button_event) {
    double x = button_event->x;
    double y = button_event->y;
    matrix.transform_point(x, y);
    uint64_t loc = location_for_coord(y);
    std::string name = trace_data->get_task_name_at_time(loc, x + trace_data->get_global_offset());
    if(name.empty()) {
        return false;
    }
    std::stringstream ss;
    ss <<"<interface>"
         "  <menu id='event-popup'>"
         "    <section>"
         "      <item>"
         "        <attribute name='label' translatable='no'>" << name << "</attribute>"
         "      </item>"
         "    </section>"
         "  </menu>"; 
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    builder->add_from_string(ss.str());
    Glib::RefPtr<Glib::Object> object = builder->get_object("event-popup");
    Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if(menu != nullptr) {
        delete menu;
    }
    menu = new Gtk::Menu(gmenu);
    auto items = menu->get_children();
    Gtk::MenuItem * item = dynamic_cast<Gtk::MenuItem*>(items[0]);
    if(item) {
        item->set_sensitive(false);
    }
    menu->attach_to_widget(*this);
    menu->popup(button_event->button, button_event->time);
    return false;
}

bool TraceArea::on_button_press_event(GdkEventButton* button_event) {
    if(trace_data == nullptr) {
        return false; // Not ready yet
    }
    if(mode == Mode::TaskExecution && button_event->type == GDK_BUTTON_PRESS) {
        if(button_event->button == 1) { // left click = start zoom
            selecting = true;
            select_start = button_event->x;
            select_stop = button_event->x;
            queue_draw();
        } else if(button_event->button == 3) { // right click = popup menu
            return display_popup_menu(button_event);
        }
    }
    return false;
}

bool TraceArea::on_button_release_event(GdkEventButton* button_event) {
    if(trace_data == nullptr) {
        return false; // Not ready yet
    }
    if(mode == Mode::TaskExecution && button_event->type == GDK_BUTTON_RELEASE) {
        if(button_event->button == 1) {
            select_stop = button_event->x;
            selecting = false;
            if(select_start != select_stop) {
                if(select_start > select_stop) {
                    std::swap(select_start, select_stop);
                }
                double unused = 0.0; // transform_point needs a y coord
                matrix.transform_point(select_start, unused);
                matrix.transform_point(select_stop, unused);
                if((double)select_start / (double)select_stop < 0.9999) {
                    zoom_start = select_start;
                    zoom_stop = select_stop;
                    zoom = true;
                    redraw();
                }
            } else {
                // No dragging
                select_event_under_cursor(button_event->x, button_event->y);
            }
            queue_draw();
        }
    }
    return false;
}

bool TraceArea::on_motion_notify_event(GdkEventMotion* motion_event) {
    if(trace_data == nullptr) {
        return false; // Not ready yet
    }
    if(selecting) {
        select_stop = motion_event->x;
        queue_draw();
    } else if (mode == Mode::TaskExecution && !should_update_label){
        should_update_label = true;
        sigc::slot<void> update_label_slot = sigc::bind(sigc::mem_fun(*this, &TraceArea::set_task_label_for_coord), motion_event->x, motion_event->y);
        Glib::signal_timeout().connect_once(update_label_slot, 10);
    }
    return false;
}


void TraceArea::set_task_label_for_coord(double x, double y) {
    if(should_update_label) {
        matrix.transform_point(x, y);
        uint64_t loc = location_for_coord(y);
        if(loc < num_locs && x > 0 && x < trace_data->get_trace_length()) {
            const uint64_t time = x + trace_data->get_global_offset();
            std::string name = trace_data->get_task_name_at_time(loc, time, true, true, true);
            std::stringstream ss;
            ss << loc << ": " << name;
            main_window->set_task_label_text(ss.str());

            const double time_sec = (double)x / (double)trace_data->get_timer_resolution();
            ss.str(std::string());
            ss << std::fixed << std::setprecision(5) << time_sec; 
            main_window->set_time_label_text(ss.str());
        } else {
            main_window->set_task_label_text("");
            main_window->set_time_label_text("");
        }
        should_update_label = false;
    }
}


void TraceArea::select_event_under_cursor(double x, double y) {
    matrix.transform_point(x, y);
    uint64_t loc = location_for_coord(y);
    if(loc < num_locs && x > 0 && x < trace_data->get_trace_length()) {
        auto tasks = trace_data->get_task_at_time(loc, x + trace_data->get_global_offset());
        if(tasks) {
            selected_event_start = &(tasks->first);
            main_window->set_selected_event(selected_event_start);
            selected_event_end = &(tasks->second);
            selected_loc = loc;
        } else {
            selected_event_start = nullptr;
            selected_event_end = nullptr;
            selected_loc = TraceData::INVALID_LOCATION_REF;
        }
    }
}


void TraceArea::set_mode(TraceArea::Mode mode) { 
    if(this->mode != mode) {
        this->mode = mode;
        unzoom();
        main_window->set_task_label_text("");
    }
}


void TraceArea::set_position(const double position) {
    if(!zoom) {
        return;
    }
    const double page_size = zoom_stop - zoom_start;    
    const double offset = page_size / 2.0;
    zoom_start = position - offset;
    zoom_stop  = position + offset;
    redraw(false);
}


void TraceArea::set_selected_related_guid(const std::string & guid) {
    selected_related_guid = guid;
    redraw();
}

