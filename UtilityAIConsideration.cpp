#include "UtilityAIConsideration.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsideration::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_input_sensor_node_path", "input_sensor_node_path"), &UtilityAIConsideration::set_input_sensor_node_path);
    ClassDB::bind_method(D_METHOD("get_input_sensor_node_path"), &UtilityAIConsideration::get_input_sensor_node_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "input_sensor_node_path", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "UtilityAISensors"), "set_input_sensor_node_path", "get_input_sensor_node_path");


    ClassDB::bind_method(D_METHOD("set_activation_curve", "activation_curve"), &UtilityAIConsideration::set_activation_curve);
    ClassDB::bind_method(D_METHOD("get_activation_curve"), &UtilityAIConsideration::get_activation_curve);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "activation_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_activation_curve", "get_activation_curve");

    ClassDB::bind_method(D_METHOD("set_activation_input_value", "activation_input_value"), &UtilityAIConsideration::set_activation_input_value);
    ClassDB::bind_method(D_METHOD("get_activation_input_value"), &UtilityAIConsideration::get_activation_input_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "activation_input_value", PROPERTY_HINT_RANGE, "0.0,1.0,allow_lower,allow_greater"), "set_activation_input_value","get_activation_input_value");
    
    /**
    //ClassDB::bind_method(D_METHOD("set_update_method", "update_method"), &UtilityAIConsideration::set_update_method);
    //ClassDB::bind_method(D_METHOD("get_update_method"), &UtilityAIConsideration::get_update_method);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "update_method", PROPERTY_HINT_ENUM, "Process:0,Physics process:1,Manual:2"), "set_update_method","get_update_method");
    

    ClassDB::bind_method(D_METHOD("change_to_state", "target_state_name"), &UtilityAIConsideration::_change_to_state);
    
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIConsideration::_update_current_state);
    /**/
}


// Constructor and destructor.

UtilityAIConsideration::UtilityAIConsideration() {
    _activation_input_value = 0.0;
    _input_sensor = nullptr;
}


UtilityAIConsideration::~UtilityAIConsideration() {
    _input_sensor = nullptr;
}

// Handling functions.



// Getters and Setters.

void UtilityAIConsideration::set_input_sensor_node_path( NodePath input_sensor_node_path ) {
    _input_sensor_node_path = input_sensor_node_path;
}

NodePath UtilityAIConsideration::get_input_sensor_node_path() const {
    return _input_sensor_node_path;
}


void UtilityAIConsideration::set_activation_curve( Ref<Curve> activation_curve ) {
    _activation_curve = activation_curve;
}

Ref<Curve> UtilityAIConsideration::get_activation_curve() const {
    return _activation_curve;
}


void UtilityAIConsideration::set_activation_input_value( double activation_input_value ) {
    _activation_input_value = activation_input_value;
}

double UtilityAIConsideration::get_activation_input_value() const {
    return _activation_input_value;
}

// Godot virtuals.
/**
void UtilityAIConsideration::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}
/**/
void UtilityAIConsideration::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    Node* node = get_node_or_null(_input_sensor_node_path);
    ERR_FAIL_COND_MSG( node == nullptr, "UtilityAIConsideration error, invalid nodepath for the sensor in UtilityAIConsideration '" + get_name() + "'.");
    
    _input_sensor = godot::Object::cast_to<UtilityAISensors>(node);
    ERR_FAIL_COND_MSG( _input_sensor == nullptr, "UtilityAIConsideration error, the assigned node's type was not a UtilityAISensor for UtilityAIConsideration '" + get_name() + "'.");
    
}
/**

void UtilityAIConsideration::_process(double delta ) {
    //if( _update_method != UtilityAIConsideration_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIConsideration::_physics_process(double delta ) {
    //if( _update_method != UtilityAIConsideration_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/



double UtilityAIConsideration::evaluate() { //UtilityAIAgent* agent, double delta) {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    if( _input_sensor != nullptr ) {
        _activation_input_value = _input_sensor->get_sensor_value();
    } //else ERR_FAIL_COND_V_MSG(true, 0.0, "nO INPUT SENSOR!");

    _score = 0.0;
    if (_activation_curve.is_valid()) {
		_score = _activation_curve->sample( _activation_input_value );
	} else {
        _score = _activation_input_value;
    }

    return _score;
}


