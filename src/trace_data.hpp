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

        LocationGroup(TraceData * trace_data, const OTF2_LocationRef loc, const OTF2_StringRef name, const OTF2_LocationGroupType type, OTF2_LocationGroupRef parent) : trace_data(trace_data), loc(loc), name(name), type(type), parent(parent), name_str(nullptr), parent_node(nullptr) {};

        OTF2_StringRef get_name_ref() const { return name; };
        OTF2_LocationGroupType get_type() const { return type; };
        OTF2_LocationGroupRef get_parent_ref() const { return parent; };
        OTF2_LocationRef get_loc() const { return loc; };

        const std::string & get_name() const;
        const TraceData::SystemTreeNode & get_parent() const;
            
    };

protected:
    using string_map_t  = std::unordered_map<OTF2_StringRef, std::string>;
    using strings_map_t = std::map<OTF2_LocationRef, string_map_t>;
    strings_map_t strings_map;

    using node_map_t    = std::map<OTF2_SystemTreeNodeRef, SystemTreeNode>;
    using nodes_map_t   = std::map<OTF2_LocationRef, node_map_t>;
    nodes_map_t   nodes_map;

    using location_group_map_t  = std::map<OTF2_LocationGroupRef, LocationGroup>;
    using location_groups_map_t = std::map<OTF2_LocationRef, location_group_map_t>;
    location_groups_map_t location_groups_map;

    OTF2_LocationRef cur_loc;

public:

    TraceData();
    virtual ~TraceData();

    void put_string(const OTF2_LocationRef loc_ref, const OTF2_StringRef str_ref, const std::string & str);
    const std::string & get_string(const OTF2_LocationRef loc_ref, const OTF2_StringRef str_ref);

    void set_current_location(const OTF2_LocationRef loc);
    OTF2_LocationRef get_current_location() const;

    void put_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref, const OTF2_StringRef name, const OTF2_StringRef desc, const OTF2_SystemTreeNodeRef parent);
    const SystemTreeNode & get_system_tree_node(const OTF2_LocationRef loc_ref, const OTF2_SystemTreeNodeRef node_ref);
    const nodes_map_t & get_system_tree_nodes();

    void put_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref, const OTF2_StringRef name, const OTF2_LocationGroupType type, const OTF2_SystemTreeNodeRef parent);
    const LocationGroup & get_location_group(const OTF2_LocationRef loc_ref, const OTF2_LocationGroupRef loc_group_ref);
    const location_groups_map_t & get_location_groups();

};

#endif // TRACE_DATA_HPP
