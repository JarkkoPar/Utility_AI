#include "behaviour.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "consideration.h"
#include "consideration_group.h"

using namespace godot;

// Method binds.

void UtilityAIBehaviour::_bind_methods() {
	ADD_SUBGROUP("Configuration", "");

	ClassDB::bind_method(D_METHOD("set_behaviour_id", "behaviour_id"), &UtilityAIBehaviour::set_behaviour_id);
	ClassDB::bind_method(D_METHOD("get_behaviour_id"), &UtilityAIBehaviour::get_behaviour_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "behaviour_id", PROPERTY_HINT_NONE), "set_behaviour_id", "get_behaviour_id");

	ClassDB::bind_method(D_METHOD("set_can_be_interrupted", "can_be_interrupted"), &UtilityAIBehaviour::set_can_be_interrupted);
	ClassDB::bind_method(D_METHOD("get_can_be_interrupted"), &UtilityAIBehaviour::get_can_be_interrupted);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "can_be_interrupted", PROPERTY_HINT_NONE), "set_can_be_interrupted", "get_can_be_interrupted");

	ClassDB::bind_method(D_METHOD("set_cooldown_seconds", "cooldown_seconds"), &UtilityAIBehaviour::set_cooldown_seconds);
	ClassDB::bind_method(D_METHOD("get_cooldown_seconds"), &UtilityAIBehaviour::get_cooldown_seconds);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown_seconds", PROPERTY_HINT_RANGE, "0.0,3600.0,or_greater,suffix:seconds"), "set_cooldown_seconds", "get_cooldown_seconds");

	ClassDB::bind_method(D_METHOD("set_cooldown_turns", "cooldown_turns"), &UtilityAIBehaviour::set_cooldown_turns);
	ClassDB::bind_method(D_METHOD("get_cooldown_turns"), &UtilityAIBehaviour::get_cooldown_turns);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cooldown_turns", PROPERTY_HINT_RANGE, "0,64,or_greater,suffix:turns"), "set_cooldown_turns", "get_cooldown_turns");

	ClassDB::bind_method(D_METHOD("set_considerations", "considerations"), &UtilityAIBehaviour::set_considerations);
	ClassDB::bind_method(D_METHOD("get_considerations"), &UtilityAIBehaviour::get_considerations);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "considerations", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "UtilityAIConsiderationResources")), "set_considerations", "get_considerations");

	ADD_SUBGROUP("Debugging", "");

	//ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviour::set_score);
	//ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviour::get_score);
	//ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"-100.0,100.0"), "set_score","get_score");

	ClassDB::bind_method(D_METHOD("set_current_action_index", "current_action_index"), &UtilityAIBehaviour::set_current_action_index);
	ClassDB::bind_method(D_METHOD("get_current_action_index"), &UtilityAIBehaviour::get_current_action_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current_action_index", PROPERTY_HINT_RANGE, "0,256"), "set_current_action_index", "get_current_action_index");

	// Signals.
	ADD_SIGNAL(MethodInfo("behaviour_entered"));
	ADD_SIGNAL(MethodInfo("physics_frame_tick", PropertyInfo(Variant::FLOAT, "delta")));
	ADD_SIGNAL(MethodInfo("idle_frame_tick", PropertyInfo(Variant::FLOAT, "delta")));
	ADD_SIGNAL(MethodInfo("behaviour_exited"));
}

// Constructor and destructor.

UtilityAIBehaviour::UtilityAIBehaviour() {
	//_current_action_node = nullptr;
	_score = 0.0f;
	_cooldown_seconds = 0.0f;
	_current_cooldown_seconds = 0.0f;
	_cooldown_turns = 0;
	_current_cooldown_turns = 0;
	_current_action_index = 0;
	_can_be_interrupted = true;
	_behaviour_id = 0;
	_num_child_considerations = 0;
}

UtilityAIBehaviour::~UtilityAIBehaviour() {
}

// Handling functions.

// Getters and Setters.

void UtilityAIBehaviour::set_behaviour_id(int behaviour_id) {
	_behaviour_id = behaviour_id;
}

int UtilityAIBehaviour::get_behaviour_id() const {
	return _behaviour_id;
}

void UtilityAIBehaviour::set_can_be_interrupted(bool can_be_interrupted) {
	_can_be_interrupted = can_be_interrupted;
}

bool UtilityAIBehaviour::get_can_be_interrupted() const {
	return _can_be_interrupted;
}

/*
void UtilityAIBehaviour::set_score( float score ) {
	_score = score;
}

float UtilityAIBehaviour::get_score() const {
	return _score;
}
*/
void UtilityAIBehaviour::set_cooldown_seconds(float cooldown_seconds) {
	_cooldown_seconds = cooldown_seconds;
}

float UtilityAIBehaviour::get_cooldown_seconds() const {
	return _cooldown_seconds;
}

void UtilityAIBehaviour::set_cooldown_turns(int cooldown_turns) {
	_cooldown_turns = cooldown_turns;
}

