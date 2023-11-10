#include "UtilityAIGroupSearchSpace.h"
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;


UtilityAIGroupSearchSpace::UtilityAIGroupSearchSpace() {
    _group_name = "";
}


UtilityAIGroupSearchSpace::~UtilityAIGroupSearchSpace() {
    
}


void UtilityAIGroupSearchSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_group_name", "group_name"), &UtilityAIGroupSearchSpace::set_group_name);
    ClassDB::bind_method(D_METHOD("get_group_name"), &UtilityAIGroupSearchSpace::get_group_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "group_name", PROPERTY_HINT_NONE), "set_group_name","get_group_name");
}

// Getters and setters.

void UtilityAIGroupSearchSpace::set_group_name( StringName group_name ) {
    _group_name = group_name;
}


StringName UtilityAIGroupSearchSpace::get_group_name() const {
    return _group_name;
}


TypedArray<Node> UtilityAIGroupSearchSpace::get_searchspace_nodes() const {
    return get_tree()->get_nodes_in_group(_group_name);
}

