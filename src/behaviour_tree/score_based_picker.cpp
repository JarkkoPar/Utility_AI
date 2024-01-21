#include "score_based_picker.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTScoreBasedPicker::_bind_methods() {
    
    //ClassDB::bind_method(D_METHOD("set_is_reactive", "is_reactive"), &UtilityAIBTScoreBasedPicker::set_is_reactive);
    //ClassDB::bind_method(D_METHOD("get_is_reactive"), &UtilityAIBTScoreBasedPicker::get_is_reactive);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_reactive", PROPERTY_HINT_NONE), "set_is_reactive","get_is_reactive");
    
    /*
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTScoreBasedPicker::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTScoreBasedPicker::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

    //ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTScoreBasedPicker::set_reset_rule);
    //ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTScoreBasedPicker::get_reset_rule);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
 
}


// Constructor and destructor.

UtilityAIBTScoreBasedPicker::UtilityAIBTScoreBasedPicker() {
    _current_child_index = -1;
    //_is_reactive = true;
}


UtilityAIBTScoreBasedPicker::~UtilityAIBTScoreBasedPicker() {
}

// Handling functions.



// Getters and Setters.
/**
void UtilityAIBTScoreBasedPicker::set_is_reactive( bool is_reactive ) {
    _is_reactive = is_reactive;
}

bool UtilityAIBTScoreBasedPicker::get_is_reactive() const {
    return _is_reactive;
}
/**/

void UtilityAIBTScoreBasedPicker::reset_bt_node() {
    // Evaluate the scores and pick the child with the highest
    // score to run.
    _current_child_index = -1;
    float current_highest_score = -99999999.9999;
    //for( int i = 0; i < get_child_count(); ++i ) {
    //    UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i));
    for( unsigned int i = 0; i < _num_child_btnodes; ++i ) {
        UtilityAIBehaviourTreeNodes* btnode = _child_btnodes[i];
        //if( btnode == nullptr ) {
        //    continue;
        //}
        if( !btnode->get_is_active() ) {
            continue;
        } 
        // Evaluate the node to get its score.
        float score = btnode->evaluate();
        if( score > current_highest_score ) {
            _current_child_index = i;
            current_highest_score = score;
        }
    }//endfor children
    
}

int UtilityAIBTScoreBasedPicker::tick(Variant user_data, float delta) {
    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED ) {
        reset_bt_node();    
    }

    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    //if( _is_first_tick ) {
    //    _is_first_tick = false;
    //    emit_signal("btnode_entered", user_data, delta);
    //}
    
    if( _current_child_index < 0 ) {
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        set_tick_result(BT_FAILURE);
        //emit_signal("btnode_exited", user_data, delta);
        return BT_FAILURE; // No valid child found.
    }

    
    //UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_current_child_index));
    UtilityAIBehaviourTreeNodes* btnode = _child_btnodes[_current_child_index];
    if( btnode != nullptr ) {
        int return_value = btnode->tick(user_data, delta);
        set_tick_result(return_value);
        //emit_signal("btnode_ticked", user_data, delta);
        if( return_value == BT_FAILURE || return_value == BT_SUCCESS ) {
            _current_child_index = -1;
            set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            //emit_signal("btnode_exited", user_data, delta);
        }
        return return_value;
    }//endif node was of correct type
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    set_tick_result(BT_FAILURE);
    //emit_signal("btnode_exited", user_data, delta);
    return BT_FAILURE; 
}


