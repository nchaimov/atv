#ifndef TRACE_DATA_HPP
#define TRACE_DATA_HPP

#include <otf2/otf2.h>
#include <unordered_map>
#include <map>
#include <vector>
#include <limits>
#include <boost/optional.hpp>
#include <utility>
#include <sstream>
#include <iomanip>
#include <set>
#include <initializer_list>

class TraceData {
public:
    class SystemTreeNode {
        TraceData * trace_data;

        const OTF2_LocationRef loc;
        const OTF2_SystemTreeNodeRef self;
        const OTF2_StringRef name;
        const OTF2_StringRef desc;
        const OTF2_SystemTreeNodeRef parent;

        mutable std::string const * name_str;
        mutable std::string const * desc_str;

        public:
        SystemTreeNode(const SystemTreeNode& mE)            = default;
        SystemTreeNode(SystemTreeNode&& mE)                 = default;
        SystemTreeNode& operator=(const SystemTreeNode& mE) = default;
        SystemTreeNode& operator=(SystemTreeNode&& mE)      = default;

        SystemTreeNode(TraceData * trace_data, const OTF2_LocationRef loc, const OTF2_SystemTreeNodeRef self, const OTF2_StringRef name, const OTF2_StringRef desc, const OTF2_SystemTreeNodeRef parent) : trace_data(trace_data), loc(loc), self(self), name(name), desc(desc), parent(parent), name_str(nullptr), desc_str(nullptr) {};

        OTF2_SystemTreeNodeRef get_self() const { return self; };
        OTF2_StringRef get_name_ref() const { return name; };
        OTF2_StringRef get_desc_ref() const { return desc; };
        OTF2_SystemTreeNodeRef get_parent_ref() const { return parent; };
        OTF2_LocationRef get_loc() const { return loc; };

        const std::string & get_name() const;
        const std::string & get_desc() const;
            
    };

    class LocationGroup {
        TraceData * trace_data;

        const OTF2_LocationRef loc;
        const OTF2_LocationGroupRef self;
        const OTF2_StringRef name;
        const OTF2_LocationGroupType type;
        const OTF2_SystemTreeNodeRef parent;

        mutable std::string const * name_str;
        mutable SystemTreeNode const * parent_node;

        public:
        LocationGroup(const LocationGroup& mE)            = default;
        LocationGroup(LocationGroup&& mE)                 = default;
        LocationGroup& operator=(const LocationGroup& mE) = default;
        LocationGroup& operator=(LocationGroup&& mE)      = default;

        LocationGroup(TraceData * trace_data, const OTF2_LocationRef loc, const OTF2_LocationGroupRef self, const OTF2_StringRef name, const OTF2_LocationGroupType type, OTF2_SystemTreeNodeRef parent) : trace_data(trace_data), loc(loc), self(self), name(name), type(type), parent(parent), name_str(nullptr), parent_node(nullptr) {};

        OTF2_LocationGroupRef get_self() const { return self; };
        OTF2_StringRef get_name_ref() const { return name; };
        OTF2_LocationGroupType get_type() const { return type; };
        OTF2_LocationGroupRef get_parent_ref() const { return parent; };
        OTF2_LocationRef get_loc() const { return loc; };

        const std::string & get_name() const;
        const TraceData::SystemTreeNode & get_parent() const;
            
    };

    class Location {
        TraceData * trace_data;

        const OTF2_LocationRef loc;
        const OTF2_StringRef name;
        const OTF2_LocationType type;
        uint64_t num_events;
        const OTF2_LocationGroupRef parent;

        mutable std::string const * name_str;
        mutable LocationGroup const * parent_node;

        public:
        Location(const Location& mE)            = default;
        Location(Location&& mE)                 = default;
        Location& operator=(const Location& mE) = default;
        Location& operator=(Location&& mE)      = default;

        Location(TraceData * trace_data, const OTF2_LocationRef loc, const OTF2_StringRef name, const OTF2_LocationType type, uint64_t num_events, OTF2_LocationGroupRef parent) : trace_data(trace_data), loc(loc), name(name), type(type), num_events(num_events), parent(parent), name_str(nullptr), parent_node(nullptr) {};

