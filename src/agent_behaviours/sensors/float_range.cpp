#include "float_range.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;

// Method binds.

void UtilityAIFloatRangeSensor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_range_value", "range_value"), &UtilityAIFloatRangeSensor::set_range_value);
    ClassDB::bind_method(D_METHOD("get_range_value"), &UtilityAIFloatRangeSensor::get_range_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "range_value", PROPERTY_HINT_NONE), "set_range_value","get_range_value");    

    ClassDB::bind_method(D_METHOD("set_range_min_value", "range_min_value"), &UtilityAIFloatRangeSensor::set_range_min_value);
    ClassDB::bind_method(D_METHOD("get_range_min_value"), &UtilityAIFloatRangeSensor::get_range_min_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "range_min_value", PROPERTY_HINT_NONE), "set_range_min_value","get_range_min_value");    

    ClassDB::bind_method(D_METHOD("set_range_max_value", "range_max_value"), &UtilityAIFloatRangeSensor::set_range_max_value);
    ClassDB::bind_method(D_METHOD("get_range_max_value"), &UtilityAIFloatRangeSensor::get_range_max_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "range_max_value", PROPERTY_HINT_NONE), "set_range_max_value","get_range_max_value");    
}


// Constructor and destructor.

UtilityAIFloatRangeSensor::UtilityAIFloatRangeSensor() {
    _range_max_value = 100.0f;
    _range_min_value = 0.0f;
    _range_value = 0.0f;
    _range_length = 100.0f;
    _one_over_range_length = 1.0f / _range_length;
}


UtilityAIFloatRangeSensor::~UtilityAIFloatRangeSensor() {
}

// Handling functions.

float UtilityAIFloatRangeSensor::evaluate_sensor_value() {
    /**
    if( get_use_absolute_value() ) {
        // Absolute value, so make sure that it is within the interval.
        float range_result = _range_value;
        if( range_result < _range_min_value ) {
            range_result = _range_min_value;
        }else if( range_result > _range_max_value ) {
            range_result = _range_max_value;
        }
        set_sensor_value(range_result);
        return get_sensor_value();
    }
    /**/
    // Relative value, so calculate the position within the interval.
    float range_result = ((_range_value - _range_min_value)) * _one_over_range_length;
    if( range_result < 0.0f ) {
        range_result = 0.0f;
    } else if( range_result > 1.0f ) {
        range_result = 1.0f;
    }
    set_sensor_value(range_result);
    return get_sensor_value();
}

// Getters and Setters.

void UtilityAIFloatRangeSensor::set_range_min_value( float range_min_value ) {
    if( _range_min_value == _range_max_value ) {
        return;
    }
    _range_min_value = range_min_value;
    _range_length = _range_max_value - _range_min_value;
    if( _range_length != 0.0f ) {
        _one_over_range_length = 1.0f / _range_length;
    } else {
        _one_over_range_length = 0.0f;
    }
}

float UtilityAIFloatRangeSensor::get_range_min_value() const {
    return _range_min_value;
}

void UtilityAIFloatRangeSensor::set_range_max_value( float range_max_value ) {
    if( _range_min_value == _range_max_value ) {
        return;
    }
    _range_max_value = range_max_value;
    _range_length = _range_max_value - _range_min_value;
    if( _range_length != 0.0f ) {
        _one_over_range_length = 1.0f / _range_length;
    } else {
        _one_over_range_length = 0.0f;
    }
}

float UtilityAIFloatRangeSensor::get_range_max_value() const {
    return _range_max_value;
}

void UtilityAIFloatRangeSensor::set_range_value( float range_value ) {
    _range_value = range_value;
    if( _range_value < _range_min_value ) {
        _range_value = _range_min_value;
    }else if( _range_value > _range_max_value ) {
        _range_value = _range_max_value;
    }
}

float UtilityAIFloatRangeSensor::get_range_value() const {
    return _range_value;
}

