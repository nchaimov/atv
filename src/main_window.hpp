#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/separator.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/builder.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/label.h>
#include <gtkmm/combobox.h>
#include <gtkmm/paned.h>
#include <gtkmm/scrolledwindow.h>

#include "status.hpp"
#include "trace_reader.hpp"
#include "trace_data.hpp"
#include "callbacks.hpp"
#include "trace_area.hpp"
#include "related_list.hpp"


class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow(const std::string & filename, const TraceReader::locations_t & locations);
    virtual ~MainWindow();

    using new_data_signal_t = sigc::signal<void, uint64_t, TraceData*>;
    new_data_signal_t new_data_event() const;

    virtual void set_task_label_text(const Glib::ustring& str);
    virtual void set_selected_event(const TraceData::Event * event);

protected:
    Gtk::VBox box;
    Gtk::Paned pane;
    Gtk::ScrolledWindow scroll;
    Gtk::Separator sep;
    Gtk::ProgressBar load_progress;
    TraceArea trace_area;
    RelatedList related_list;
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Toolbar * top_bar;
    Gtk::Toolbar * bottom_bar;
    Gtk::Label * task_label;
    Gtk::ComboBox * combobox;

    new_data_signal_t new_data_signal;

    std::string filename;
    const TraceReader::locations_t locations;
    DefaultCallbacks callbacks;

    int last_width;
    int last_height;

    virtual bool setup_load_traces(GdkEventAny * event);
    virtual void setup_toolbar();
    virtual void load_traces();
    virtual void update_status(uint64_t num_locs);

    virtual bool on_configure_event(GdkEventConfigure* configure_event) override;
    virtual void on_view_changed();


    class ViewsComboBoxModel : public Gtk::TreeModelColumnRecord {
    public:
        
    ViewsComboBoxModel()
        { add(view_name); add(view_num); }
        
    Gtk::TreeModelColumn<Glib::ustring> view_name;
    Gtk::TreeModelColumn<int> view_num;
    };

    ViewsComboBoxModel columns;

    Glib::RefPtr<Gtk::ListStore> list_store;

};



#endif // MAIN_WINDOW_HPP
