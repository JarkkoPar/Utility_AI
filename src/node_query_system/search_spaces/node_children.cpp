#include "node_children.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


UtilityAINodeChildrenSearchSpace::UtilityAINodeChildrenSearchSpace() {
    _parent_node = nullptr;
}


UtilityAINodeChildrenSearchSpace::~UtilityAINodeChildrenSearchSpace() {
    
}


void UtilityAINodeChildrenSearchSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_parent_node", "parent_node"), &UtilityAINodeChildrenSearchSpace::set_parent_node);
    ClassDB::bind_method(D_METHOD("get_parent_node"), &UtilityAINodeChildrenSearchSpace::get_parent_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "parent_node", PROPERTY_HINT_NODE_TYPE, "Node"), "set_parent_node","get_parent_node");
}


void UtilityAINodeChildrenSearchSpace::_initialize_search_space() {
}

void UtilityAINodeChildrenSearchSpace::_uninitialize_search_space() {
    _parent_node = nullptr;
}

// Getters and setters.

void UtilityAINodeChildrenSearchSpace::set_parent_node( Node* parent_node ) {
    _parent_node = parent_node;
}


Node* UtilityAINodeChildrenSearchSpace::get_parent_node() const {
    return _parent_node;
}


TypedArray<Node> UtilityAINodeChildrenSearchSpace::get_searchspace_nodes() const {
    if( _parent_node == nullptr || !UtilityFunctions::is_instance_valid(_parent_node) ) {
        TypedArray<Node> emptyarray;
        return emptyarray;
    }
    return _parent_node->get_children();
}


/**
void UtilityAINodeChildrenSearchSpace::_ready() {
    //if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    //_parent_node = get_node_or_null(_parent_node_path);
    
}
/**/
