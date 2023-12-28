#include "inverter.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTInverter::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTInverter::tick);
}


// Constructor and destructor.

UtilityAIBTInverter::UtilityAIBTInverter() {
    
}


UtilityAIBTInverter::~UtilityAIBTInverter() {
}


// Getters and Setters.


// Handling methods.

int UtilityAIBTInverter::tick(Variant user_data, float delta) { 
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
            
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            int result = -btnode->tick(user_data, delta);
            set_tick_result(result);
            if( result != BT_RUNNING ) {
                set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            }
            return result;
        }

    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    set_tick_result(BT_FAILURE);
    return BT_FAILURE;
}


