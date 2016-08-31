
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <otf2/otf2.h>
#include "trace_data.hpp"
#include "utils.hpp"

TraceData::TraceData() :
    cur_loc(0),
    invalid_system_tree_node(this, 
            INVALID_LOCATION_REF,
            INVALID_SYSTEM_TREE_NODE_REF,
            INVALID_STRING_REF,
            INVALID_STRING_REF,
            INVALID_SYSTEM_TREE_NODE_REF),
    invalid_location_group(this,
            INVALID_LOCATION_REF,
            INVALID_LOCATION_GROUP_REF,
            INVALID_STRING_REF,
            OTF2_LOCATION_GROUP_TYPE_UNKNOWN,
            INVALID_SYSTEM_TREE_NODE_REF),
    invalid_location(this,
            INVALID_LOCATION_REF,
            INVALID_STRING_REF,
            OTF2_LOCATION_TYPE_UNKNOWN,
            INVALID_SIZE,
            INVALID_LOCATION_GROUP_REF),
    invalid_region(this,
            INVALID_LOCATION_REF,
            INVALID_REGION_REF,
            INVALID_STRING_REF,
            INVALID_STRING_REF,
            INVALID_STRING_REF,
            OTF2_REGION_ROLE_UNKNOWN,
            OTF2_PARADIGM_UNKNOWN,
            OTF2_REGION_FLAG_NONE,
            INVALID_STRING_REF,
            INVALID_LINE,
            INVALID_LINE),
    next_seq_id(0) {
}

TraceData::~TraceData() {

}

void TraceData::put_string(OTF2_LocationRef loc_ref, OTF2_StringRef str_ref, const std::string & str) {
   strings_map[loc_ref][str_ref] = str;
}