        OTF2_StringRef get_name_ref() const { return name; };
        OTF2_LocationType get_type() const { return type; };
        uint64_t get_num_events() const { return num_events; };
        OTF2_LocationGroupRef get_parent_ref() const { return parent; };
        OTF2_LocationRef get_loc() const { return loc; };

        const std::string & get_name() const;
        const TraceData::LocationGroup & get_parent() const;
            
    };

    class Region {
        TraceData * trace_data;

        const OTF2_LocationRef loc;
        const OTF2_RegionRef self;
        const OTF2_StringRef name;
        const OTF2_StringRef guid;
        const OTF2_StringRef desc;
        const OTF2_RegionRole role;
        const OTF2_Paradigm paradigm;
        const OTF2_RegionFlag region_flag;
        const OTF2_StringRef source_file;
        const uint32_t begin_line_number;
        const uint32_t end_line_number;

        mutable std::string const * name_str;
        mutable std::string const * guid_str;
        mutable std::string const * desc_str;
        mutable Location const * location;

        public:
        Region(const Region& mE)            = default;
        Region(Region&& mE)                 = default;
        Region& operator=(const Region& mE) = default;
        Region& operator=(Region&& mE)      = default;

        Region( TraceData * trace_data,
                const OTF2_LocationRef loc,
                const OTF2_RegionRef self,
                const OTF2_StringRef name,
                const OTF2_StringRef guid,
                const OTF2_StringRef desc,
                const OTF2_RegionRole role,
                const OTF2_Paradigm paradigm,
                const OTF2_RegionFlag region_flag,
                const OTF2_StringRef source_file,
                const uint32_t begin_line_number,
                const uint32_t end_line_number)
          : trace_data(trace_data),
            loc(loc),
            self(self),
            name(name),
            guid(guid),
            desc(desc),
            role(role),
            paradigm(paradigm),
            region_flag(region_flag),
            source_file(source_file),
            begin_line_number(begin_line_number),
            end_line_number(end_line_number),
            name_str(nullptr),
            guid_str(nullptr),
            desc_str(nullptr) {};

        OTF2_LocationRef get_loc() const { return loc; };
        OTF2_RegionRef get_self() const { return self; };
        OTF2_StringRef get_name_ref() const { return name; };
        OTF2_StringRef get_guid_ref() const { return name; };
        OTF2_StringRef get_desc_ref() const { return name; };
        OTF2_RegionRole get_role() const { return role; };
        OTF2_Paradigm get_paradigm() const { return paradigm; };
        OTF2_RegionFlag get_region_flag() const { return region_flag; };
        OTF2_StringRef get_source_file_ref() const { return source_file; };
        uint32_t get_begin_line_number() const { return begin_line_number; };
        uint32_t get_end_line_number() const { return end_line_number; };

        const std::string & get_name() const;
        const std::string & get_guid() const;
        const std::string & get_desc() const;
        const Location & get_location() const;

        std::string to_string() const {
            std::stringstream ss;
            ss << "(";
            if(get_self() != INVALID_REGION_REF) {
                ss << get_self() << " ";
                if(get_name_ref() != INVALID_STRING_REF && !get_name().empty()) {
                    ss << get_name() << " ";
                }
                if(get_guid_ref() != INVALID_STRING_REF) {
                    std::string guid = get_guid();
                    std::string type = TraceData::guid_type_to_str(trace_data->get_type_for_guid(guid));
                    ss << type << " " << guid;
                }               
            }
            ss << ")";
            return ss.str();
        }
            
    };

    enum class EventType {
        MeasurementOn,
        MeasurementOff,
        Enter,
        Leave,
        TaskCreate,
        TaskDestroy,
        TaskRunnable,
        AddDependence,
        SatisfyDependence,
        DataAcquire,
        DataRelease,
        EventCreate,
        EventDestroy,
        DataCreate,
        DataDestroy,
        Artificial,
        Unknown
    };

    class Event {
        TraceData * trace_data;

        const OTF2_LocationRef loc;
        const EventType event_type;
        const OTF2_TimeStamp time;
        const uint64_t event_position;
        const OTF2_RegionRef object;
        const OTF2_RegionRef subject;
        const OTF2_RegionRef parent;
        const uint64_t size;

