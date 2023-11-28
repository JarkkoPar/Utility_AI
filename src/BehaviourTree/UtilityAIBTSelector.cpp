#include "UtilityAIBTSelector.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTSelector::_bind_methods() {
    /**
    ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIBTSelector::set_has_vetoed);
    ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIBTSelector::get_has_vetoed);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTSelector::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTSelector::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

}


// Constructor and destructor.

UtilityAIBTSelector::UtilityAIBTSelector() {
    
}


UtilityAIBTSelector::~UtilityAIBTSelector() {
}

// Handling functions.



// Getters and Setters.

/**
void UtilityAIBTSelector::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIBTSelector::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIBTSelector::set_score( double score ) {
    _score = score;
}

double UtilityAIBTSelector::get_score() const {
    return _score;
}
*/

int UtilityAIBTSelector::tick() { 
    return 0;
}


