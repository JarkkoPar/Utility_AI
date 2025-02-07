#include "agent.h"
#include "behaviour.h"
#include "sensors.h"
//#include "behaviour_group.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

#ifdef DEBUG_ENABLED
#include "../debugger/debugger_overlay.h"
#endif

using namespace godot;

// Method binds.

void UtilityAIAgent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_current_behaviour_group_node"), &UtilityAIAgent::set_current_behaviour_group_node);
	ClassDB::bind_method(D_METHOD("get_current_behaviour_group_node"), &UtilityAIAgent::get_current_behaviour_group_node);

	ClassDB::bind_method(D_METHOD("set_current_behaviour_node"), &UtilityAIAgent::set_current_behaviour_node);
	ClassDB::bind_method(D_METHOD("get_current_behaviour_node"), &UtilityAIAgent::get_current_behaviour_node);

	ClassDB::bind_method(D_METHOD("set_current_action_node"), &UtilityAIAgent::set_current_action_node);
	ClassDB::bind_method(D_METHOD("get_current_action_node"), &UtilityAIAgent::get_current_action_node);

	ClassDB::bind_method(D_METHOD("evaluate_options", "delta"), &UtilityAIAgent::evaluate_options);
	ClassDB::bind_method(D_METHOD("update_current_behaviour"), &UtilityAIAgent::update_current_behaviour);
	ClassDB::bind_method(D_METHOD("abort_current_behaviour"), &UtilityAIAgent::abort_current_behaviour);

	ClassDB::bind_method(D_METHOD("set_num_behaviours_to_select", "num_behaviours_to_select"), &UtilityAIAgent::set_num_behaviours_to_select);
	ClassDB::bind_method(D_METHOD("get_num_behaviours_to_select"), &UtilityAIAgent::get_num_behaviours_to_select);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_behaviours_to_select", PROPERTY_HINT_RANGE, "1,16"), "set_num_behaviours_to_select", "get_num_behaviours_to_select");

	ClassDB::bind_method(D_METHOD("set_thinking_delay_in_seconds", "thinking_delay_in_seconds"), &UtilityAIAgent::set_thinking_delay_in_seconds);
	ClassDB::bind_method(D_METHOD("get_thinking_delay_in_seconds"), &UtilityAIAgent::get_thinking_delay_in_seconds);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thinking_delay_in_seconds", PROPERTY_HINT_RANGE, "0.0,3600.0,or_greater,suffix:seconds"), "set_thinking_delay_in_seconds", "get_thinking_delay_in_seconds");

	ClassDB::bind_method(D_METHOD("set_current_behaviour_bias", "current_behaviour_bias"), &UtilityAIAgent::set_current_behaviour_bias);
	ClassDB::bind_method(D_METHOD("get_current_behaviour_bias"), &UtilityAIAgent::get_current_behaviour_bias);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "current_behaviour_bias", PROPERTY_HINT_RANGE, "-1.0,1.0,or_greater"), "set_current_behaviour_bias", "get_current_behaviour_bias");

	ADD_SUBGROUP("Debugging", "");

	ClassDB::bind_method(D_METHOD("set_top_scoring_behaviour_name", "top_scoring_behaviour_name"), &UtilityAIAgent::set_top_scoring_behaviour_name);
	ClassDB::bind_method(D_METHOD("get_top_scoring_behaviour_name"), &UtilityAIAgent::get_top_scoring_behaviour_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "top_scoring_behaviour_name", PROPERTY_HINT_NONE), "set_top_scoring_behaviour_name", "get_top_scoring_behaviour_name");

	ClassDB::bind_method(D_METHOD("set_current_behaviour_name", "current_behaviour_name"), &UtilityAIAgent::set_current_behaviour_name);
	ClassDB::bind_method(D_METHOD("get_current_behaviour_name"), &UtilityAIAgent::get_current_behaviour_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "current_behaviour_name", PROPERTY_HINT_NONE), "set_current_behaviour_name", "get_current_behaviour_name");

