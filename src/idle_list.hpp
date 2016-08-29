#ifndef IDLE_LIST_HPP
#define IDLE_LIST_HPP

#include <gtkmm/treeview.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treestore.h>

#include "trace_data.hpp"
#include "idle_detector.hpp"

class MainWindow;

class IdleList : public Gtk::TreeView {

    protected:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:
        ModelColumns()
        { add(col_id); add(col_start); add(col_prop); };

        Gtk::TreeModelColumn<uint64_t> col_id;
        Gtk::TreeModelColumn<Glib::ustring> col_start;
        Gtk::TreeModelColumn<Glib::ustring> col_prop;
    };

    bool first = true;
    bool clicked = false;

    ModelColumns columns;
    Glib::RefPtr<Gtk::TreeStore> tree_store;
    const TraceData * trace_data;
    MainWindow * main_window;
    IdleDetector * idle_detector;

    void update_model();

    void on_selection_changed();
    void set_scroll_mode();
    virtual bool on_button_press_event(GdkEventButton* button_event) override;

    public:
    IdleList(MainWindow * main_window);
    virtual ~IdleList();

    void on_new_data(uint64_t num_locs, TraceData * trace_data);

};

#endif