        mutable Region const * object_region;
        mutable Region const * subject_region;
        mutable Region const * parent_region;
        mutable Location const * location;
        const int seq_entry_id;

        public:
        Event(const Event& mE)            = default;
        Event(Event&& mE)                 = default;
        Event& operator=(const Event& mE) = default;
        Event& operator=(Event&& mE)      = default;

        Event( TraceData * trace_data,
                const OTF2_LocationRef loc,
                const EventType event_type,
                const OTF2_TimeStamp time,
                uint64_t event_position,
                const OTF2_RegionRef object,
                const OTF2_RegionRef subject,
                const OTF2_RegionRef parent,
                const uint64_t size,
                const int seq_entry_id)
          : trace_data(trace_data),
            loc(loc),
            event_type(event_type),
            time(time),
            event_position(event_position),
            object(object),
            subject(subject),
            parent(parent),
            size(size),
            object_region(nullptr),
            subject_region(nullptr),
            parent_region(nullptr),
            seq_entry_id(seq_entry_id) {};

        OTF2_LocationRef get_loc() const { return loc; };
        EventType get_event_type() const { return event_type; };
        std::string get_event_type_str() const {
            switch(get_event_type()) {
                case EventType::MeasurementOn:       return "MeasurementOn";
                case EventType::MeasurementOff:      return "MeasurementOff";
                case EventType::Enter:               return "Enter";
                case EventType::Leave:               return "Leave";
                case EventType::TaskCreate:          return "TaskCreate";
                case EventType::TaskDestroy:         return "TaskDestroy";
                case EventType::TaskRunnable:        return "TaskRunnable";
                case EventType::AddDependence:       return "AddDependence";
                case EventType::SatisfyDependence:   return "SatisfyDependence";
                case EventType::DataAcquire:         return "DataAcquire";
                case EventType::DataRelease:         return "DataRelease";
                case EventType::EventCreate:         return "EventCreate";
                case EventType::EventDestroy:        return "EventDestroy";
                case EventType::DataCreate:          return "DataCreate";
                case EventType::DataDestroy:         return "DataDestroy";
                case EventType::Artificial:          return "Artificial";
                case EventType::Unknown:             return "Unknown";
            }
            return "Invalid event type";
        };
        OTF2_TimeStamp get_time() const { return time; };
        double get_seconds() const { return (double)get_time() / (double)trace_data->get_timer_resolution(); };
        uint64_t get_event_position() const { return event_position; };
        OTF2_RegionRef get_object_ref() const { return object; };
        OTF2_RegionRef get_subject_ref() const { return subject; };
        OTF2_RegionRef get_parent_ref() const { return parent; };
        uint64_t get_size() const { return size; };
        int get_seq_entry_id() const { return seq_entry_id; };

        const Location & get_location() const;
        const Region & get_object() const;
        const Region & get_subject() const;
        const Region & get_parent() const;

        std::string to_string() const {
            std::stringstream ss;
            ss << std::setw(5) << get_loc() << " ";
            ss << std::setw(10) << get_time() << " ";
            ss << std::setw(10) << get_event_position() << " ";
            ss << std::left << std::setw(18) << get_event_type_str() << " ";
            ss << std::left << std::setw(45) << get_object().to_string() << " ";
            ss << std::left << std::setw(45) << get_subject().to_string() << " ";
            return ss.str();
        }

        std::string to_unformatted_string() const {
            std::stringstream ss;
            ss << get_loc() << " ";
            ss << get_time() << " ";
            ss << get_event_position() << " ";
            ss << get_event_type_str() << " ";
            ss << get_object().to_string() << " ";
            ss << get_subject().to_string() << " ";
            return ss.str();
        }
            
    };

    enum class GuidType {
        Task,
        Event,
        Datablock,
        Unknown
    };

    static std::string guid_type_to_str(GuidType gt) {
        switch(gt) {
            case GuidType::Task:      return "Task";
            case GuidType::Event:     return "Event";
            case GuidType::Datablock: return "Datablock";
            case GuidType::Unknown:   return "Unknown";
        }
        return "Invalid GUID Type";
    };


public:

    struct timestamp_compare {
        bool operator()(const TraceData::Event & left, const TraceData::Event & right) {
            return left.get_time() < right.get_time();
        };
    };

    struct timestamp_ptr_compare {
        bool operator()(const TraceData::Event * left, const TraceData::Event * right) {
            return left->get_time() < right->get_time();
        };
    };

    OTF2_LocationRef cur_loc;

    using string_map_t  = std::unordered_map<OTF2_StringRef, std::string>;
    using strings_map_t = std::map<OTF2_LocationRef, string_map_t>;
    strings_map_t strings_map;

    using node_map_t    = std::map<OTF2_SystemTreeNodeRef, SystemTreeNode>;
    using nodes_map_t   = std::map<OTF2_LocationRef, node_map_t>;
    nodes_map_t   nodes_map;
    SystemTreeNode invalid_system_tree_node;

    using location_group_map_t  = std::map<OTF2_LocationGroupRef, LocationGroup>;
    using location_groups_map_t = std::map<OTF2_LocationRef, location_group_map_t>;
    location_groups_map_t location_groups_map;
    LocationGroup invalid_location_group;

    using location_map_t = std::map<OTF2_LocationRef, Location>;
    location_map_t location_map;
    Location invalid_location;

    using location_ref_list_t = std::vector<OTF2_LocationRef>;
    location_ref_list_t location_ref_list;
    using location_ref_to_id_map_t = std::map<OTF2_LocationRef, uint64_t>;
    location_ref_to_id_map_t location_ref_to_id_map;
    uint64_t next_location_ref_id = 0; 

    using region_map_t = std::unordered_map<OTF2_RegionRef, Region>;
    using regions_map_t = std::map<OTF2_LocationRef, region_map_t>;
    regions_map_t regions_map;
    Region invalid_region;

    using event_list_t = std::vector<Event>;
    using events_map_t = std::map<OTF2_LocationRef, event_list_t>;
    events_map_t events_map;

    uint64_t timer_resolution;
    uint64_t global_offset;
    uint64_t trace_length;

    int next_seq_id;
    using name_map_t = std::map<std::string, int>;
    name_map_t name_map;

    using event_pair_t = std::pair<const Event&, const Event&>;
    using maybe_event_pair_t = const boost::optional<const event_pair_t>;

    using event_iter_pair_t = std::pair<event_list_t::const_iterator, event_list_t::const_iterator>;
    using maybe_event_iter_pair_t = const boost::optional<const event_iter_pair_t>;

    using event_ptr_list_t = std::vector<const Event *>;
    using guid_map_t = std::unordered_map<std::string,event_ptr_list_t>;
    mutable guid_map_t guid_map;

    using guid_type_map_t = std::unordered_map<std::string,GuidType>;
    guid_type_map_t guid_type_map;

    std::map<OTF2_LocationRef, OTF2_RegionRef> last_entered_map;

    bool limit_events = false;
    std::set<EventType> guid_map_event_types;

public:

    static constexpr OTF2_LocationRef INVALID_LOCATION_REF = std::numeric_limits<OTF2_LocationRef>::max();
    static constexpr OTF2_SystemTreeNodeRef INVALID_SYSTEM_TREE_NODE_REF = std::numeric_limits<OTF2_SystemTreeNodeRef>::max();
    static constexpr OTF2_StringRef INVALID_STRING_REF = std::numeric_limits<OTF2_StringRef>::max();
    static constexpr OTF2_LocationGroupRef INVALID_LOCATION_GROUP_REF = std::numeric_limits<OTF2_LocationGroupRef>::max();
    static constexpr OTF2_RegionRef INVALID_REGION_REF = std::numeric_limits<OTF2_RegionRef>::max();
    static constexpr uint64_t INVALID_SIZE = std::numeric_limits<uint64_t>::max();
    static constexpr uint64_t INVALID_TIME = std::numeric_limits<uint64_t>::max();
    static constexpr uint32_t INVALID_LINE = std::numeric_limits<uint32_t>::max();

    TraceData();
    virtual ~TraceData();