#ifdef DEBUG_ENABLED
	ClassDB::bind_method(D_METHOD("set_total_evaluate_options_usec", "total_evaluate_options_usec"), &UtilityAIAgent::set_total_evaluate_options_usec);
	ClassDB::bind_method(D_METHOD("get_total_evaluate_options_usec"), &UtilityAIAgent::get_total_evaluate_options_usec);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "total_evaluate_options_usec", PROPERTY_HINT_NONE), "set_total_evaluate_options_usec", "get_total_evaluate_options_usec");

	ClassDB::bind_method(D_METHOD("set_total_update_behaviour_usec", "total_update_behaviour_usec"), &UtilityAIAgent::set_total_update_behaviour_usec);
	ClassDB::bind_method(D_METHOD("get_total_update_behaviour_usec"), &UtilityAIAgent::get_total_update_behaviour_usec);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "total_update_behaviour_usec", PROPERTY_HINT_NONE), "set_total_update_behaviour_usec", "get_total_update_behaviour_usec");
#endif

	// Add all signals.

	ADD_SIGNAL(MethodInfo("behaviour_group_changed", PropertyInfo(Variant::OBJECT, "behaviour_group_node")));
	ADD_SIGNAL(MethodInfo("behaviour_group_exited", PropertyInfo(Variant::OBJECT, "behaviour_group_node")));

	ADD_SIGNAL(MethodInfo("behaviour_changed", PropertyInfo(Variant::OBJECT, "behaviour_node")));
	ADD_SIGNAL(MethodInfo("behaviour_exited", PropertyInfo(Variant::OBJECT, "behaviour_node")));

	ADD_SIGNAL(MethodInfo("action_changed", PropertyInfo(Variant::OBJECT, "action_node")));
	ADD_SIGNAL(MethodInfo("action_exited", PropertyInfo(Variant::OBJECT, "action_node")));
}

// Constructor and destructor.

UtilityAIAgent::UtilityAIAgent() {
	_rng.instantiate();

	_current_behaviour_group_node = nullptr;
	_current_behaviour_node = nullptr;
	_num_behaviours_to_select = 1;
	_num_possible_behaviours = 0;
	for (int i = 0; i < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS; ++i) {
		//_top_scoring_behaviours[i] = -1;
		_top_scoring_behaviours_score[i] = 0.0f;
		_top_scoring_behaviours_nodes[i] = nullptr;
		_top_scoring_behaviours_group_nodes[i] = nullptr;
	}
	_top_scoring_behaviour_name = "";

	_current_action_node = nullptr;

	_thinking_delay_in_seconds = 1.0f; // One second delay in thinking of options.
	_thinking_delay_in_seconds_current_timer = 0.0f;
	_current_behaviour_bias = 0.1f;

	_rng->set_seed(time(0));

#ifdef DEBUG_ENABLED
	_total_evaluate_options_usec = 0;
	_total_update_behaviour_usec = 0;
#endif

	_num_child_behaviours = 0;
	_num_child_sensors = 0;
}

UtilityAIAgent::~UtilityAIAgent() {
	_current_behaviour_node = nullptr;
	_current_action_node = nullptr;
	for (int i = 0; i < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS; ++i) {
		_top_scoring_behaviours_nodes[i] = nullptr;
	}
}

// Handling functions.

