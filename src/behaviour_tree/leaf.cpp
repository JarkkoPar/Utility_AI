#include "leaf.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTLeaf::_bind_methods() {
    
    //ClassDB::bind_method(D_METHOD("set_tick_result", "tick_result"), &UtilityAIBTLeaf::set_tick_result);
    //ClassDB::bind_method(D_METHOD("get_tick_result"), &UtilityAIBTLeaf::get_tick_result);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_tick_result","get_tick_result");
    //ADD_SIGNAL(MethodInfo("ticked", PropertyInfo(Variant::OBJECT, "user_data"), PropertyInfo(Variant::FLOAT, "delta"), PropertyInfo(Variant::OBJECT, "leaf_node")));

    ADD_SIGNAL(MethodInfo("btree_node_entered", PropertyInfo(Variant::OBJECT, "user_data"), PropertyInfo(Variant::FLOAT, "delta")));
    ADD_SIGNAL(MethodInfo("btree_node_ticked", PropertyInfo(Variant::OBJECT, "user_data"), PropertyInfo(Variant::FLOAT, "delta")));
    ADD_SIGNAL(MethodInfo("btree_node_exited", PropertyInfo(Variant::OBJECT, "user_data"), PropertyInfo(Variant::FLOAT, "delta")));
}


// Constructor and destructor.

UtilityAIBTLeaf::UtilityAIBTLeaf() {
    _has_on_tick_method = false;
    _has_tick_method = false;
}


UtilityAIBTLeaf::~UtilityAIBTLeaf() {
}


// Getters and Setters.
/**
void UtilityAIBTLeaf::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
    if( _tick_result > 1 ) {
        _tick_result = 1;
    } else if (_tick_result < -1 ) {
        _tick_result = -1;
    }
}


int  UtilityAIBTLeaf::get_tick_result() const {
    return _tick_result;
}
/**/

// Handling methods.

int UtilityAIBTLeaf::tick(Variant user_data, float delta) { 
    
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    emit_signal("btree_node_entered", user_data, delta);
    if( _has_on_tick_method ) {
        godot::Variant return_value = call("on_tick", user_data, delta);
        if( return_value.get_type() == godot::Variant::Type::INT) {
            set_tick_result((int)return_value);
        }
        
    } else if( _has_tick_method ) {
        godot::Variant return_value = call("tick", user_data, delta);
        if( return_value.get_type() == godot::Variant::Type::INT) {
            set_tick_result((int)return_value);
        }
        
    }
    emit_signal("btree_node_ticked", user_data, delta);
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    emit_signal("btree_node_exited", user_data, delta);
    return get_tick_result();
}


// Godot virtuals.

void UtilityAIBTLeaf::_enter_tree() {
    _has_on_tick_method = has_method("on_tick");
    _has_tick_method = has_method("tick");
}

