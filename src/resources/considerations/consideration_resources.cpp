#include "consideration_resources.h"


using namespace godot;


UtilityAIConsiderationResources::UtilityAIConsiderationResources() {

}


UtilityAIConsiderationResources::~UtilityAIConsiderationResources() {
    
}


void UtilityAIConsiderationResources::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAIConsiderationResources::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAIConsiderationResources::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
}

// Getters and setters.


void UtilityAIConsiderationResources::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAIConsiderationResources::get_is_active() const {
    return _is_active;
}

void  UtilityAIConsiderationResources::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}
bool  UtilityAIConsiderationResources::get_has_vetoed() const {
    return _has_vetoed;
}


// Handling methods.

double UtilityAIConsiderationResources::evaluate() { 
    return 0.0;
}

