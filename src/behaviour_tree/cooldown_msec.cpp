#include "cooldown_msec.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

// Method binds.

void UtilityAIBTCooldownMsec::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_cooldown_msec", "cooldown_msec"), &UtilityAIBTCooldownMsec::set_cooldown_msec);
    ClassDB::bind_method(D_METHOD("get_cooldown_msec"), &UtilityAIBTCooldownMsec::get_cooldown_msec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_msec", PROPERTY_HINT_RANGE, "0,1000,or_greater" ), "set_cooldown_msec","get_cooldown_msec");

    ClassDB::bind_method(D_METHOD("set_cooldown_return_value", "cooldown_return_value"), &UtilityAIBTCooldownMsec::set_cooldown_return_value);
    ClassDB::bind_method(D_METHOD("get_cooldown_return_value"), &UtilityAIBTCooldownMsec::get_cooldown_return_value);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_return_value", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_cooldown_return_value","get_cooldown_return_value");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_cooldown_start_timestamp", "cooldown_start_timestamp"), &UtilityAIBTCooldownMsec::set_cooldown_start_timestamp);
    ClassDB::bind_method(D_METHOD("get_cooldown_start_timestamp"), &UtilityAIBTCooldownMsec::get_cooldown_start_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_start_timestamp", PROPERTY_HINT_RANGE, "0,1000,or_greater" ), "set_cooldown_start_timestamp","get_cooldown_start_timestamp");

}


// Constructor and destructor.

UtilityAIBTCooldownMsec::UtilityAIBTCooldownMsec() {
    _cooldown_msec = 0;
    _cooldown_start_timestamp = 0;
    _cooldown_return_value = BT_FAILURE;
}


UtilityAIBTCooldownMsec::~UtilityAIBTCooldownMsec() {
}


// Getters and Setters.

void UtilityAIBTCooldownMsec::set_cooldown_msec( int cooldown_msec ) {
    _cooldown_msec = cooldown_msec;
}


int  UtilityAIBTCooldownMsec::get_cooldown_msec() const {
    return _cooldown_msec;
}


void UtilityAIBTCooldownMsec::set_cooldown_start_timestamp( int cooldown_start_timestamp ) {
    _cooldown_start_timestamp = cooldown_start_timestamp;
}


int  UtilityAIBTCooldownMsec::get_cooldown_start_timestamp() const {
    return _cooldown_start_timestamp;
}


void UtilityAIBTCooldownMsec::set_cooldown_return_value( int cooldown_return_value ) {
    _cooldown_return_value = cooldown_return_value;
}


int  UtilityAIBTCooldownMsec::get_cooldown_return_value() const {
    return _cooldown_return_value;
}

// Handling methods.

int UtilityAIBTCooldownMsec::tick(Variant user_data, float delta) {
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    uint64_t wait_time = godot::Time::get_singleton()->get_ticks_msec() - _cooldown_start_timestamp;
    if( wait_time < _cooldown_msec ) {
        return _cooldown_return_value;
    }
    _cooldown_start_timestamp = godot::Time::get_singleton()->get_ticks_msec();
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


