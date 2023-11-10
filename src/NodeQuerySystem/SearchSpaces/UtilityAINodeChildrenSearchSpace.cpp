#include "UtilityAINodeChildrenSearchSpace.h"
#include <godot_cpp/classes/engine.hpp>
//#include <godot_cpp/classes/node.hpp>

using namespace godot;


UtilityAINodeChildrenSearchSpace::UtilityAINodeChildrenSearchSpace() {
    _parent_node_path = "";
}


UtilityAINodeChildrenSearchSpace::~UtilityAINodeChildrenSearchSpace() {
    
}


void UtilityAINodeChildrenSearchSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_parent_node_path", "parent_node_path"), &UtilityAINodeChildrenSearchSpace::set_parent_node_path);
    ClassDB::bind_method(D_METHOD("get_parent_node_path"), &UtilityAINodeChildrenSearchSpace::get_parent_node_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "parent_node_path", PROPERTY_HINT_NONE), "set_parent_node_path","get_parent_node_path");
}

// Getters and setters.

void UtilityAINodeChildrenSearchSpace::set_parent_node_path( NodePath parent_node_path ) {
    _parent_node_path = parent_node_path;
}


NodePath UtilityAINodeChildrenSearchSpace::get_parent_node_path() const {
    return _parent_node_path;
}


TypedArray<Node> UtilityAINodeChildrenSearchSpace::get_searchspace_nodes() const {
    if( _parent_node == nullptr ) {
        return nullptr;
    }
    return _parent_node->get_children();
}


void UtilityAINodeChildrenSearchSpace::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    _parent_node = get_node_or_null(_parent_node_path);
}

