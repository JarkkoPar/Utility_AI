#include "UtilityAIBooleanConsideration.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIBooleanConsideration::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_true_score_value", "true_score_value"), &UtilityAIBooleanConsideration::set_true_score_value);
    ClassDB::bind_method(D_METHOD("get_true_score_value"), &UtilityAIBooleanConsideration::get_true_score_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "true_score_value", PROPERTY_HINT_RANGE, "0.0,1.0,or_less,or_greater"), "set_true_score_value","get_true_score_value");

    ClassDB::bind_method(D_METHOD("set_false_score_value", "false_score_value"), &UtilityAIBooleanConsideration::set_false_score_value);
    ClassDB::bind_method(D_METHOD("get_false_score_value"), &UtilityAIBooleanConsideration::get_false_score_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "false_score_value", PROPERTY_HINT_RANGE, "0.0,1.0,or_less,or_greater"), "set_false_score_value","get_false_score_value");

    ClassDB::bind_method(D_METHOD("sample_activation_curve", "input_value"), &UtilityAIBooleanConsideration::sample_activation_curve);
}


// Constructor and destructor.

UtilityAIBooleanConsideration::UtilityAIBooleanConsideration() {
    _true_score_value = 1.0;
    _false_score_value = 0.0;
}


UtilityAIBooleanConsideration::~UtilityAIBooleanConsideration() {
}


// Getters and Setters.

void UtilityAIBooleanConsideration::set_true_score_value( double true_score_value ) {
    _true_score_value = true_score_value;
}

double UtilityAIBooleanConsideration::get_true_score_value() const {
    return _true_score_value;
}

void UtilityAIBooleanConsideration::set_false_score_value( double false_score_value ) {
    _false_score_value = false_score_value;
}

double UtilityAIBooleanConsideration::get_false_score_value() const {
    return _false_score_value;
}


// Godot virtuals.
/**
void UtilityAIBooleanConsideration::_ready() {
    initialize_consideration();
}

/**
void UtilityAIBooleanConsideration::_notification(int p_what) {
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

// Handling functions.
    

void UtilityAIBooleanConsideration::_evaluate_consideration() { 
    _score = sample_activation_curve(get_activation_input_value());
}

double UtilityAIBooleanConsideration::sample_activation_curve( double input_value ) const {
    if( input_value < 0.5 ) return _false_score_value;
    return _true_score_value;
}