int UtilityAIBehaviour::get_cooldown_turns() const {
	return _cooldown_turns;
}

void UtilityAIBehaviour::set_current_action_index(int current_action_index) {
	_current_action_index = current_action_index;
}

int UtilityAIBehaviour::get_current_action_index() const {
	return _current_action_index;
}

/**
void UtilityAIBehaviour::set_considerations( TypedArray<UtilityAIConsiderationResources> considerations ) {
	_considerations = considerations;
}

TypedArray<UtilityAIConsiderationResources> UtilityAIBehaviour::get_considerations() const {
	return _considerations;
}
/**/

// Godot virtuals.
/**
void UtilityAIBehaviour::_notification(int p_what) {

	if( p_what == NOTIFICATION_CHILD_ORDER_CHANGED ) {
		_child_considerations.clear();
		int num_children = get_child_count();
		for( int i = 0; i < num_children; ++i ) {
			if( UtilityAIConsiderations* cons = godot::Object::cast_to<UtilityAIConsiderations>(get_child(i))) {
				_child_considerations.push_back(cons);
			}
		}//endfor child nodes
		_num_child_considerations = (unsigned int)_child_considerations.size();
	}
	/**
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			// Entered the tree.
		} break;
		case NOTIFICATION_EXIT_TREE: {

		} break;
	}

}
/**/

void UtilityAIBehaviour::_ready() {
	if (!get_is_active())
		return;
	if (Engine::get_singleton()->is_editor_hint())
		return;

	// Get the considerations and actions.
}

void UtilityAIBehaviour::_process(double delta) {
	if (!get_is_active())
		return;
	if (Engine::get_singleton()->is_editor_hint())
		return;
	if (_current_cooldown_seconds > 0.0f) {
		_current_cooldown_seconds -= delta;
		if (_current_cooldown_seconds < 0.0f)
			_current_cooldown_seconds = 0.0f;
	}
}

// Handling functions.

float UtilityAIBehaviour::evaluate() {
#ifdef DEBUG_ENABLED
	_last_evaluated_timestamp = godot::Time::get_singleton()->get_ticks_usec();
#endif

	// If the behaviour is on cooldown, it cannot be chosen.
	if (_current_cooldown_seconds > 0.0f)
		return 0.0f;
	if (_current_cooldown_turns > 0) {
		--_current_cooldown_turns;
		return 0.0f;
	}

	_score = 0.0f;
	bool has_vetoed = false;
	// Evaluate the consideration resources (if any).
	int num_resources = _considerations.size();
	for (int i = 0; i < num_resources; ++i) {
		UtilityAIConsiderationResources *consideration_resource = godot::Object::cast_to<UtilityAIConsiderationResources>(_considerations[i]);
		if (consideration_resource == nullptr) {
			continue;
		}
		if (!consideration_resource->get_is_active()) {
			continue;
		}
		float child_score = consideration_resource->evaluate(has_vetoed, this);
		if (has_vetoed) {
			return 0.0f; // A consideration vetoed.
		}
		switch (_evaluation_method) {
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Min: {
				if (i == 0)
					_score = child_score;
				if (child_score < _score)
					_score = child_score;
			} break;
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Max: {
				if (i == 0)
					_score = child_score;
				if (child_score > _score)
					_score = child_score;
			} break;
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Multiply: {
				if (i == 0)
					_score = child_score;
				else
					_score *= child_score;
				// If after multiplication we are at 0.0, then none of the
				// other considerations will ever change the result, so bail.
				if (_score == 0.0) {
					return 0.0;
				}
			} break;
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::FirstNonZero: {
				if (child_score > 0.0) {
					_score = child_score;
					return _score;
				}
			} break;
			default:
				_score += child_score;
		} //end switch evaluation method
	}

	// Evaluate the child nodes.
	//int num_children = get_child_count();
	//for( int i = 0; i < num_children; ++i ) {
	//UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(get_child(i));
	float child_score = 0.0f;
	for (unsigned int i = 0; i < _num_child_considerations; ++i) {
		UtilityAIConsiderations *considerationNode = _child_considerations[i];
		//if( considerationNode == nullptr ) continue;
		if (!considerationNode->get_is_active())
			continue;
		child_score = considerationNode->evaluate();
		if (considerationNode->get_has_vetoed()) {
			_score = 0.0f;
			return 0.0f; // The consideration vetoed this behaviour.
		}
		switch (_evaluation_method) {
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Min: {
				if (i == 0)
					_score = child_score;
				if (child_score < _score)
					_score = child_score;
			} break;
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Max: {
				if (i == 0)
					_score = child_score;
				if (child_score > _score)
					_score = child_score;
			} break;
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Multiply: {
				if (i == 0)
					_score = child_score;
				else
					_score *= child_score;
				// If after multiplication we are at 0.0, then none of the
				// other considerations will ever change the result, so bail.
				if (_score == 0.0) {
					return 0.0;
				}
			} break;
			case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::FirstNonZero: {
				if (child_score > 0.0) {
					_score = child_score;
					return _score;
				}
			} break;
			default:
				_score += child_score;
		} //end switch evaluation method
	} //endfor children

	return _score;
}

