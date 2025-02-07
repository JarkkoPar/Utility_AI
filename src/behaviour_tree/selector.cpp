#include "selector.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// Method binds.

void UtilityAIBTSelector::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("set_is_reactive", "is_reactive"), &UtilityAIBTSelector::set_is_reactive);
	//ClassDB::bind_method(D_METHOD("get_is_reactive"), &UtilityAIBTSelector::get_is_reactive);
	//ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_reactive", PROPERTY_HINT_NONE), "set_is_reactive","get_is_reactive");

	/**
	ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTSelector::set_score);
	ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTSelector::get_score);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
	/**/

	//ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTSelector::set_reset_rule);
	//ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTSelector::get_reset_rule);
	//ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
}

// Constructor and destructor.

UtilityAIBTSelector::UtilityAIBTSelector() {
	_current_child_index = 0;
	//_is_reactive = true;
}

UtilityAIBTSelector::~UtilityAIBTSelector() {
}

// Handling functions.

// Getters and Setters.

/**
void UtilityAIBTSelector::set_is_reactive( bool is_reactive ) {
	_is_reactive = is_reactive;
}

bool UtilityAIBTSelector::get_is_reactive() const {
	return _is_reactive;
}

/**
void UtilityAIBTSelector::set_score( float score ) {
	_score = score;
}

float UtilityAIBTSelector::get_score() const {
	return _score;
}
*/

void UtilityAIBTSelector::reset_bt_node() {
	_current_child_index = 0;
}

int UtilityAIBTSelector::tick(Variant user_data, float delta) {
	if (get_internal_status() == BT_INTERNAL_STATUS_UNTICKED) {
		reset_bt_node();
	}
	set_internal_status(BT_INTERNAL_STATUS_TICKED);
	//if( _is_first_tick ) {
	//    _is_first_tick = false;
	//    emit_signal("btnode_entered", user_data, delta);
	//}
	//emit_signal("btnode_ticked", user_data, delta);
	//while( _current_child_index < get_child_count() ) {
	//    UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_current_child_index));
	//if( btnode != nullptr ) {
	while (_current_child_index < (int)_num_child_btnodes) {
		UtilityAIBehaviourTreeNodes *btnode = _child_btnodes[_current_child_index];
		if (btnode->get_is_active()) {
			int result = btnode->tick(user_data, delta);
			set_tick_result(result);
			if (result == BT_SUCCESS) { //&& _current_child_index == get_child_count() - 1 ) {
				set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
				//emit_signal("btnode_exited", user_data, delta);
				return BT_SUCCESS;
			} else if (result == BT_RUNNING) {
				return BT_RUNNING;
			}
		} //endif is active
		//}//endif node was of correct type
		++_current_child_index;
	} //endwhile children to tick
	//_current_child_index = -1;
	set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
	//emit_signal("btnode_exited", user_data, delta);
	return BT_FAILURE;
}
