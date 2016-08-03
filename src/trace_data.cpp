
#include <limits>
#include <iostream>
#include <otf2/otf2.h>
#include "trace_data.hpp"


TraceData::TraceData() :
    cur_loc(0),
    invalid_system_tree_node(this, 
            std::numeric_limits<OTF2_LocationRef>::max(),
            std::numeric_limits<OTF2_SystemTreeNodeRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            std::numeric_limits<OTF2_SystemTreeNodeRef>::max()),
    invalid_location_group(this,
            std::numeric_limits<OTF2_LocationRef>::max(),
            std::numeric_limits<OTF2_LocationGroupRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            OTF2_LOCATION_GROUP_TYPE_UNKNOWN,
            std::numeric_limits<OTF2_SystemTreeNodeRef>::max()),
    invalid_location(this,
            std::numeric_limits<OTF2_LocationRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            OTF2_LOCATION_TYPE_UNKNOWN,
            std::numeric_limits<uint64_t>::max(),
            std::numeric_limits<OTF2_LocationGroupRef>::max()),
    invalid_region(this,
            std::numeric_limits<OTF2_LocationRef>::max(),
            std::numeric_limits<OTF2_RegionRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            std::numeric_limits<OTF2_StringRef>::max(),
            OTF2_REGION_ROLE_UNKNOWN,
            OTF2_PARADIGM_UNKNOWN,
            OTF2_REGION_FLAG_NONE,
            std::numeric_limits<OTF2_StringRef>::max(),
            std::numeric_limits<uint32_t>::max(),
            std::numeric_limits<uint32_t>::max()) {
    
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
    const auto & map = nodes_map[loc_ref];
    const auto itr = map.find(node_ref);
    if(itr != map.end()) {
        return itr->second;
    }
    return invalid_system_tree_node;
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
        const TraceData::SystemTreeNode & parent_from_map = trace_data->find_system_tree_node(parent);
        parent_node = &parent_from_map;
    }
    return *parent_node;
}

void TraceData::put_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref, const OTF2_StringRef name, const OTF2_LocationGroupType type, const OTF2_SystemTreeNodeRef parent) {
    location_groups_map[loc_ref].emplace(std::piecewise_construct, std::forward_as_tuple(loc_group_ref), std::forward_as_tuple(this, loc_ref, loc_group_ref, name, type, parent));
}

const TraceData::LocationGroup & TraceData::get_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref) {
    const auto & map = location_groups_map[loc_ref];
    const auto itr = map.find(loc_group_ref);
    if(itr != map.end()) {
        return itr->second;
    }
    return invalid_location_group;
}

const TraceData::location_groups_map_t & TraceData::get_location_groups() {
    return location_groups_map;
}

const std::string & TraceData::Location::get_name() const {
    if(name_str == nullptr) {
        const std::string & name_from_map = trace_data->get_string(loc, name);
        name_str = &name_from_map;
    }
    return *name_str;
}

const TraceData::LocationGroup & TraceData::Location::get_parent() const {
    if(parent_node == nullptr) {
        const TraceData::LocationGroup & parent_from_map = trace_data->find_location_group(parent);
        parent_node = &parent_from_map;
    }
    return *parent_node;
}


void TraceData::put_location(const OTF2_LocationRef loc_ref, const OTF2_StringRef name, const OTF2_LocationType type, const uint64_t num_events, const OTF2_LocationGroupRef parent) {
    location_map.emplace(std::piecewise_construct, std::forward_as_tuple(loc_ref), std::forward_as_tuple(this, loc_ref, name, type, num_events, parent));
}

const TraceData::Location & TraceData::get_location(const OTF2_LocationRef loc_ref) {
    const auto itr = location_map.find(loc_ref);
    if(itr != location_map.end()) {
        return itr->second;
    }
    return invalid_location;
}

const TraceData::location_map_t & TraceData::get_locations() {
    return location_map;
}


const TraceData::SystemTreeNode & TraceData::find_system_tree_node(const OTF2_SystemTreeNodeRef node_ref) {
    for(const auto & loc_pair : nodes_map) {
        const auto & nodes = loc_pair.second;
        const auto node_itr = nodes.find(node_ref);
        if(node_itr != nodes.end()) {
            return node_itr->second;
        }
    }
    return invalid_system_tree_node;
}

const TraceData::LocationGroup & TraceData::find_location_group(const OTF2_LocationGroupRef loc_group_ref) {
    for(const auto & loc_pair : location_groups_map) {
        const auto & nodes = loc_pair.second;
        const auto node_itr = nodes.find(loc_group_ref);
        if(node_itr != nodes.end()) {
            return node_itr->second;
        }
    }
    return invalid_location_group;
}

const std::string & TraceData::Region::get_name() const {
    if(name_str == nullptr) {
        const std::string & name_from_map = trace_data->get_string(loc, name);
        name_str = &name_from_map;
    }
    return *name_str;
}

const std::string & TraceData::Region::get_guid() const {
    if(guid_str == nullptr) {
        const std::string & guid_from_map = trace_data->get_string(loc, guid);
        guid_str = &guid_from_map;
    }
    return *guid_str;
}

const std::string & TraceData::Region::get_desc() const {
    if(desc_str == nullptr) {
        const std::string & desc_from_map = trace_data->get_string(loc, desc);
        desc_str = &desc_from_map;
    }
    return *desc_str;
}

void TraceData::put_region(const OTF2_LocationRef loc_ref, const OTF2_RegionRef self, const OTF2_StringRef name, const OTF2_StringRef guid, const OTF2_StringRef desc, const OTF2_RegionRole role, const OTF2_Paradigm paradigm, const OTF2_RegionFlag region_flag, const OTF2_StringRef source_file, const uint32_t begin_line_number, const uint32_t end_line_number) {
    regions_map[loc_ref].emplace(std::piecewise_construct, std::forward_as_tuple(loc_ref), std::forward_as_tuple(this, loc_ref, self, name, guid, desc, role, paradigm, region_flag, source_file, begin_line_number, end_line_number));
}
    
const TraceData::Region & TraceData::get_region(const OTF2_LocationRef loc_ref, const OTF2_RegionRef region_ref) {
    const auto & map = regions_map[loc_ref];
    const auto itr = map.find(region_ref);
    if(itr != map.end()) {
        return itr->second;
    }
    return invalid_region;
}

const TraceData::regions_map_t & TraceData::get_regions() {
    return regions_map;
}

const TraceData::Region & TraceData::Event::get_object() const {
    if(object_region == nullptr) {
        const Region & object_from_map = trace_data->get_region(loc, object);
        object_region = &object_from_map;
    }
    return *object_region;
}

const TraceData::Region & TraceData::Event::get_subject() const {
    if(subject_region == nullptr) {
        const Region & subject_from_map = trace_data->get_region(loc, subject);
        subject_region = &subject_from_map;
    }
    return *subject_region;
}

void TraceData::put_event(const OTF2_LocationRef loc_ref, const EventType event_type, const OTF2_TimeStamp time, uint64_t event_position, const OTF2_RegionRef object, const OTF2_RegionRef subject, const uint64_t size) {
   events_map[loc_ref].emplace_back(this, loc_ref, event_type, time, event_position, object, subject, size); 
}

const TraceData::event_list_t & TraceData::get_events(const OTF2_LocationRef loc_ref) {
    return events_map[loc_ref];
}
