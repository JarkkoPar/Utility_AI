#include "UtilityAIBTInverter.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTInverter::_bind_methods() {
}


// Constructor and destructor.

UtilityAIBTInverter::UtilityAIBTInverter() {
    
}


UtilityAIBTInverter::~UtilityAIBTInverter() {
}


// Getters and Setters.


// Handling methods.

int UtilityAIBTInverter::tick(Variant user_data, double delta) { 
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
            return -btnode->tick(user_data, delta);
        }

    }
    return BT_FAILURE;
}


