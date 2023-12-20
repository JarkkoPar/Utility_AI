#include "consideration_resource.h"
//#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/window.hpp"

using namespace godot;


UtilityAIConsiderationResource::UtilityAIConsiderationResource() {
    _input_sensor = nullptr;

}


UtilityAIConsiderationResource::~UtilityAIConsiderationResource() {
    _input_sensor = nullptr;
}


void UtilityAIConsiderationResource::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_input_sensor_nodepath", "input_sensor_nodepath"), &UtilityAIConsiderationResource::set_input_sensor_nodepath);
    ClassDB::bind_method(D_METHOD("get_input_sensor_nodepath"), &UtilityAIConsiderationResource::get_input_sensor_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "input_sensor_nodepath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "UtilityAISensors"), "set_input_sensor_nodepath", "get_input_sensor_nodepath");


    ClassDB::bind_method(D_METHOD("set_activation_curve", "activation_curve"), &UtilityAIConsiderationResource::set_activation_curve);
    ClassDB::bind_method(D_METHOD("get_activation_curve"), &UtilityAIConsiderationResource::get_activation_curve);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "activation_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_activation_curve", "get_activation_curve");

    ClassDB::bind_method(D_METHOD("sample_activation_curve", "input_value"), &UtilityAIConsiderationResource::sample_activation_curve);
}

// Getters and setters.

void UtilityAIConsiderationResource::set_input_sensor_nodepath( NodePath input_sensor_nodepath ) {
    _input_sensor_nodepath = input_sensor_nodepath;
}

NodePath UtilityAIConsiderationResource::get_input_sensor_nodepath() const {
    return _input_sensor_nodepath;
}


void UtilityAIConsiderationResource::set_activation_curve( Ref<Curve> activation_curve ) {
    _activation_curve = activation_curve;
}

Ref<Curve> UtilityAIConsiderationResource::get_activation_curve() const {
    return _activation_curve;
}


// Handling methods.

double UtilityAIConsiderationResource::evaluate(bool& has_vetoed, Node* parent_node) { 
    if( _input_sensor == nullptr ) {
        _input_sensor = godot::Object::cast_to<UtilityAISensors>(parent_node->get_node_or_null(_input_sensor_nodepath));
    }

    double input_value = 0.0;
    if( _input_sensor != nullptr ) {
        input_value = _input_sensor->get_sensor_value();
    }

    double score = 0.0;
    if( has_method("eval")) {
        Variant return_value = call("eval", input_value);
        if( return_value.get_type() == Variant::Type::ARRAY ) {
            Array retarray = return_value;
            if( retarray.size() > 0 ) {
                score = retarray[0];
            }
            if( retarray.size() > 1 ) {
                has_vetoed = retarray[1];
            }
        } else if( return_value.get_type() == Variant::Type::FLOAT) {
            score = return_value;
        }
        return score;
    }

    if(_activation_curve.is_valid()) {
		score = _activation_curve->sample( input_value );
	} else {
        score = input_value;
    }

    return score;
}


double UtilityAIConsiderationResource::sample_activation_curve( double input_value ) const {
    if(_activation_curve.is_valid()) {
		return _activation_curve->sample( input_value );
    }
    return 0.0; //input_value;
}