    void put_string(const OTF2_LocationRef loc_ref, const OTF2_StringRef str_ref, const std::string & str);
    const std::string & get_string(const OTF2_LocationRef loc_ref, const OTF2_StringRef str_ref);

    void set_current_location(const OTF2_LocationRef loc);
    OTF2_LocationRef get_current_location() const;

    void put_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref, const OTF2_StringRef name, const OTF2_StringRef desc, const OTF2_SystemTreeNodeRef parent);
    const SystemTreeNode & get_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref);
    const SystemTreeNode & find_system_tree_node(const OTF2_SystemTreeNodeRef node_ref);
    const nodes_map_t & get_system_tree_nodes() const;

    void put_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref, const OTF2_StringRef name, const OTF2_LocationGroupType type, const OTF2_SystemTreeNodeRef parent);
    const LocationGroup & get_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref);
    const LocationGroup & find_location_group(const OTF2_LocationGroupRef loc_group_ref);
    const location_groups_map_t & get_location_groups() const;

    void put_location(const OTF2_LocationRef loc_ref, const OTF2_StringRef name, const OTF2_LocationType type, const uint64_t num_events, const OTF2_LocationGroupRef parent);
    const Location & get_location(const OTF2_LocationRef loc_ref);
    const location_map_t & get_locations() const;
    const location_ref_list_t & get_location_refs() const;
    OTF2_LocationRef get_location_ref(location_ref_list_t::size_type offset) const;
    uint64_t get_location_offset(OTF2_LocationRef loc_ref) const;

    void put_region(const OTF2_LocationRef loc, const OTF2_RegionRef self, const OTF2_StringRef name, const OTF2_StringRef guid, const OTF2_StringRef desc, const OTF2_RegionRole role, const OTF2_Paradigm paradigm, const OTF2_RegionFlag region_flag, const OTF2_StringRef source_file, const uint32_t begin_line_number, const uint32_t end_line_number);
    const Region & get_region(const OTF2_LocationRef loc_ref, const OTF2_RegionRef region_ref);
    const regions_map_t & get_regions() const;

    void put_event(const OTF2_LocationRef loc_ref, const EventType event_type, const OTF2_TimeStamp time, uint64_t event_position, const OTF2_RegionRef object, const OTF2_RegionRef subject, const OTF2_RegionRef parent, const uint64_t size);
    void put_event(const OTF2_LocationRef loc_ref, const EventType event_type, const OTF2_TimeStamp time, uint64_t event_position, const OTF2_RegionRef object, const OTF2_RegionRef subject, const uint64_t size);
    const event_list_t & get_events(const OTF2_LocationRef loc_ref);
    event_list_t::const_iterator get_compute_event_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time);
    maybe_event_pair_t get_task_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time);   
    maybe_event_iter_pair_t get_task_iter_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time, const bool or_before = false);   
    std::string get_task_name_at_time(const OTF2_LocationRef loc_ref, const OTF2_TimeStamp time, bool also_guid=false, bool markup=false, bool also_time=false);
    event_list_t::const_iterator get_next_compute_event(const OTF2_LocationRef loc_ref, event_list_t::const_iterator iter);
    event_list_t::const_iterator get_prev_compute_event(const OTF2_LocationRef loc_ref, event_list_t::const_iterator iter);

    const event_ptr_list_t & get_events_for_guid(const std::string & guid) const;
    TraceData::GuidType get_type_for_guid(const std::string & guid);
    
    void put_clock_properties(uint64_t timer_resolution, uint64_t global_offset, uint64_t trace_length) {
        this->timer_resolution = timer_resolution;
        this->global_offset = global_offset;
        this->trace_length = trace_length;
    };
    
    uint64_t get_timer_resolution() const { return timer_resolution; };
    uint64_t get_global_offset() const { return global_offset; };
    uint64_t get_trace_length() const { return trace_length; };

    int get_seq_id(const std::string &  name);

    OTF2_RegionRef get_last_entered(OTF2_LocationRef loc_ref);
    void set_last_entered(OTF2_LocationRef loc_ref, OTF2_RegionRef region);

    void set_selective_guid_map_events(std::initializer_list<EventType> event_types);
};

#endif // TRACE_DATA_HPP
