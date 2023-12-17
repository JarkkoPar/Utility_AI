#include "int_range.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;

// Method binds.

void UtilityAIIntRangeSensor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_range_value", "range_value"), &UtilityAIIntRangeSensor::set_range_value);
    ClassDB::bind_method(D_METHOD("get_range_value"), &UtilityAIIntRangeSensor::get_range_value);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "range_value", PROPERTY_HINT_NONE), "set_range_value","get_range_value");    

    ClassDB::bind_method(D_METHOD("set_range_min_value", "range_min_value"), &UtilityAIIntRangeSensor::set_range_min_value);
    ClassDB::bind_method(D_METHOD("get_range_min_value"), &UtilityAIIntRangeSensor::get_range_min_value);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "range_min_value", PROPERTY_HINT_NONE), "set_range_min_value","get_range_min_value");    

    ClassDB::bind_method(D_METHOD("set_range_max_value", "range_max_value"), &UtilityAIIntRangeSensor::set_range_max_value);
    ClassDB::bind_method(D_METHOD("get_range_max_value"), &UtilityAIIntRangeSensor::get_range_max_value);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "range_max_value", PROPERTY_HINT_NONE), "set_range_max_value","get_range_max_value");    
}


// Constructor and destructor.

UtilityAIIntRangeSensor::UtilityAIIntRangeSensor() {
    _range_max_value = 100;
    _range_min_value = 0;
    _range_value = 0;
    _range_length = 100;
    _one_over_range_length = 1.0 / (double)_range_length;
}


UtilityAIIntRangeSensor::~UtilityAIIntRangeSensor() {
}

// Handling functions.

double UtilityAIIntRangeSensor::evaluate_sensor_value() {
    /**
    if( get_use_absolute_value() ) {
        // Absolute value, so make sure that it is within the interval.
        int range_result = _range_value;
        if( range_result < _range_min_value ) {
            range_result = _range_min_value;
        }else if( range_result > _range_max_value ) {
            range_result = _range_max_value;
        }
        set_sensor_value((double)range_result);
        return get_sensor_value();
    }
    /**/
    // Relative value, so calculate the position within the interval.
    double range_result = ((double)(_range_value - _range_min_value)) * _one_over_range_length;
    if( range_result < 0.0 ) {
        range_result = 0.0;
    } else if( range_result > 1.0 ) {
        range_result = 1.0;
    }
    set_sensor_value(range_result);
    return get_sensor_value();
}

// Getters and Setters.

void UtilityAIIntRangeSensor::set_range_min_value( int range_min_value ) {
    if( _range_min_value == _range_max_value ) {
        return;
    }
    _range_min_value = range_min_value;
    _range_length = _range_max_value - _range_min_value;
    if( _range_length != 0 ) {
        _one_over_range_length = 1.0 / (double)_range_length;
    } else {
        _one_over_range_length = 0.0;
    }
}

int UtilityAIIntRangeSensor::get_range_min_value() const {
    return _range_min_value;
}

void UtilityAIIntRangeSensor::set_range_max_value( int range_max_value ) {
    if( _range_min_value == _range_max_value ) {
        return;
    }
    _range_max_value = range_max_value;
    _range_length = _range_max_value - _range_min_value;
    if( _range_length != 0 ) {
        _one_over_range_length = 1.0 / (double)_range_length;
    } else {
        _one_over_range_length = 0.0;
    }
}

int UtilityAIIntRangeSensor::get_range_max_value() const {
    return _range_max_value;
}

void UtilityAIIntRangeSensor::set_range_value( int range_value ) {
    _range_value = range_value;
    if( _range_value < _range_min_value ) {
        _range_value = _range_min_value;
    }else if( _range_value > _range_max_value ) {
        _range_value = _range_max_value;
    }
}

int UtilityAIIntRangeSensor::get_range_value() const {
    return _range_value;
}

