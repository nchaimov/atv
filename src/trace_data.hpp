#ifndef TRACE_DATA_HPP
#define TRACE_DATA_HPP

#include <otf2/otf2.h>
#include <unordered_map>
#include <map>
#include <vector>

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
            
    };



protected:
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

    using region_map_t = std::unordered_map<OTF2_RegionRef, Region>;
    using regions_map_t = std::map<OTF2_LocationRef, region_map_t>;
    regions_map_t regions_map;
    Region invalid_region;


public:

    TraceData();
    virtual ~TraceData();

    void put_string(const OTF2_LocationRef loc_ref, const OTF2_StringRef str_ref, const std::string & str);
    const std::string & get_string(const OTF2_LocationRef loc_ref, const OTF2_StringRef str_ref);

    void set_current_location(const OTF2_LocationRef loc);
    OTF2_LocationRef get_current_location() const;

    void put_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref, const OTF2_StringRef name, const OTF2_StringRef desc, const OTF2_SystemTreeNodeRef parent);
    const SystemTreeNode & get_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref);
    const SystemTreeNode & find_system_tree_node(const OTF2_SystemTreeNodeRef node_ref);
    const nodes_map_t & get_system_tree_nodes();

    void put_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref, const OTF2_StringRef name, const OTF2_LocationGroupType type, const OTF2_SystemTreeNodeRef parent);
    const LocationGroup & get_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref);
    const LocationGroup & find_location_group(const OTF2_LocationGroupRef loc_group_ref);
    const location_groups_map_t & get_location_groups();

    void put_location(const OTF2_LocationRef loc_ref, const OTF2_StringRef name, const OTF2_LocationType type, const uint64_t num_events, const OTF2_LocationGroupRef parent);
    const Location & get_location(const OTF2_LocationRef loc_ref);
    const location_map_t & get_locations();

    void put_region(const OTF2_LocationRef loc, const OTF2_RegionRef self, const OTF2_StringRef name, const OTF2_StringRef guid, const OTF2_StringRef desc, const OTF2_RegionRole role, const OTF2_Paradigm paradigm, const OTF2_RegionFlag region_flag, const OTF2_StringRef source_file, const uint32_t begin_line_number, const uint32_t end_line_number);
    const Region & get_region(const OTF2_LocationRef loc_ref, const OTF2_RegionRef region_ref);
    const regions_map_t & get_regions();

};

#endif // TRACE_DATA_HPP
