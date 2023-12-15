#include "node_group.h"
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;


UtilityAINodeGroupSearchSpace::UtilityAINodeGroupSearchSpace() {
    _group_name = "";
}


UtilityAINodeGroupSearchSpace::~UtilityAINodeGroupSearchSpace() {
    
}


void UtilityAINodeGroupSearchSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_group_name", "group_name"), &UtilityAINodeGroupSearchSpace::set_group_name);
    ClassDB::bind_method(D_METHOD("get_group_name"), &UtilityAINodeGroupSearchSpace::get_group_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "group_name", PROPERTY_HINT_NONE), "set_group_name","get_group_name");
}

// Getters and setters.

void UtilityAINodeGroupSearchSpace::set_group_name( StringName group_name ) {
    _group_name = group_name;
}


StringName UtilityAINodeGroupSearchSpace::get_group_name() const {
    return _group_name;
}


TypedArray<Node> UtilityAINodeGroupSearchSpace::get_searchspace_nodes() const {
    return get_tree()->get_nodes_in_group(_group_name);
}

