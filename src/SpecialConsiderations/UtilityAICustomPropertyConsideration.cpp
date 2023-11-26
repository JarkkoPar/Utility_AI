#include "UtilityAICustomPropertyConsideration.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAICustomPropertyConsideration::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_node_with_property_nodepath", "node_with_property_nodepath"), &UtilityAICustomPropertyConsideration::set_node_with_property_nodepath);
    ClassDB::bind_method(D_METHOD("get_node_with_property_nodepath"), &UtilityAICustomPropertyConsideration::get_node_with_property_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "node_with_property_nodepath", PROPERTY_HINT_NONE), "set_node_with_property_nodepath","get_node_with_property_nodepath");

    ClassDB::bind_method(D_METHOD("set_property_name", "property_name"), &UtilityAICustomPropertyConsideration::set_property_name);
    ClassDB::bind_method(D_METHOD("get_property_name"), &UtilityAICustomPropertyConsideration::get_property_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "property_name", PROPERTY_HINT_NONE), "set_property_name","get_property_name");

    ClassDB::bind_method(D_METHOD("set_property_max_value", "property_max_value"), &UtilityAICustomPropertyConsideration::set_property_max_value);
    ClassDB::bind_method(D_METHOD("get_property_max_value"), &UtilityAICustomPropertyConsideration::get_property_max_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "property_max_value", PROPERTY_HINT_NONE), "set_property_max_value","get_property_max_value");


    ClassDB::bind_method(D_METHOD("sample_activation_curve", "input_value"), &UtilityAICustomPropertyConsideration::sample_activation_curve);
}


// Constructor and destructor.

UtilityAICustomPropertyConsideration::UtilityAICustomPropertyConsideration() {
    _property_max_value = 1.0;
    _one_over_property_max_value = 1.0;
    _node_with_property = nullptr;
}


UtilityAICustomPropertyConsideration::~UtilityAICustomPropertyConsideration() {
}


// Getters and Setters.


void UtilityAICustomPropertyConsideration::set_activation_curve( Ref<Curve> activation_curve ) {
    _activation_curve = activation_curve;
}

Ref<Curve> UtilityAICustomPropertyConsideration::get_activation_curve() const {
    return _activation_curve;
}

void UtilityAICustomPropertyConsideration::set_node_with_property_nodepath( NodePath node_with_property_nodepath ) {
    _node_with_property_nodepath = node_with_property_nodepath;
}
NodePath UtilityAICustomPropertyConsideration::get_node_with_property_nodepath() const {
    return _node_with_property_nodepath;
}

void UtilityAICustomPropertyConsideration::set_property_max_value( double property_max_value ) {
    if( _property_max_value == 0.0 ) return;
    _property_max_value = property_max_value;
    _one_over_property_max_value = 1.0 / _property_max_value;
}

double UtilityAICustomPropertyConsideration::get_property_max_value() const {
    return _property_max_value;
}

void UtilityAICustomPropertyConsideration::set_property_name( StringName property_name ) {
    _property_name = property_name;
}

StringName UtilityAICustomPropertyConsideration::get_property_name() const {
    return _property_name;
}


// Godot virtuals.

void UtilityAICustomPropertyConsideration::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;

    _node_with_property = get_node_or_null(_node_with_property_nodepath);
    initialize_consideration();
}

/**
void UtilityAICustomPropertyConsideration::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			//_clear_monitoring();
		} break;
	}
}
/**/



void UtilityAICustomPropertyConsideration::initialize_consideration() {
    //if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    if( _property_max_value != 0.0 ) {
        _one_over_property_max_value = _property_max_value;
    }
}

// Handling functions.
    
/**
void UtilityAICustomPropertyConsideration::_evaluate_consideration() { 
    //_score = sample_activation_curve(get_activation_input_value());
}
/**/


double UtilityAICustomPropertyConsideration::evaluate() { 
    if( !get_is_active() ) return 0.0;
    if( _node_with_property == nullptr ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;
    if( get_has_vetoed() ) return 0.0;

    if( !this->_get(_property_name, _property_variant_value) ) {
        _score = 0.0;
        return 0.0;
    }

    _score = (double)_property_variant_value * _one_over_property_max_value;

    if(_activation_curve.is_valid()) {
		_score = _activation_curve->sample( _score );
	}
    return _score;
}

double UtilityAICustomPropertyConsideration::sample_activation_curve( double input_value ) const {
    if(_activation_curve.is_valid()) {
		return _activation_curve->sample( input_value );
    }
    return 0.0;
}

