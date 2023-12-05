#include "UtilityAIBTCooldownUsec.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

// Method binds.

void UtilityAIBTCooldownUsec::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_cooldown_usec", "cooldown_usec"), &UtilityAIBTCooldownUsec::set_cooldown_usec);
    ClassDB::bind_method(D_METHOD("get_cooldown_usec"), &UtilityAIBTCooldownUsec::get_cooldown_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_usec", PROPERTY_HINT_RANGE, "0,1000,or_greater" ), "set_cooldown_usec","get_cooldown_usec");

    ClassDB::bind_method(D_METHOD("set_cooldown_start_timestamp", "cooldown_start_timestamp"), &UtilityAIBTCooldownUsec::set_cooldown_start_timestamp);
    ClassDB::bind_method(D_METHOD("get_cooldown_start_timestamp"), &UtilityAIBTCooldownUsec::get_cooldown_start_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_start_timestamp", PROPERTY_HINT_RANGE, "0,1000,or_greater" ), "set_cooldown_start_timestamp","get_cooldown_start_timestamp");

    ClassDB::bind_method(D_METHOD("set_cooldown_return_value", "cooldown_return_value"), &UtilityAIBTCooldownUsec::set_cooldown_return_value);
    ClassDB::bind_method(D_METHOD("get_cooldown_return_value"), &UtilityAIBTCooldownUsec::get_cooldown_return_value);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_return_value", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_cooldown_return_value","get_cooldown_return_value");

    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTCooldownUsec::tick);

}


// Constructor and destructor.

UtilityAIBTCooldownUsec::UtilityAIBTCooldownUsec() {
    _cooldown_usec = 0;
    _cooldown_start_timestamp = 0;
    _cooldown_return_value = BT_FAILURE;
}


UtilityAIBTCooldownUsec::~UtilityAIBTCooldownUsec() {
}


// Getters and Setters.

void UtilityAIBTCooldownUsec::set_cooldown_usec( int cooldown_usec ) {
    _cooldown_usec = cooldown_usec;
}


int  UtilityAIBTCooldownUsec::get_cooldown_usec() const {
    return _cooldown_usec;
}


void UtilityAIBTCooldownUsec::set_cooldown_start_timestamp( int cooldown_start_timestamp ) {
    _cooldown_start_timestamp = cooldown_start_timestamp;
}


int  UtilityAIBTCooldownUsec::get_cooldown_start_timestamp() const {
    return _cooldown_start_timestamp;
}


void UtilityAIBTCooldownUsec::set_cooldown_return_value( int cooldown_return_value ) {
    _cooldown_return_value = cooldown_return_value;
}


int  UtilityAIBTCooldownUsec::get_cooldown_return_value() const {
    return _cooldown_return_value;
}

// Handling methods.

int UtilityAIBTCooldownUsec::tick(Variant user_data, double delta) {
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
            
    uint64_t wait_time = godot::Time::get_singleton()->get_ticks_usec() - _cooldown_start_timestamp;
    if( wait_time < _cooldown_usec ) {
        return _cooldown_return_value;
    }
    _cooldown_start_timestamp = godot::Time::get_singleton()->get_ticks_usec();
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


