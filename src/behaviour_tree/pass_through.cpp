#include "pass_through.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// Method binds.

void UtilityAIBTPassThrough::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("set_tick_result", "tick_result"), &UtilityAIBTPassThrough::set_tick_result);
	//ClassDB::bind_method(D_METHOD("get_tick_result"), &UtilityAIBTPassThrough::get_tick_result);
	//ADD_PROPERTY(PropertyInfo(Variant::INT, "tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_tick_result","get_tick_result");

	//ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTPassThrough::tick);
}

// Constructor and destructor.

UtilityAIBTPassThrough::UtilityAIBTPassThrough() {
	_tick_result = 1;
	_has_on_tick_method = false;
	_has_tick_method = false;
}

UtilityAIBTPassThrough::~UtilityAIBTPassThrough() {
}

// Getters and Setters.

void UtilityAIBTPassThrough::set_tick_result(int tick_result) {
	_tick_result = tick_result;
	if (_tick_result > 1) {
		_tick_result = 1;
	} else if (_tick_result < -1) {
		_tick_result = -1;
	}
}

int UtilityAIBTPassThrough::get_tick_result() const {
	return _tick_result;
}

// Handling methods.

int UtilityAIBTPassThrough::tick(Variant user_data, float delta) {
	// The passthrough node just calls its tick and then ticks the first
	// behaviour tree node child and returns the result of the child.
	// Otherwise it returns what ever is set as the tick result property.
	set_internal_status(BT_INTERNAL_STATUS_TICKED);
	//if( _is_first_tick ) {
	//    _is_first_tick = false;
	//    emit_signal("btnode_entered", user_data, delta);
	//}
	if (_has_tick_method) {
		godot::Variant return_value = call("tick", user_data, delta);
		if (return_value.get_type() == godot::Variant::Type::INT) {
			_tick_result = (int)return_value;
			if (_tick_result > 1) {
				_tick_result = 1;
			} else if (_tick_result < -1) {
				_tick_result = -1;
			}
		}
	} else if (_has_on_tick_method) {
		godot::Variant return_value = call("on_tick", user_data, delta);
		if (return_value.get_type() == godot::Variant::Type::INT) {
			_tick_result = (int)return_value;
			if (_tick_result > 1) {
				_tick_result = 1;
			} else if (_tick_result < -1) {
				_tick_result = -1;
			}
		}
	}
	//emit_signal("btnode_ticked", user_data, delta);

	//for( int i = 0; i < get_child_count(); ++i ) {
	//    Node* node = get_child(i);
	//    if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
	for (unsigned int i = 0; i < _num_child_btnodes; ++i) {
		UtilityAIBehaviourTreeNodes *btnode = _child_btnodes[i];
		if (!btnode->get_is_active()) {
			continue;
		}
		int result = btnode->tick(user_data, delta);
		if (result != BT_RUNNING) {
			set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
			//emit_signal("btnode_exited", user_data, delta);
		}
		return result;
	} //endfor child ndoes

	//}
	set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
	//emit_signal("btnode_exited", user_data, delta);
	return _tick_result;
}

void UtilityAIBTPassThrough::_notification(int p_what) {
	if (p_what == NOTIFICATION_POST_ENTER_TREE) {
		_has_on_tick_method = has_method("on_tick");
		_has_tick_method = has_method("tick");

	} else if (p_what == NOTIFICATION_CHILD_ORDER_CHANGED) {
		update_child_vectors();
	}
}