void UtilityAIAgent::evaluate_options(float delta) {
	uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
#ifdef DEBUG_ENABLED
	_last_evaluated_timestamp = method_start_time_usec;
#endif
	if (!get_is_active())
		return;
	if (Engine::get_singleton()->is_editor_hint())
		return;
	int num_children = get_child_count();
	if (num_children < 1)
		return; // Cannot evaluate without children.

	if (_current_behaviour_node != nullptr) {
		// Respect the thinking delay if we have a current behaviour.
		_thinking_delay_in_seconds_current_timer -= delta;
		if (_thinking_delay_in_seconds_current_timer > 0.0f) {
#ifdef DEBUG_ENABLED
			_total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
			UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
#endif
			return;
		}
		_thinking_delay_in_seconds_current_timer = _thinking_delay_in_seconds;

		// If the current behaviour cannot be interrupted, don't evaluate.
		//UtilityAIBehaviour* behaviour_node = godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node);
		if (!_current_behaviour_node->get_can_be_interrupted()) {
#ifdef DEBUG_ENABLED
			_total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
			UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
#endif
			return;
		}
	}

	// Go through the behaviours and check which one seems
	// best to perform.
	float score = 0.0f;
	int place_in_behaviour_list = 0;
	_num_possible_behaviours = 0;
	int chosen_node_index = 0;
	float highest_score = -1.0f;
	UtilityAIBehaviour *new_behaviour = nullptr;

	for (int b = 0; b < _num_behaviours_to_select; ++b) {
		_top_scoring_behaviours_group_nodes[b] = nullptr;
		_top_scoring_behaviours_nodes[b] = nullptr;
		_top_scoring_behaviours_score[b] = -1.0f;
	}
	//WARN_PRINT("Checking sensors...");
	// Evaluate the sensors.
	for (unsigned int i = 0; i < _num_child_sensors; ++i) {
		UtilityAISensors *sensorNode = _child_sensors[i];
		if (sensorNode->get_is_active()) {
			sensorNode->evaluate_sensor_value();
		}
	} //endfor child sensors.
	//WARN_PRINT("DONE!");
	//WARN_PRINT("Checking Behaviours...");
	for (unsigned i = 0; i < _num_child_behaviours; ++i) {
		UtilityAIBehaviours *behavioursNode = _child_behaviours[i];
		if (!behavioursNode->get_is_active()) {
			continue;
		}

		float score = behavioursNode->evaluate();

		if (behavioursNode->is_behaviour_group()) {
			if (!(score >= behavioursNode->get_activation_score())) {
				continue;
			}
			//std::vector<UtilityAIBehaviours*> bgiBehaviours = behavioursNode->get_child_behaviours();
			unsigned int num_bgi_behaviours = behavioursNode->get_num_child_behaviours();
			for (unsigned int c = 0; c < num_bgi_behaviours; ++c) {
				UtilityAIBehaviours *bgiNode = behavioursNode->get_child_behaviours()[c]; //bgiBehaviours[c];
				if (bgiNode->is_behaviour_group())
					continue;
				float bgiScore = bgiNode->evaluate();
				if (bgiNode == _current_behaviour_node) {
					bgiScore += _current_behaviour_bias;
				}
				if (bgiScore > 0.0f) {
					place_into_top_n_behaviour_list((UtilityAIBehaviourGroup *)behavioursNode, (UtilityAIBehaviour *)bgiNode, bgiScore);
				}

			} //endfor child behaviours

		} else {
			if (behavioursNode == _current_behaviour_node) {
				score += _current_behaviour_bias;
			}
			if (score > 0.0f) {
				place_into_top_n_behaviour_list(nullptr, (UtilityAIBehaviour *)behavioursNode, score);
			}
		} //endif is behaviour group.
	} //endfor child behaviours
	//WARN_PRINT("DONE!");
	// Evaluate the children.
	/**
	for( int i = 0; i < num_children; ++i ) {
		Node* node = get_child(i);
		if( node == nullptr ) continue;

		// If it is a sensor, do an evaluation to update any groups.
		UtilityAISensors* sensorNode = godot::Object::cast_to<UtilityAISensors>(node);
		if( sensorNode != nullptr ) {
			if( sensorNode->get_is_active() ) {
				sensorNode->evaluate_sensor_value();
			}
			continue;
		}

		// If it is a behaviour group, see if it evaluates so that it should be used.
		if( UtilityAIBehaviourGroup* behaviourGroupNode = godot::Object::cast_to<UtilityAIBehaviourGroup>(node) ) {
			if( behaviourGroupNode->evaluate() ) {
				// Go through the group children and find their place in the top_n list.
				for( int bgi = 0; bgi < behaviourGroupNode->get_child_count(); ++bgi ) {
					Node* bgiNode = behaviourGroupNode->get_child(bgi);
					if(bgiNode == nullptr ) continue;
					if( UtilityAIBehaviour* bgiBehaviourNode = godot::Object::cast_to<UtilityAIBehaviour>(bgiNode) ){
						if( !bgiBehaviourNode->get_is_active()) continue;
						score = bgiBehaviourNode->evaluate();
						if( bgiBehaviourNode == _current_behaviour_node ) {
							score += _current_behaviour_bias;
						}
						if( score > 0.0f ) {
							place_into_top_n_behaviour_list( behaviourGroupNode, bgiBehaviourNode, score );
						}
					}//endif is a behaviour node
				}//endfor behaviour group children
			}//endif behaviour group is valid
			continue;
		}//endif behaviour group node

		// If it is a behaviour, evaluate it and place in to the top_n list.
		UtilityAIBehaviour* behaviourNode = godot::Object::cast_to<UtilityAIBehaviour>(node);
		if( behaviourNode == nullptr ) continue;
		if( !behaviourNode->get_is_active()) continue;

		score = behaviourNode->evaluate();
		if( behaviourNode == _current_behaviour_node ) {
			score += _current_behaviour_bias;
		}

		if( score > 0.0f ) {
			place_into_top_n_behaviour_list( nullptr, behaviourNode, score );
		}
	}//endfor children
	*/

	// No behaviours found?
	_top_scoring_behaviour_name = "";
	if (_num_possible_behaviours < 1) {
		if (_current_behaviour_node != nullptr) {
			// (godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
			emit_signal("behaviour_exited", _current_behaviour_node);
			_current_behaviour_node->end_behaviour();
			_current_behaviour_node = nullptr;
		}
		if (_current_behaviour_group_node != nullptr) {
			emit_signal("behaviour_group_exited", _current_behaviour_group_node);
			_current_behaviour_group_node->emit_signal("behaviour_group_exited");
			_current_behaviour_group_node = nullptr;
		}
#ifdef DEBUG_ENABLED
		_total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
		UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
#endif
		return; // No behaviour chosen.
	}

	// Set the top scoring behaviour name.

	if (_top_scoring_behaviours_nodes[0] != nullptr) {
		_top_scoring_behaviour_name = _top_scoring_behaviours_nodes[0]->get_name();
	}

	// Select a random behaviour from the top n behaviours.
	int chosen_behaviour_index = 0;
	if (_num_possible_behaviours > 1) {
		int random_behaviour = _rng->randi_range(0, _num_possible_behaviours - 1);
		chosen_behaviour_index = random_behaviour;
	}

	//new_behaviour = godot::Object::cast_to<UtilityAIBehaviour>(_top_scoring_behaviours_nodes[chosen_behaviour_index]);
	//UtilityAIBehaviourGroup* new_behaviour_group = godot::Object::cast_to<UtilityAIBehaviourGroup>(_top_scoring_behaviours_group_nodes[chosen_behaviour_index]);
	//ERR_FAIL_COND_MSG( new_behaviour == nullptr, "UtilityAIAgent::evaluate_options(): Error, new_behaviour is nullptr.");
	new_behaviour = _top_scoring_behaviours_nodes[chosen_behaviour_index];
	UtilityAIBehaviourGroup *new_behaviour_group = nullptr;
	if (_top_scoring_behaviours_group_nodes[chosen_behaviour_index] != nullptr) {
		new_behaviour_group = _top_scoring_behaviours_group_nodes[chosen_behaviour_index];
	}

	if (new_behaviour == _current_behaviour_node) {
#ifdef DEBUG_ENABLED
		_total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
		UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
#endif
		return; // No change.
	}
	if (_current_action_node != nullptr) {
		//(godot::Object::cast_to<UtilityAIActions>(_current_action_node))->end_action();
		_current_action_node->end_action();
		emit_signal("action_exited", _current_action_node);
		_current_action_node = nullptr;
	}
	if (_current_behaviour_node != nullptr) {
		//(godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
		_current_behaviour_node->end_behaviour();
		emit_signal("behaviour_exited", _current_behaviour_node);
		_current_behaviour_node = nullptr;
	}

	if (_current_behaviour_group_node != new_behaviour_group && _current_behaviour_group_node != nullptr) {
		_current_behaviour_group_node->emit_signal("behaviour_group_exited");
		emit_signal("behaviour_group_exited", _current_behaviour_group_node);
	}

	// Start and signal the chosen behaviour node.
	_current_behaviour_group_node = new_behaviour_group;
	if (new_behaviour_group != nullptr) {
		new_behaviour_group->emit_signal("behaviour_group_entered");
	}
	_current_behaviour_name = new_behaviour->get_name();
	_current_behaviour_node = new_behaviour; //::Object::cast_to<Node>(new_behaviour);
	new_behaviour->start_behaviour();
	_current_action_node = nullptr;
	emit_signal("behaviour_group_changed", _current_behaviour_group_node);
	emit_signal("behaviour_changed", _current_behaviour_node);
	//emit_signal("action_changed", _current_action_node);

	_thinking_delay_in_seconds_current_timer = _thinking_delay_in_seconds;

#ifdef DEBUG_ENABLED
	_total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
	UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
#endif
}

