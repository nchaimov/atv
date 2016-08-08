#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/hvbox.h>
#include <gtkmm/button.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/separator.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/builder.h>

#include "status.hpp"
#include "trace_reader.hpp"
#include "trace_data.hpp"
#include "callbacks.hpp"
#include "trace_area.hpp"


class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow(const std::string & filename, const TraceReader::locations_t & locations);
    virtual ~MainWindow();

    using new_data_signal_t = sigc::signal<void, uint64_t, TraceData*>;
    new_data_signal_t new_data_event() const;

protected:
    Gtk::VBox box;
    Gtk::Separator sep;
    Gtk::ProgressBar load_progress;
    TraceArea trace_area;
    Glib::RefPtr<Gtk::Builder> builder;


    new_data_signal_t new_data_signal;

    std::string filename;
    const TraceReader::locations_t locations;
    DefaultCallbacks callbacks;

    int last_width;
    int last_height;

    bool setup_load_traces(GdkEventAny * event);
    void setup_toolbar();
    void load_traces();
    void update_status(uint64_t num_locs);

    virtual bool on_configure_event(GdkEventConfigure* configure_event) override;

};



#endif // MAIN_WINDOW_HPP
