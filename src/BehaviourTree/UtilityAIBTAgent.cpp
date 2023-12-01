#include "UtilityAIBTAgent.h"
#include "UtilityAIBehaviourTreeNodes.h"
#include "../UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTAgent::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIBTAgent::set_has_vetoed);
    //ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIBTAgent::get_has_vetoed);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    
    /**
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTAgent::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTAgent::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

    ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAIBTAgent::tick);
}


// Constructor and destructor.

UtilityAIBTAgent::UtilityAIBTAgent() {
    
}


UtilityAIBTAgent::~UtilityAIBTAgent() {
}

// Handling functions.



// Getters and Setters.

/**
void UtilityAIBTAgent::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIBTAgent::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIBTAgent::set_score( double score ) {
    _score = score;
}

double UtilityAIBTAgent::get_score() const {
    return _score;
}
*/

int UtilityAIBTAgent::tick(Variant user_data, double delta) { 
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAISensors* sensor = godot::Object::cast_to<UtilityAISensors>(node) ) {
            sensor->evaluate_sensor_value();
            continue;
        }
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
            int result = btnode->tick(user_data, delta);
            return result;
        }
    }
    return -1;
}


