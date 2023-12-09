#include "UtilityAIBTCooldownTicks.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTCooldownTicks::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_cooldown_ticks", "cooldown_ticks"), &UtilityAIBTCooldownTicks::set_cooldown_ticks);
    ClassDB::bind_method(D_METHOD("get_cooldown_ticks"), &UtilityAIBTCooldownTicks::get_cooldown_ticks);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_ticks", PROPERTY_HINT_RANGE, "0,1000,or_greater" ), "set_cooldown_ticks","get_cooldown_ticks");

    ClassDB::bind_method(D_METHOD("set_cooldown_return_value", "cooldown_return_value"), &UtilityAIBTCooldownTicks::set_cooldown_return_value);
    ClassDB::bind_method(D_METHOD("get_cooldown_return_value"), &UtilityAIBTCooldownTicks::get_cooldown_return_value);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_return_value", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_cooldown_return_value","get_cooldown_return_value");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_current_cooldown_ticks", "current_cooldown_ticks"), &UtilityAIBTCooldownTicks::set_current_cooldown_ticks);
    ClassDB::bind_method(D_METHOD("get_current_cooldown_ticks"), &UtilityAIBTCooldownTicks::get_current_cooldown_ticks);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_cooldown_ticks", PROPERTY_HINT_RANGE, "0,1000,or_greater" ), "set_current_cooldown_ticks","get_current_cooldown_ticks");

    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTCooldownTicks::tick);

}


// Constructor and destructor.

UtilityAIBTCooldownTicks::UtilityAIBTCooldownTicks() {
    _cooldown_ticks = 0;
    _current_cooldown_ticks = 0;
    _cooldown_return_value = BT_FAILURE;
}


UtilityAIBTCooldownTicks::~UtilityAIBTCooldownTicks() {
}


// Getters and Setters.

void UtilityAIBTCooldownTicks::set_cooldown_ticks( int cooldown_ticks ) {
    _cooldown_ticks = cooldown_ticks;
}


int  UtilityAIBTCooldownTicks::get_cooldown_ticks() const {
    return _cooldown_ticks;
}


void UtilityAIBTCooldownTicks::set_current_cooldown_ticks( int current_cooldown_ticks ) {
    _current_cooldown_ticks = current_cooldown_ticks;
}


int  UtilityAIBTCooldownTicks::get_current_cooldown_ticks() const {
    return _current_cooldown_ticks;
}


void UtilityAIBTCooldownTicks::set_cooldown_return_value( int cooldown_return_value ) {
    _cooldown_return_value = cooldown_return_value;
}


int  UtilityAIBTCooldownTicks::get_cooldown_return_value() const {
    return _cooldown_return_value;
}

// Handling methods.

int UtilityAIBTCooldownTicks::tick(Variant user_data, double delta) { 
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    if( _current_cooldown_ticks > 0 ) {
        --_current_cooldown_ticks;
        return _cooldown_return_value;
    }
    _current_cooldown_ticks = _cooldown_ticks;
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            int result = btnode->tick(user_data, delta);
            set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            set_tick_result(result);
            return result;
        }

    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    set_tick_result(BT_FAILURE);
    return BT_FAILURE;
}


