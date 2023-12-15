#include "UtilityAIBTNodeReference.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTNodeReference::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_node_reference", "node_reference"), &UtilityAIBTNodeReference::set_node_reference);
    ClassDB::bind_method(D_METHOD("get_node_reference"), &UtilityAIBTNodeReference::get_node_reference);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "node_reference", PROPERTY_HINT_NODE_TYPE, "UtilityAIBehaviourTreeNodes" ), "set_node_reference","get_node_reference");

    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTNodeReference::tick);

}


// Constructor and destructor.

UtilityAIBTNodeReference::UtilityAIBTNodeReference() {
    //_tick_result = 1;
    _node_reference = nullptr;
}


UtilityAIBTNodeReference::~UtilityAIBTNodeReference() {
}


// Getters and Setters.

void UtilityAIBTNodeReference::set_node_reference(UtilityAIBehaviourTreeNodes* node_reference) {
    if( _node_reference == node_reference || (node_reference != nullptr && (this == node_reference || node_reference->is_ancestor_of(this) || this->is_ancestor_of(node_reference))) ) {
        return;
    }

    _node_reference = node_reference;
}

UtilityAIBehaviourTreeNodes* UtilityAIBTNodeReference::get_node_reference() const {
    return _node_reference;
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

void UtilityAIBTNodeReference::reset() {
    if(!_node_reference) {
        return;
    }
    _node_reference->reset();
}


int UtilityAIBTNodeReference::tick(Variant user_data, double delta) { 
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    if( !_node_reference ) {
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        set_tick_result(BT_FAILURE);
        return BT_FAILURE;
    }
    int result = _node_reference->tick( user_data, delta );
    set_tick_result(result);
    if( result != BT_RUNNING) {
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    }
    return result;
}

