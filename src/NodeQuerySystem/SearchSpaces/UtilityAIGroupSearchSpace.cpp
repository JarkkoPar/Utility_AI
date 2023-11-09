#include "UtilityAIGroupSearchSpace.h"
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;


UtilityAIGroupSearchSpace::UtilityAIGroupSearchSpace() {
    _searchspace_node_group = "";
}


UtilityAIGroupSearchSpace::~UtilityAIGroupSearchSpace() {
    
}


void UtilityAIGroupSearchSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_searchspace_node_group", "searchspace_node_group"), &UtilityAIGroupSearchSpace::set_searchspace_node_group);
    ClassDB::bind_method(D_METHOD("get_searchspace_node_group"), &UtilityAIGroupSearchSpace::get_searchspace_node_group);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "searchspace_node_group", PROPERTY_HINT_NONE), "set_searchspace_node_group","get_searchspace_node_group");
}

// Getters and setters.

void UtilityAIGroupSearchSpace::set_searchspace_node_group( StringName searchspace_node_group ) {
    _searchspace_node_group = searchspace_node_group;
}


StringName UtilityAIGroupSearchSpace::get_searchspace_node_group() const {
    return _searchspace_node_group;
}


TypedArray<Node> UtilityAIGroupSearchSpace::get_searchspace_nodes() const {
    return get_tree()->get_nodes_in_group(_searchspace_node_group);
}

