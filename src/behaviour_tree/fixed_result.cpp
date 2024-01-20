#include "fixed_result.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTFixedResult::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_fixed_result", "fixed_result"), &UtilityAIBTFixedResult::set_fixed_result);
    ClassDB::bind_method(D_METHOD("get_fixed_result"), &UtilityAIBTFixedResult::get_fixed_result);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "fixed_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_fixed_result","get_fixed_result");

    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTFixedResult::tick);

}


// Constructor and destructor.

UtilityAIBTFixedResult::UtilityAIBTFixedResult() {
    _fixed_result = BT_SUCCESS;
}


UtilityAIBTFixedResult::~UtilityAIBTFixedResult() {
}


// Getters and Setters.

void UtilityAIBTFixedResult::set_fixed_result( int fixed_result ) {
    _fixed_result = fixed_result;
}


int  UtilityAIBTFixedResult::get_fixed_result() const {
    return _fixed_result;
}

// Handling methods.

int UtilityAIBTFixedResult::tick(Variant user_data, float delta) {
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    //if( _is_first_tick ) {
    //    _is_first_tick = false;
    //    emit_signal("btnode_entered", user_data, delta);
    //}

    set_tick_result(_fixed_result);
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            btnode->tick(user_data, delta);
            //emit_signal("btnode_ticked", user_data, delta);
            break;
        }

    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    //emit_signal("btnode_exited", user_data, delta);
    return _fixed_result;
}