void UtilityAIAgent::place_into_top_n_behaviour_list(UtilityAIBehaviourGroup *behaviour_group, UtilityAIBehaviour *behaviour, float score) {
	// First on the list.
	if (_num_possible_behaviours == 0) {
		_top_scoring_behaviours_group_nodes[0] = behaviour_group;
		_top_scoring_behaviours_nodes[0] = behaviour;
		_top_scoring_behaviours_score[0] = score;
		_num_possible_behaviours = 1;
		return;
	}

	// Somewhere in the list.
	int place_in_behaviour_list = -1;
	for (int b = 0; b < _num_behaviours_to_select; ++b) {
		if (score > _top_scoring_behaviours_score[b]) {
			place_in_behaviour_list = b;
			break;
		}
	}
	if (place_in_behaviour_list < 0)
		return; // Not better than anything else on the list.

	// Last on the list.
	if (place_in_behaviour_list == _num_behaviours_to_select - 1) {
		_top_scoring_behaviours_group_nodes[_num_behaviours_to_select - 1] = behaviour_group;
		_top_scoring_behaviours_nodes[_num_behaviours_to_select - 1] = behaviour;
		_top_scoring_behaviours_score[_num_behaviours_to_select - 1] = score;
		return;
	}

	// In the beginning or in the middle of a list.
	for (int b = _num_behaviours_to_select - 1; b > place_in_behaviour_list; --b) {
		_top_scoring_behaviours_group_nodes[b] = _top_scoring_behaviours_group_nodes[b - 1];
		_top_scoring_behaviours_nodes[b] = _top_scoring_behaviours_nodes[b - 1];
		_top_scoring_behaviours_score[b] = _top_scoring_behaviours_score[b - 1];
	}

	_top_scoring_behaviours_group_nodes[place_in_behaviour_list] = behaviour_group;
	_top_scoring_behaviours_nodes[place_in_behaviour_list] = behaviour;
	_top_scoring_behaviours_score[place_in_behaviour_list] = score;
	if (_num_possible_behaviours < _num_behaviours_to_select) {
		++_num_possible_behaviours;
	}
}

