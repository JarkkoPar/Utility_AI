#include "consideration_group_resource.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// Method binds.

void UtilityAIConsiderationGroupResource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_child_nodes", "child_nodes"), &UtilityAIConsiderationGroupResource::set_child_nodes);
	ClassDB::bind_method(D_METHOD("get_child_nodes"), &UtilityAIConsiderationGroupResource::get_child_nodes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "child_nodes", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "UtilityAIConsiderationResources")), "set_child_nodes", "get_child_nodes");

	ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIConsiderationGroupResource::set_evaluation_method);
	ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIConsiderationGroupResource::get_evaluation_method);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method", "get_evaluation_method");

	ClassDB::bind_method(D_METHOD("set_invert_score", "invert_score"), &UtilityAIConsiderationGroupResource::set_invert_score);
	ClassDB::bind_method(D_METHOD("get_invert_score"), &UtilityAIConsiderationGroupResource::get_invert_score);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invert_score", PROPERTY_HINT_NONE), "set_invert_score", "get_invert_score");
}

// Constructor and destructor.

UtilityAIConsiderationGroupResource::UtilityAIConsiderationGroupResource() {
	_evaluation_method = 4; // Default to multiplication.
	_invert_score = false;
	set_local_to_scene(true);
}

UtilityAIConsiderationGroupResource::~UtilityAIConsiderationGroupResource() {
}

// Getters and Setters.

void UtilityAIConsiderationGroupResource::set_evaluation_method(int evaluation_method) {
	_evaluation_method = evaluation_method;
}

int UtilityAIConsiderationGroupResource::get_evaluation_method() const {
	return _evaluation_method;
}

void UtilityAIConsiderationGroupResource::set_invert_score(bool invert_score) {
	_invert_score = invert_score;
}

bool UtilityAIConsiderationGroupResource::get_invert_score() const {
	return _invert_score;
}

void UtilityAIConsiderationGroupResource::set_child_nodes(TypedArray<UtilityAIConsiderationResources> child_nodes) {
	_child_nodes = child_nodes;
}

TypedArray<UtilityAIConsiderationResources> UtilityAIConsiderationGroupResource::get_child_nodes() const {
	return _child_nodes;
}

// Handling functions.

float UtilityAIConsiderationGroupResource::evaluate(bool &has_vetoed, Node *parent_node) {
	float score = 0.0;
	for (int i = 0; i < _child_nodes.size(); ++i) {
		UtilityAIConsiderationResources *consideration = godot::Object::cast_to<UtilityAIConsiderationResources>(_child_nodes[i]);
		if (consideration == nullptr) {
			continue;
		}
		if (!consideration->get_is_active()) {
			continue;
		}
		bool child_has_vetoed = false;
		float child_score = consideration->evaluate(child_has_vetoed, parent_node);
		if (child_has_vetoed) {
			has_vetoed = true;
			return 0.0;
		}

		switch (_evaluation_method) {
			case UtilityAIConsiderationGroupResourceEvaluationMethod::Min: {
				if (i == 0)
					score = child_score;
				if (child_score < score)
					score = child_score;
			} break;
			case UtilityAIConsiderationGroupResourceEvaluationMethod::Max: {
				if (i == 0)
					score = child_score;
				if (child_score > score)
					score = child_score;
			} break;
			case UtilityAIConsiderationGroupResourceEvaluationMethod::Multiply: {
				if (i == 0)
					score = child_score;
				else
					score *= child_score;
				// If after multiplication we are at 0.0, then none of the
				// other considerations will ever change the result, so bail.
				if (score == 0.0) {
					if (_invert_score) {
						return 1.0;
					}
					return 0.0;
				}
			} break;
			case UtilityAIConsiderationGroupResourceEvaluationMethod::FirstNonZero: {
				if (child_score > 0.0) {
					if (_invert_score) {
						score = 1.0 - child_score;
					} else {
						score = child_score;
					}
					return score;
				}
			} break;
			default:
				score += child_score;
		} //end switch evaluation method
	} //endfor children

	if (_evaluation_method == UtilityAIConsiderationGroupResourceEvaluationMethod::Mean) {
		score = score / ((float)_child_nodes.size());
	}

	if (_invert_score) {
		score = 1.0 - score;
	}

	return score;
	/**
	_score = 0.0;
	_has_vetoed = false;

	// Evaluate the children.
	int num_children = get_child_count();
	if( num_children < 1 ) return 0.0;
	float child_score = 0.0;
	for( int i = 0; i < num_children; ++i ) {
		Node* node = get_child(i);
		if( node == nullptr ) continue;
		UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(node);
		if( considerationNode == nullptr ) continue;
		if( !considerationNode->get_is_active() ) continue;
		child_score = considerationNode->evaluate(); //agent, delta);
		if( considerationNode->get_has_vetoed()) {
			_score = 0.0;
			_has_vetoed = true;
			return _score; // Veto zeroes out the score for the entire group.
		}

		switch( _evaluation_method ) {
			case UtilityAIConsiderationGroupResourceEvaluationMethod::Min:
			{
				if( i == 0 ) _score = child_score;
				if( child_score < _score ) _score = child_score;
			}
			break;
			case UtilityAIConsiderationGroupResourceEvaluationMethod::Max:
			{
				if( i == 0 ) _score = child_score;
				if( child_score > _score ) _score = child_score;
			}
			break;
			case UtilityAIConsiderationGroupResourceEvaluationMethod::Multiply:
			{
				if( i == 0 ) _score = child_score;
				else _score *= child_score;
				// If after multiplication we are at 0.0, then none of the
				// other considerations will ever change the result, so bail.
				if( _score == 0.0 ) {
					if( _invert_score ) {
						return 1.0;
					}
					return 0.0;
				}
			}
			break;
			case UtilityAIConsiderationGroupResourceEvaluationMethod::FirstNonZero:
			{
				if( child_score > 0.0 ) {
					if( _invert_score ) {
						_score = 1.0 - child_score;
					} else {
						_score = child_score;
					}
					return _score;
				}
			}
			break;
			default: _score += child_score;
		}//end switch evaluation method

	}//endfor children

	if( _evaluation_method == UtilityAIConsiderationGroupResourceEvaluationMethod::Mean ) {
		_score = _score / ((float)num_children);
	}

	if( _invert_score ) {
		_score = 1.0 - _score;
	}

	return _score;
	*/
}