const std::string & TraceData::get_string(OTF2_LocationRef loc_ref, OTF2_StringRef str_ref) {
    static std::string invalid_str("INVALID"); 
    constexpr OTF2_StringRef invalid_str_ref = INVALID_STRING_REF;
    if(str_ref == invalid_str_ref) {
        return invalid_str;
    }
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

const TraceData::nodes_map_t & TraceData::get_system_tree_nodes() const {
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

const TraceData::location_groups_map_t & TraceData::get_location_groups() const {
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
    events_map[loc_ref].reserve(num_events);
    location_ref_list.emplace_back(loc_ref);
    location_ref_to_id_map.emplace(loc_ref, next_location_ref_id++);
}

const TraceData::Location & TraceData::get_location(const OTF2_LocationRef loc_ref) {
    const auto itr = location_map.find(loc_ref);
    if(itr != location_map.end()) {
        return itr->second;
    }
    return invalid_location;
}

const TraceData::location_map_t & TraceData::get_locations() const {
    return location_map;
}

const TraceData::location_ref_list_t & TraceData::get_location_refs() const {
    return location_ref_list;
}

OTF2_LocationRef TraceData::get_location_ref(TraceData::location_ref_list_t::size_type offset) const {
    if(!(offset < location_ref_list.size())) {
        return INVALID_LOCATION_REF;
    }
    return location_ref_list[offset];
}

uint64_t TraceData::get_location_offset(OTF2_LocationRef loc_ref) const {
    const auto itr = location_ref_to_id_map.find(loc_ref);
    if(itr != location_ref_to_id_map.end()) {
        return itr->second;
    }
    return INVALID_SIZE;
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

const TraceData::Location & TraceData::Region::get_location() const {
    if(location == nullptr) {
        const Location & my_location = trace_data->get_location(loc);
        location = &my_location;
    }
    return *location;
}

void TraceData::put_region(const OTF2_LocationRef loc_ref, const OTF2_RegionRef self, const OTF2_StringRef name, const OTF2_StringRef guid, const OTF2_StringRef desc, const OTF2_RegionRole role, const OTF2_Paradigm paradigm, const OTF2_RegionFlag region_flag, const OTF2_StringRef source_file, const uint32_t begin_line_number, const uint32_t end_line_number) {
    regions_map[loc_ref].emplace(std::piecewise_construct, std::forward_as_tuple(self), std::forward_as_tuple(this, loc_ref, self, name, guid, desc, role, paradigm, region_flag, source_file, begin_line_number, end_line_number));
}
    
const TraceData::Region & TraceData::get_region(const OTF2_LocationRef loc_ref, const OTF2_RegionRef region_ref) {
    const auto & map = regions_map[loc_ref];
    const auto itr = map.find(region_ref);
    if(itr != map.end()) {
        return itr->second;
    }
    return invalid_region;
}

const TraceData::regions_map_t & TraceData::get_regions() const {
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

const TraceData::Region & TraceData::Event::get_parent() const {
    if(parent_region == nullptr) {
        const Region & parent_from_map = trace_data->get_region(loc, parent);
        parent_region = &parent_from_map;
    }
    return *parent_region;
}

const TraceData::Location & TraceData::Event::get_location() const {
    if(location == nullptr) {
        const Location & my_location = trace_data->get_location(loc);
        location = &my_location;
    }
    return *location;
}

void TraceData::put_event(const OTF2_LocationRef loc_ref, const EventType event_type, const OTF2_TimeStamp time, uint64_t event_position, const OTF2_RegionRef object, const OTF2_RegionRef subject, const uint64_t size) {
    put_event(loc_ref, event_type, time, event_position, object, subject, get_last_entered(loc_ref), size);
}

void TraceData::put_event(const OTF2_LocationRef loc_ref, const EventType event_type, const OTF2_TimeStamp time, uint64_t event_position, const OTF2_RegionRef object, const OTF2_RegionRef subject, const OTF2_RegionRef parent, const uint64_t size) {
    Event * event;
    auto & vect = events_map[loc_ref];
    int seq_id = -1;
    if(event_type == TraceData::EventType::Enter || event_type == TraceData::EventType::Leave) {
        seq_id = get_seq_id(get_region(loc_ref, object).get_name());
    }
    vect.emplace_back(this, loc_ref, event_type, time, event_position, object, subject, parent, size, seq_id); 
    event = &(vect.back());

    if(limit_events) {
        if(guid_map_event_types.find(event_type) == guid_map_event_types.end()) {
            return;
        }
    }

    if(object != INVALID_REGION_REF) {
        const std::string & object_guid = event->get_object().get_guid();
        guid_map[object_guid].emplace_back(event);
        switch(event_type) {
            case TraceData::EventType::TaskCreate:
                guid_type_map[object_guid] = TraceData::GuidType::Task;
                break;
            case TraceData::EventType::EventCreate:
                guid_type_map[object_guid] = TraceData::GuidType::Event;
                break;
            case TraceData::EventType::DataCreate:
                guid_type_map[object_guid] = TraceData::GuidType::Datablock;
            default:
                break;
        }
    }

    if(subject != INVALID_REGION_REF && object != subject) {
        const std::string & subject_guid = event->get_subject().get_guid();
        guid_map[subject_guid].emplace_back(event);
    }

    if(parent != INVALID_REGION_REF && parent != object && parent != subject) {
        const std::string & parent_guid = event->get_parent().get_guid();
        guid_map[parent_guid].emplace_back(event); 
    }
}

const TraceData::event_list_t & TraceData::get_events(const OTF2_LocationRef loc_ref) {
    return events_map[loc_ref];
}

int TraceData::get_seq_id(const std::string & name) {
    const auto itr = name_map.find(name);
    if(itr != name_map.end()) {
        return itr->second;    
    } else {
        const int new_id = next_seq_id++;
        name_map[name] = new_id;
        return new_id;
    }
}

TraceData::event_list_t::const_iterator TraceData::get_compute_event_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time) {
    TraceData::Event target(this, loc_ref, TraceData::EventType::Artificial, time, 0, INVALID_REGION_REF, INVALID_REGION_REF, INVALID_REGION_REF, INVALID_SIZE, 0);
    const auto & vect = events_map[loc_ref];
    auto begin = vect.begin();
    auto end = vect.end();
    TraceData::event_list_t::const_iterator iter = std::lower_bound(begin, end, target, timestamp_compare());
    while(iter != begin) {
        if(iter != end) {
            switch(iter->get_event_type()) {
                case TraceData::EventType::Enter:
                case TraceData::EventType::Leave:
                    return iter;
                    break;
                default:
                    break;
            }
        }
        iter = std::prev(iter, 1);
    }
    return iter;

}


TraceData::event_list_t::const_iterator TraceData::get_next_compute_event(const OTF2_LocationRef loc_ref, TraceData::event_list_t::const_iterator iter) {
    const auto & vect = events_map[loc_ref];
    auto end = vect.end();
    while(iter != end) {
        iter = std::next(iter, 1);
        switch(iter->get_event_type()) {
            case TraceData::EventType::Enter:
            case TraceData::EventType::Leave:
                return iter;
                break;
            default:
                break;
        }
    }
    return iter;
}

TraceData::event_list_t::const_iterator TraceData::get_prev_compute_event(const OTF2_LocationRef loc_ref, TraceData::event_list_t::const_iterator iter) {
    const auto & vect = events_map[loc_ref];
    auto begin = vect.begin();
    while(iter != begin) {
        iter = std::prev(iter, 1);
        switch(iter->get_event_type()) {
            case TraceData::EventType::Enter:
            case TraceData::EventType::Leave:
                return iter;
                break;
            default:
                break;
        }
    }
    return iter;
}


TraceData::maybe_event_iter_pair_t TraceData::get_task_iter_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time, const bool or_before) {
    auto it = get_compute_event_at_time(loc_ref, time);
    TraceData::event_list_t::const_iterator enter_it;
    TraceData::event_list_t::const_iterator leave_it;
    if(it->get_event_type() == TraceData::EventType::Enter) {
        enter_it = it;
        leave_it = std::next(it, 1);
        while(leave_it->get_event_type() != TraceData::EventType::Leave) {
            leave_it = std::next(leave_it, 1);
        }
    } else if(it->get_event_type() == TraceData::EventType::Leave) {
        enter_it = std::prev(it, 1);
        while(enter_it->get_event_type() != TraceData::EventType::Enter) {
            enter_it = std::prev(enter_it, 1);
        }
        leave_it = it;
    } else {
        return boost::none;
    }
    // Make sure that the event is active during the time
    if(!or_before && (enter_it->get_time() > time || leave_it->get_time() < time)) {
        return boost::none;
    } 
    return event_iter_pair_t(enter_it, leave_it);
}

TraceData::maybe_event_pair_t TraceData::get_task_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time) {
    TraceData::maybe_event_iter_pair_t p = get_task_iter_at_time(loc_ref, time);
    if(p) {
        return event_pair_t(*(p->first), *(p->second));        
    }
    return boost::none;
}

std::string TraceData::get_task_name_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time, bool also_guid, bool markup, bool also_time) {
    auto events = get_task_at_time(loc_ref, time);
    std::stringstream ss;
    if(events) {
        if(markup) {
            ss << "<b>";
        }
        ss << events->first.get_object().get_name();
        if(markup) {
            ss << "</b>";
        }
        if(also_guid) {
            ss << " " << events->first.get_object().get_guid();
        }
        if(also_time) {
            const uint64_t task_start = events->first.get_time() - get_global_offset();
            const uint64_t task_end = events->second.get_time() - get_global_offset();
            const double start_secs = (double)task_start / (double)get_timer_resolution();
            const double end_secs = (double)task_end / (double)get_timer_resolution();
            ss << " " << std::fixed << std::setprecision(5) << start_secs << " -> " << std::fixed << std::setprecision(5) << end_secs;
        }
    }
    return ss.str();
}

const TraceData::event_ptr_list_t & TraceData::get_events_for_guid(const std::string & guid) const {
    return guid_map[guid];
}

TraceData::GuidType TraceData::get_type_for_guid(const std::string & guid) {
    auto iter = guid_type_map.find(guid);
    if(iter != guid_type_map.end()) {
        return iter->second;
    } else {
        return TraceData::GuidType::Unknown;
    }
}

OTF2_RegionRef TraceData::get_last_entered(OTF2_LocationRef loc_ref) {
    const auto itr = last_entered_map.find(loc_ref);
    if(itr != last_entered_map.end()) {
        return itr->second;
    }
    return TraceData::INVALID_REGION_REF;
}

void TraceData::set_last_entered(OTF2_LocationRef loc_ref, OTF2_RegionRef region) {
    last_entered_map[loc_ref] = region;
}


void TraceData::set_selective_guid_map_events(std::initializer_list<TraceData::EventType> event_types) {
    guid_map_event_types.clear();
    if(event_types.size() == 0) {
        limit_events = false;
    } else {
        guid_map_event_types.insert(event_types);
        limit_events = true;
    }
}

