
#include <otf2/otf2.h>
#include "trace_data.hpp"


TraceData::TraceData() : cur_loc(0) {

}

TraceData::~TraceData() {

}

void TraceData::put_string(OTF2_LocationRef loc_ref, OTF2_StringRef str_ref, const std::string & str) {
   strings_map[loc_ref][str_ref] = str;
}

const std::string & TraceData::get_string(OTF2_LocationRef loc_ref, OTF2_StringRef str_ref) {
   return strings_map[loc_ref][str_ref];
}

OTF2_LocationRef TraceData::get_current_location() const {
    return cur_loc;
}

void TraceData::set_current_location(const OTF2_LocationRef loc) {
    cur_loc = loc;
}

void TraceData::put_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref, const OTF2_StringRef name, const OTF2_StringRef desc, const OTF2_SystemTreeNodeRef parent) {
    nodes_map[loc_ref].emplace(std::piecewise_construct, std::forward_as_tuple(node_ref), std::forward_as_tuple(this, loc_ref, node_ref, name, desc, parent));
}
    
const TraceData::SystemTreeNode & TraceData::get_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref) {
    return nodes_map[loc_ref].find(node_ref)->second;    
}

const TraceData::nodes_map_t & TraceData::get_system_tree_nodes() {
    return nodes_map;
}

const std::string & TraceData::SystemTreeNode::get_name() const {
    if(name_str == nullptr) {
        const std::string & name_from_map = trace_data->get_string(loc, name);
        name_str = &name_from_map;
    }
    return *name_str;
}

const std::string & TraceData::SystemTreeNode::get_desc() const {
    if(desc_str == nullptr) {
        const std::string & desc_from_map = trace_data->get_string(loc, desc);
        desc_str = &desc_from_map;
    }
    return *desc_str;
}

const std::string & TraceData::LocationGroup::get_name() const {
    if(name_str == nullptr) {
        const std::string & name_from_map = trace_data->get_string(loc, name);
        name_str = &name_from_map;
    }
    return *name_str;
};


const TraceData::SystemTreeNode & TraceData::LocationGroup::get_parent() const {
    if(parent_node == nullptr) {
        const TraceData::SystemTreeNode & parent_from_map = trace_data->get_system_tree_node(loc, parent);
        parent_node = &parent_from_map;
    }
    return *parent_node;
}

void TraceData::put_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref, const OTF2_StringRef name, const OTF2_LocationGroupType type, const OTF2_SystemTreeNodeRef parent) {
    location_groups_map[loc_ref].emplace(std::piecewise_construct, std::forward_as_tuple(loc_group_ref), std::forward_as_tuple(this, loc_ref, name, type, parent));
}

const TraceData::LocationGroup & TraceData::get_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref) {
    return location_groups_map[loc_ref].find(loc_group_ref)->second;
}

const TraceData::location_groups_map_t & TraceData::get_location_groups() {
    return location_groups_map;
}

