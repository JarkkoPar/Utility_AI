#include "sequence.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTSequence::_bind_methods() {
    
    //ClassDB::bind_method(D_METHOD("set_is_reactive", "is_reactive"), &UtilityAIBTSequence::set_is_reactive);
    //ClassDB::bind_method(D_METHOD("get_is_reactive"), &UtilityAIBTSequence::get_is_reactive);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_reactive", PROPERTY_HINT_NONE), "set_is_reactive","get_is_reactive");
    
    /*
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTSequence::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTSequence::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

    //ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTSequence::set_reset_rule);
    //ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTSequence::get_reset_rule);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
 
}


// Constructor and destructor.

UtilityAIBTSequence::UtilityAIBTSequence() {
    _current_child_index = 0;
    //_is_reactive = true;
}


UtilityAIBTSequence::~UtilityAIBTSequence() {
}

// Handling functions.



// Getters and Setters.

/**
void UtilityAIBTSequence::set_is_reactive( bool is_reactive ) {
    _is_reactive = is_reactive;
}

bool UtilityAIBTSequence::get_is_reactive() const {
    return _is_reactive;
}
/**/

void UtilityAIBTSequence::reset_bt_node() {
    _current_child_index = 0;
}


int UtilityAIBTSequence::tick(Variant user_data, float delta) {
    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED ) {
        _current_child_index = 0;
    }
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    while( _current_child_index < get_child_count() ) {
        UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_current_child_index));
        if( btnode != nullptr ) {
            if( btnode->get_is_active() ) {
                
                int result = btnode->tick(user_data, delta);
                set_tick_result(result);
                if( result == BT_FAILURE ) {
                    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
                    return BT_FAILURE;
                } else if ( result == BT_RUNNING ) {
                    return BT_RUNNING;
                }
            }//endif is active
        }//endif node was of correct type
        ++_current_child_index;
    }//endwhile children to tick
    
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    return BT_SUCCESS;
}


