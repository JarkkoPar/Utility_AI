#include "random_selector.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTRandomSelector::_bind_methods() {

}


// Constructor and destructor.

UtilityAIBTRandomSelector::UtilityAIBTRandomSelector() {
    _current_child_index = 0;
}


UtilityAIBTRandomSelector::~UtilityAIBTRandomSelector() {
}




// Getters and Setters.



void UtilityAIBTRandomSelector::reset_bt_node() {
    _current_child_index = 0;
    // Create a random order.
    _child_node_order.clear();
    for( unsigned int i = 0; i < _num_child_btnodes; ++i ) {
        UtilityAIBehaviourTreeNodes* btnode = _child_btnodes[i];
        if( !btnode->get_is_active() ) {
            continue;
        } 
        _child_node_order.push_back(i);
    }
    _child_node_order.shuffle();
}


// Handling functions.

int UtilityAIBTRandomSelector::tick(Variant user_data, float delta) { 
    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED ) {
        reset_bt_node();
    }

    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    //if( _is_first_tick ) {
    //    _is_first_tick = false;
    //    emit_signal("btnode_entered", user_data, delta);
    //}
    //emit_signal("btnode_ticked", user_data, delta);
    while( _current_child_index < _child_node_order.size() ) {
        //UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_child_node_order[_current_child_index]));
        UtilityAIBehaviourTreeNodes* btnode = _child_btnodes[(int)_child_node_order[_current_child_index]];
        //if( btnode != nullptr ) {
        //if( !btnode->get_is_active() ) {
        //    continue;
        //} 
        int result = btnode->tick(user_data, delta);
        if( result == BT_SUCCESS ) {
            //_current_child_index = -1;
            set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            //emit_signal("btnode_exited", user_data, delta);
            return BT_SUCCESS;
        } else if ( result == BT_RUNNING ) {
            return BT_RUNNING;
        }
        //}//endif node was of correct type
        ++_current_child_index;
    }//endwhile children to tick
    //_current_child_index = -1;
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    //emit_signal("btnode_exited", user_data, delta);
    return BT_FAILURE;
}