void UtilityAIAgent::update_current_behaviour() {
	uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();

	if (_current_behaviour_node == nullptr) {
		// No behaviour, so make sure the current action node is null as well.
		if (_current_action_node != nullptr) {
			//UtilityAIActions* actions_node = godot::Object::cast_to<UtilityAIActions>(_current_action_node);
			if (_current_action_node != nullptr) {
				_current_action_node->end_action();
			}
			_current_action_node = nullptr;
			emit_signal("action_changed", _current_action_node);
		}
#ifdef DEBUG_ENABLED
		_total_update_behaviour_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
		UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_update_behaviour_usec(_total_update_behaviour_usec);
#endif
		return;
	}
	UtilityAIAction *new_action_node = _current_behaviour_node->update_behaviour();
	//godot::Object::cast_to<Node>((godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->update_behaviour());
	if (_current_action_node != new_action_node) {
		_current_action_node = new_action_node;
		emit_signal("action_changed", _current_action_node);
	}
	if (_current_action_node == nullptr) {
		//(godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
		_current_behaviour_node->end_behaviour();
		_current_behaviour_name = "";
		//emit_signal("behaviour_completed", _current_behaviour_node );
		_current_behaviour_node = nullptr;
		emit_signal("behaviour_changed", _current_behaviour_node);
	}
#ifdef DEBUG_ENABLED
	_total_update_behaviour_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
	UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_update_behaviour_usec(_total_update_behaviour_usec);
#endif
}

