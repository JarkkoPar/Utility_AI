#include "UtilityAIBTRandomSelector.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTRandomSelector::_bind_methods() {

    //ClassDB::bind_method(D_METHOD("set_is_reactive", "is_reactive"), &UtilityAIBTRandomSelector::set_is_reactive);
    //ClassDB::bind_method(D_METHOD("get_is_reactive"), &UtilityAIBTRandomSelector::get_is_reactive);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_reactive", PROPERTY_HINT_NONE), "set_is_reactive","get_is_reactive");
    

    /**
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTRandomSelector::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTRandomSelector::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTRandomSelector::tick);
    //ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTRandomSelector::set_reset_rule);
    //ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTRandomSelector::get_reset_rule);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
 
}


// Constructor and destructor.

UtilityAIBTRandomSelector::UtilityAIBTRandomSelector() {
    _current_child_index = 0;
    //_is_reactive = true;
}


UtilityAIBTRandomSelector::~UtilityAIBTRandomSelector() {
}




// Getters and Setters.

/**
void UtilityAIBTRandomSelector::set_is_reactive( bool is_reactive ) {
    _is_reactive = is_reactive;
}

bool UtilityAIBTRandomSelector::get_is_reactive() const {
    return _is_reactive;
}
/**/

void UtilityAIBTRandomSelector::reset_bt_node() {
    _current_child_index = 0;
    // Create a random order.
    _child_node_order.clear();
    for( int i = 0; i < get_child_count(); ++i ) {
        UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i));
        if( btnode == nullptr ) continue;
        if( !btnode->get_is_active() ) {
            continue;
        } 
        _child_node_order.push_back(i);
    }
    _child_node_order.shuffle();
}


// Handling functions.

int UtilityAIBTRandomSelector::tick(Variant user_data, double delta) { 
    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED ) {
        reset_bt_node();
    }

    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    while( _current_child_index < _child_node_order.size() ) {
        UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_child_node_order[_current_child_index]));
        if( btnode != nullptr ) {
            //if( !btnode->get_is_active() ) {
            //    continue;
            //} 
            int result = btnode->tick(user_data, delta);
            if( result == BT_SUCCESS ) {
                //_current_child_index = -1;
                set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
                return BT_SUCCESS;
            } else if ( result == BT_RUNNING ) {
                return BT_RUNNING;
            }
        }//endif node was of correct type
        ++_current_child_index;
    }//endwhile children to tick
    //_current_child_index = -1;
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    return BT_FAILURE;
}