void UtilityAIBehaviour::start_behaviour() {
	_current_cooldown_seconds = _cooldown_seconds;
	_current_cooldown_turns = _cooldown_turns;
	_current_action_index = 0;
	//_current_action_node = nullptr;
	//_current_action_node = update_behaviour();
	emit_signal("behaviour_entered");
	update_behaviour();
}

void UtilityAIBehaviour::end_behaviour() {
	emit_signal("behaviour_exited");
	_current_action_index = 0;
}

UtilityAIAction *UtilityAIBehaviour::update_behaviour() {
	//WARN_PRINT("AIBehaviour::update_behaviour(): stepping actions. " + get_name());
	return godot::Object::cast_to<UtilityAIAction>(step_actions());
}

Node *UtilityAIBehaviour::step_actions() {
	//WARN_PRINT("UtilityAIBehaviour::step_actions() " + get_name());
	if (_current_action_index >= get_child_count())
		return nullptr;

	// Check if the node is an action.
	Node *current_node = get_child(_current_action_index);
	if (UtilityAIAction *current_action = godot::Object::cast_to<UtilityAIAction>(current_node)) {
		if (!current_action->get_is_finished()) {
			return current_node;
		}
		// If the action fails, clean up and end stepping.
		if (current_action->get_has_failed()) {
			current_action->end_action();
			return nullptr;
		}
		current_action->end_action();
	} else {
		//WARN_PRINT("UtilityAIBehaviour::step_actions(): Checking if the current index is an action group.");
		// Check if the current index has an action group and if that group has a follow-up action.
		if (UtilityAIActionGroup *current_action_group = godot::Object::cast_to<UtilityAIActionGroup>(current_node)) {
			//WARN_PRINT("UtilityAIBehaviour::step_actions(): Yes, current action is an action group. Stepping...");
			current_action = godot::Object::cast_to<UtilityAIAction>(current_action_group->step_actions());
			//if( _current_action_node == nullptr ) WARN_PRINT("UtilityAIBehaviour::step_actions(): group sent back a NULL action pointer.");
			if (current_action != nullptr)
				return current_action;
			//WARN_PRINT("UtilityAIBehaviour::step_actions(): Action has completed, ending action for the action group.");
			// If the group fails, clean up and end stepping.
			if (current_action_group->get_has_failed()) {
				current_action_group->end_action();
				return nullptr;
			}
			current_action_group->end_action();
			//WARN_PRINT("UtilityAIBehaviour::step_actions(): Action group action ended.");
		} //endif current node index is action group
	} //endif current node index is an action
	//WARN_PRINT("UtilityAIBehaviour::step_actions(): Finding a new action...");

	++_current_action_index;
	while (_current_action_index < get_child_count()) {
		current_node = get_child(_current_action_index);
		if (current_node != nullptr) {
			if (UtilityAIAction *action_node = godot::Object::cast_to<UtilityAIAction>(current_node)) {
				//WARN_PRINT("UtilityAIBehaviour::step_actions(): Found an action, starting the action...");
				if (action_node->get_is_active()) {
					//_current_action_node = action_node;
					bool action_start_result = action_node->start_action();
					//if( !action_start_result ) return nullptr;
					//WARN_PRINT("UtilityAIBehaviour::step_actions(): Done, returning action node.");
					return action_node;
				} //endif action is active
			} else if (UtilityAIActionGroup *action_group = godot::Object::cast_to<UtilityAIActionGroup>(current_node)) {
				if (action_group->get_is_active()) {
					//WARN_PRINT("UtilityAIBehaviour::step_actions(): Found an action group, starting the action group." + get_name());
					bool action_group_start_result = action_group->start_action();
					//if( !action_group_start_result ) return nullptr;
					//WARN_PRINT("UtilityAIBehaviour::step_actions(): Stepping it to find the sub action...");
					action_node = godot::Object::cast_to<UtilityAIAction>(action_group->step_actions());
					//if( _current_action_node == nullptr ) {
					//WARN_PRINT("UtilityAIBehaviour::step_actions(): Stepping function returned NULL action pointer.");
					//}
					if (action_node != nullptr) {
						//WARN_PRINT("UtilityAIBehaviour::step_actions(): Stepping function returned a valid action pointer." + _current_action_node->get_name());
						action_node->start_action();
						return action_node;
					}
				} //endif action group is active
			} // endif is action or action_group
		} // endif node is not nullptr
		++_current_action_index;
	} //endwhile action index in bounds

	//WARN_PRINT("UtilityAIBehaviour::step_actions(): NO ACTION FOUND! " + get_name());
	return nullptr;
}