void UtilityAIAgent::set_current_action_is_finished(bool is_finished) {
	if (_current_behaviour_node == nullptr)
		return;
	if (_current_action_node == nullptr)
		return;
	_current_action_node->set_is_finished(is_finished);
	//((UtilityAIAction*)_current_action_node)->set_is_finished(is_finished);
}

void UtilityAIAgent::abort_current_behaviour() {
	if (_current_behaviour_node == nullptr)
		return;
	//(godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
	_current_behaviour_node->end_behaviour();
	_current_behaviour_name = "";
	_current_behaviour_node = nullptr;
	_current_action_node = nullptr;
	emit_signal("behaviour_changed", _current_behaviour_node);
	emit_signal("action_changed", _current_action_node);
}

// Getters and Setters.

void UtilityAIAgent::set_current_behaviour_name(godot::String current_behaviour_name) {
	_current_behaviour_name = current_behaviour_name;
}

godot::String UtilityAIAgent::get_current_behaviour_name() const {
	return _current_behaviour_name;
}

void UtilityAIAgent::set_current_behaviour_group_node(UtilityAIBehaviourGroup *new_behaviour_group) {
	_current_behaviour_group_node = new_behaviour_group;
}

UtilityAIBehaviourGroup *UtilityAIAgent::get_current_behaviour_group_node() const {
	return _current_behaviour_group_node;
}

void UtilityAIAgent::set_current_behaviour_node(UtilityAIBehaviour *new_behaviour) {
	_current_behaviour_node = new_behaviour;
}

UtilityAIBehaviour *UtilityAIAgent::get_current_behaviour_node() const {
	return _current_behaviour_node;
}

void UtilityAIAgent::set_current_action_node(UtilityAIAction *new_action_node) {
	_current_action_node = new_action_node;
}

UtilityAIAction *UtilityAIAgent::get_current_action_node() const {
	return _current_action_node;
}

void UtilityAIAgent::set_num_behaviours_to_select(int num_behaviours_to_select) {
	_num_behaviours_to_select = num_behaviours_to_select;
}

int UtilityAIAgent::get_num_behaviours_to_select() const {
	return _num_behaviours_to_select;
}

void UtilityAIAgent::set_thinking_delay_in_seconds(float thinking_delay_in_seconds) {
	_thinking_delay_in_seconds = thinking_delay_in_seconds;
}

float UtilityAIAgent::get_thinking_delay_in_seconds() const {
	return _thinking_delay_in_seconds;
}

void UtilityAIAgent::set_current_behaviour_bias(float current_behaviour_bias) {
	_current_behaviour_bias = current_behaviour_bias;
}

float UtilityAIAgent::get_current_behaviour_bias() const {
	return _current_behaviour_bias;
}

void UtilityAIAgent::set_top_scoring_behaviour_name(godot::String top_scoring_behaviour_name) {
	_top_scoring_behaviour_name = top_scoring_behaviour_name;
}

godot::String UtilityAIAgent::get_top_scoring_behaviour_name() const {
	return _top_scoring_behaviour_name;
}

#ifdef DEBUG_ENABLED

void UtilityAIAgent::set_total_evaluate_options_usec(uint64_t total_evaluate_options_usec) {
	_total_evaluate_options_usec = total_evaluate_options_usec;
}

uint64_t UtilityAIAgent::get_total_evaluate_options_usec() const {
	return _total_evaluate_options_usec;
}

void UtilityAIAgent::set_total_update_behaviour_usec(uint64_t total_update_behaviour_usec) {
	_total_update_behaviour_usec = total_update_behaviour_usec;
}

uint64_t UtilityAIAgent::get_total_update_behaviour_usec() const {
	return _total_update_behaviour_usec;
}

#endif

