#ifndef RELATED_LIST_HPP
#define RELATED_LIST_HPP

#include "trace_data.hpp"
#include <gtkmm/treeview.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treestore.h>


class RelatedList : public Gtk::TreeView {

    protected:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:
        ModelColumns()
        { add(col_id); add(col_name); }

        Gtk::TreeModelColumn<int> col_id;
        Gtk::TreeModelColumn<Glib::ustring> col_name;
    };

    ModelColumns columns;
    Glib::RefPtr<Gtk::TreeStore> tree_store;
    const TraceData * trace_data;

    void update_model();
        

    public:
    RelatedList();
    virtual ~RelatedList();

    const TraceData::Event * selected_event;
    void set_selected_task(const TraceData::Event * event);

    void on_new_data(uint64_t num_locs, TraceData * trace_data);

};

#endif
