#include "utility_ai.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAI::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAI::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAI::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
}


// Constructor and destructor.

UtilityAI::UtilityAI() {
    _is_active = true;
}


UtilityAI::~UtilityAI() {
}

// Handling functions.



// Getters and Setters.

void UtilityAI::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAI::get_is_active() const {
    return _is_active;
}