/**
void UtilityAIAgent::set_random_number_generator( RandomNumberGenerator rng ) {
	_rng = rng;
}

RandomNumberGenerator UtilityAIAgent::get_random_number_generator() const {
	return _rng;
}
*/

// Godot virtuals.

/**
void UtilityAIAgent::_notification( int p_what ) {
	switch( p_what ) {
		case NOTIFICATION_PHYSICS_PROCESS: {
			double dt = get_physics_process_delta_time();
			if( _current_behaviour_group_node ) {
				_current_behaviour_group_node->emit_signal("on_physics_frame_tick", dt);
			}
			if( _current_behaviour_node ) {
				_current_behaviour_node->emit_signal("on_physics_frame_tick", dt);
			}
			if( _current_action_node ) {
				_current_action_node->emit_signal("on_physics_frame_tick", dt);
			}
		} break;
		case NOTIFICATION_PROCESS: {
			double dt = get_process_delta_time();
			if( _current_behaviour_group_node ) {
				_current_behaviour_group_node->emit_signal("on_idle_frame_tick", dt);
			}
			if( _current_behaviour_node ) {
				_current_behaviour_node->emit_signal("on_idle_frame_tick", dt);
			}
			if( _current_action_node ) {
				_current_action_node->emit_signal("on_idle_frame_tick", dt);
			}
		} break;
		default: {} break;
	}//endswitch
}
*/

void UtilityAIAgent::_ready() {
	if (Engine::get_singleton()->is_editor_hint())
		return;
#ifdef DEBUG_ENABLED
	UtilityAIDebuggerOverlay::get_singleton()->register_ai_agent(this->get_instance_id());
#endif
	for (int i = 0; i < get_child_count(); ++i) {
		if (UtilityAIBehaviours *beh = godot::Object::cast_to<UtilityAIBehaviours>(get_child(i))) {
			_child_behaviours.push_back(beh);
		} else if (UtilityAISensors *sensor = godot::Object::cast_to<UtilityAISensors>(get_child(i))) {
			_child_sensors.push_back(sensor);
		}
	}
	_num_child_behaviours = (unsigned int)_child_behaviours.size();
	_num_child_sensors = (unsigned int)_child_sensors.size();
}

void UtilityAIAgent::_process(double delta) {
#ifdef DEBUG_ENABLED
	uint64_t current_timestamp = godot::Time::get_singleton()->get_ticks_usec();
#endif
	if (_current_behaviour_group_node) {
		_current_behaviour_group_node->emit_signal("idle_frame_tick", delta);
#ifdef DEBUG_ENABLED
		_current_behaviour_group_node->set_last_visited_timestamp(current_timestamp);
#endif
	}
	if (_current_behaviour_node) {
		_current_behaviour_node->emit_signal("idle_frame_tick", delta);
#ifdef DEBUG_ENABLED
		_current_behaviour_node->set_last_visited_timestamp(current_timestamp);
#endif
	}
	if (_current_action_node) {
		_current_action_node->emit_signal("idle_frame_tick", delta);
#ifdef DEBUG_ENABLED
		_current_action_node->set_last_visited_timestamp(current_timestamp);
#endif
	}
}

void UtilityAIAgent::_physics_process(double delta) {
#ifdef DEBUG_ENABLED
	uint64_t current_timestamp = godot::Time::get_singleton()->get_ticks_usec();
#endif
	if (_current_behaviour_group_node) {
		_current_behaviour_group_node->emit_signal("physics_frame_tick", delta);
#ifdef DEBUG_ENABLED
		_current_behaviour_group_node->set_last_visited_timestamp(current_timestamp);
#endif
	}
	if (_current_behaviour_node) {
		_current_behaviour_node->emit_signal("physics_frame_tick", delta);
#ifdef DEBUG_ENABLED
		_current_behaviour_node->set_last_visited_timestamp(current_timestamp);
#endif
	}
	if (_current_action_node) {
		_current_action_node->emit_signal("physics_frame_tick", delta);
#ifdef DEBUG_ENABLED
		_current_action_node->set_last_visited_timestamp(current_timestamp);
#endif
	}
}
