#include "UtilityAIBTNodeReference.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTNodeReference::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_node_reference_nodepath", "node_reference_nodepath"), &UtilityAIBTNodeReference::set_node_reference_nodepath);
    ClassDB::bind_method(D_METHOD("get_node_reference_nodepath"), &UtilityAIBTNodeReference::get_node_reference_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "node_reference_nodepath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "UtilityAIBehaviourTreeNodes" ), "set_node_reference_nodepath","get_node_reference_nodepath");

}


// Constructor and destructor.

UtilityAIBTNodeReference::UtilityAIBTNodeReference() {
    //_tick_result = 1;
}


UtilityAIBTNodeReference::~UtilityAIBTNodeReference() {
}


// Getters and Setters.

void UtilityAIBTNodeReference::set_node_reference_nodepath(const NodePath &node_reference_nodepath) {
    if( _node_reference_nodepath == node_reference_nodepath ) {
        return;
    }

    _node_reference_nodepath = node_reference_nodepath;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    if( is_inside_tree() ) {
        _update_cache();
    }

}

NodePath UtilityAIBTNodeReference::get_node_reference_nodepath() const {
    return _node_reference_nodepath;
}

/**
void UtilityAIBTNodeReference::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
}


int  UtilityAIBTNodeReference::get_tick_result() const {
    return _tick_result;
}
/**/

// Handling methods.

void UtilityAIBTNodeReference::_update_cache() {
    _cache = ObjectID();
	if (has_node(_node_reference_nodepath)) {
		UtilityAIBehaviourTreeNodes* btnode = get_node<UtilityAIBehaviourTreeNodes>(_node_reference_nodepath);
		if (!btnode || this == btnode || btnode->is_ancestor_of(this) || this->is_ancestor_of(btnode)) {
			return;
		}
		_cache = btnode->get_instance_id();
	}
}


int UtilityAIBTNodeReference::tick(Variant user_data, double delta) { 
    if(_cache.is_null()) {
		return BT_FAILURE;
	}
    if( !_cache.is_valid() ) {
        return BT_FAILURE;
    }
    
    UtilityAIBehaviourTreeNodes* btnode = Object::cast_to<UtilityAIBehaviourTreeNodes>(ObjectDB::get_instance(_cache));
    if( btnode == nullptr ) {
        return BT_FAILURE;
    }
    return btnode->tick( user_data, delta );
}

// Godot virtuals.

void UtilityAIBTNodeReference::_enter_tree() {
    _update_cache();
}

