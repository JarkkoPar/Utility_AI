#include "UtilityAIBehaviourTreeNodes.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBehaviourTreeNodes::_bind_methods() {
    /**
    ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIBehaviourTreeNodes::set_has_vetoed);
    ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIBehaviourTreeNodes::get_has_vetoed);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviourTreeNodes::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviourTreeNodes::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

}


// Constructor and destructor.

UtilityAIBehaviourTreeNodes::UtilityAIBehaviourTreeNodes() {
    
}


UtilityAIBehaviourTreeNodes::~UtilityAIBehaviourTreeNodes() {
}

// Handling functions.



// Getters and Setters.

/**
void UtilityAIBehaviourTreeNodes::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIBehaviourTreeNodes::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIBehaviourTreeNodes::set_score( double score ) {
    _score = score;
}

double UtilityAIBehaviourTreeNodes::get_score() const {
    return _score;
}
*/

int UtilityAIBehaviourTreeNodes::tick() { 
    return 0;
}


