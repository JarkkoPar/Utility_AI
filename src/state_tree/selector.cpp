#include "selector.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include "../performance_monitor_singleton.h"


using namespace godot;

// Method binds.

void UtilityAISTSelector::_bind_methods() {

    //ADD_SUBGROUP("Debugging","");

    //ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAISTSelector::set_total_tick_usec);
    //ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAISTSelector::get_total_tick_usec);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");

    //ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAISTSelector::tick);
}


// Constructor and destructor.

UtilityAISTSelector::UtilityAISTSelector() {
    _current_child_index = -1;
}


UtilityAISTSelector::~UtilityAISTSelector() {
}


// Getters and Setters.






// Handling functions.


UtilityAIStateTreeNodes* UtilityAISTSelector::_tick(Variant user_data, double delta) { 

    // The selector will only consider the state tree nodes.
    UtilityAIStateTreeNodes* result_state = nullptr;
    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(i)) ) {
            if( stnode->on_enter_condition( user_data, delta ) ) {
                result_state = stnode->_tick(user_data, delta);
                if( result_state != nullptr ) {
                    return result_state;
                }
            }//endif on_enter_condition returned true
        }// endif valid stnode
    }//endfor child count
    return nullptr; // We shouldn't get here. If we do, there were no child nodes.
}


// Godot virtuals.
void UtilityAISTSelector::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    reset();
}


