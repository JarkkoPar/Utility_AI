#include "consideration_resources.h"

using namespace godot;

UtilityAIConsiderationResources::UtilityAIConsiderationResources() {
	_is_active = true;
	//_has_vetoed = false;
}

UtilityAIConsiderationResources::~UtilityAIConsiderationResources() {
}

void UtilityAIConsiderationResources::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAIConsiderationResources::set_is_active);
	ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAIConsiderationResources::get_is_active);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active", "get_is_active");

	//ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIConsiderationResources::set_has_vetoed);
	//ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIConsiderationResources::get_has_vetoed);
	//ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
}

// Getters and setters.

void UtilityAIConsiderationResources::set_is_active(bool is_active) {
	_is_active = is_active;
}

bool UtilityAIConsiderationResources::get_is_active() const {
	return _is_active;
}

/**
void  UtilityAIConsiderationResources::set_has_vetoed( bool has_vetoed ) {
	_has_vetoed = has_vetoed;
}
bool  UtilityAIConsiderationResources::get_has_vetoed() const {
	return _has_vetoed;
}
/**/

// Handling methods.

float UtilityAIConsiderationResources::evaluate(bool &has_vetoed, Node *parent_node) {
	has_vetoed = false;
	return 0.0;
}
