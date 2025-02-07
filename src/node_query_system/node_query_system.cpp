#include "node_query_system.h"
#include <godot_cpp/classes/performance.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

UtilityAINodeQuerySystem::UtilityAINodeQuerySystem() {
	_current_high_priority_query_index = 0;
	_current_regular_query_index = 0;

	_time_allocation_pct_to_high_priority_queries = 0.8f;

	_run_queries_time_budget_per_frame = 1000;
	_run_queries_time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * ((float)_run_queries_time_budget_per_frame));
	_run_queries_time_budget_per_frame_regular_queries = _run_queries_time_budget_per_frame - _run_queries_time_budget_per_frame_high_priority_queries;

	_post_query_time_budget_per_frame = 500;
	_post_query_time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (double)_post_query_time_budget_per_frame);
	_post_query_time_budget_per_frame_regular_queries = _post_query_time_budget_per_frame - _post_query_time_budget_per_frame_high_priority_queries;

	_post_high_priority_queries_time_elapsed_usec = 0;
	_post_regular_queries_time_elapsed_usec = 0;
	_run_queries_time_elapsed_usec = 0;
	_current_post_high_priority_queries_time_elapsed_usec = 0;
	_current_post_regular_queries_time_elapsed_usec = 0;

	_is_performance_counter_initialized = false;

	_num_active_high_priority_queries = 0;
	_num_active_regular_priority_queries = 0;

	_high_priority_query_per_frame_execute_query_time_budget_usec = 20;
	_regular_query_per_frame_execute_query_time_budget_usec = 10;
}

UtilityAINodeQuerySystem::~UtilityAINodeQuerySystem() {
}

void UtilityAINodeQuerySystem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_run_queries_time_budget_per_frame", "run_queries_time_budget_per_frame_usec"), &UtilityAINodeQuerySystem::set_run_queries_time_budget_per_frame);
	ClassDB::bind_method(D_METHOD("get_run_queries_time_budget_per_frame"), &UtilityAINodeQuerySystem::get_run_queries_time_budget_per_frame);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "run_queries_time_budget_per_frame_usec", PROPERTY_HINT_RANGE, "1,10000,or_greater"), "set_run_queries_time_budget_per_frame", "get_run_queries_time_budget_per_frame");

	//ClassDB::bind_method(D_METHOD("set_post_query_time_budget_per_frame", "post_query_time_budget_per_frame"), &UtilityAINodeQuerySystem::set_post_query_time_budget_per_frame);
	//ClassDB::bind_method(D_METHOD("get_post_query_time_budget_per_frame"), &UtilityAINodeQuerySystem::get_post_query_time_budget_per_frame);
	//ADD_PROPERTY(PropertyInfo(Variant::INT, "post_query_time_budget_per_frame", PROPERTY_HINT_RANGE, "1,10000,or_greater"), "set_post_query_time_budget_per_frame","get_post_query_time_budget_per_frame");

	ClassDB::bind_method(D_METHOD("set_high_priority_query_per_frame_execute_query_time_budget_usec", "high_priority_query_per_frame_execute_query_time_budget_usec"), &UtilityAINodeQuerySystem::set_high_priority_query_per_frame_execute_query_time_budget_usec);
	ClassDB::bind_method(D_METHOD("get_high_priority_query_per_frame_execute_query_time_budget_usec"), &UtilityAINodeQuerySystem::get_high_priority_query_per_frame_execute_query_time_budget_usec);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "high_priority_query_per_frame_execute_query_time_budget_usec", PROPERTY_HINT_RANGE, "1,100,or_greater"), "set_high_priority_query_per_frame_execute_query_time_budget_usec", "get_high_priority_query_per_frame_execute_query_time_budget_usec");

	ClassDB::bind_method(D_METHOD("set_regular_query_per_frame_execute_query_time_budget_usec", "regular_query_per_frame_execute_query_time_budget_usec"), &UtilityAINodeQuerySystem::set_regular_query_per_frame_execute_query_time_budget_usec);
	ClassDB::bind_method(D_METHOD("get_regular_query_per_frame_execute_query_time_budget_usec"), &UtilityAINodeQuerySystem::get_regular_query_per_frame_execute_query_time_budget_usec);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "regular_query_per_frame_execute_query_time_budget_usec", PROPERTY_HINT_RANGE, "1,100,or_greater"), "set_regular_query_per_frame_execute_query_time_budget_usec", "get_regular_query_per_frame_execute_query_time_budget_usec");

	ClassDB::bind_method(D_METHOD("set_time_allocation_pct_to_high_priority_queries", "time_allocation_pct_to_high_priority_queries"), &UtilityAINodeQuerySystem::set_time_allocation_pct_to_high_priority_queries);
	ClassDB::bind_method(D_METHOD("get_time_allocation_pct_to_high_priority_queries"), &UtilityAINodeQuerySystem::get_time_allocation_pct_to_high_priority_queries);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time_allocation_pct_to_high_priority_queries", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_time_allocation_pct_to_high_priority_queries", "get_time_allocation_pct_to_high_priority_queries");

	ClassDB::bind_method(D_METHOD("post_query", "search_space", "is_high_priority"), &UtilityAINodeQuerySystem::post_query);
	ClassDB::bind_method(D_METHOD("stop_query", "search_space"), &UtilityAINodeQuerySystem::stop_query);
	ClassDB::bind_method(D_METHOD("run_queries"), &UtilityAINodeQuerySystem::run_queries);
	ClassDB::bind_method(D_METHOD("clear_queries"), &UtilityAINodeQuerySystem::clear_queries);
	ClassDB::bind_method(D_METHOD("initialize_performance_counters"), &UtilityAINodeQuerySystem::initialize_performance_counters);
	ClassDB::bind_method(D_METHOD("get_run_queries_time_elapsed_usec"), &UtilityAINodeQuerySystem::get_run_queries_time_elapsed_usec);
	ClassDB::bind_method(D_METHOD("get_post_queries_time_elapsed_usec"), &UtilityAINodeQuerySystem::get_post_queries_time_elapsed_usec);
}

// Getters and setters.

void UtilityAINodeQuerySystem::set_run_queries_time_budget_per_frame(uint64_t run_queries_time_budget_per_frame) {
	_run_queries_time_budget_per_frame = run_queries_time_budget_per_frame;
	_run_queries_time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (double)_run_queries_time_budget_per_frame);
}

uint64_t UtilityAINodeQuerySystem::get_run_queries_time_budget_per_frame() const {
	return _run_queries_time_budget_per_frame;
}

void UtilityAINodeQuerySystem::set_post_query_time_budget_per_frame(uint64_t post_query_time_budget_per_frame) {
	_post_query_time_budget_per_frame = post_query_time_budget_per_frame;
	_post_query_time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (double)_post_query_time_budget_per_frame);
	_post_query_time_budget_per_frame_regular_queries = _post_query_time_budget_per_frame - _post_query_time_budget_per_frame_high_priority_queries;
}

uint64_t UtilityAINodeQuerySystem::get_post_query_time_budget_per_frame() const {
	return _post_query_time_budget_per_frame;
}

void UtilityAINodeQuerySystem::set_time_allocation_pct_to_high_priority_queries(float time_allocation_pct_to_high_priority_queries) {
	_time_allocation_pct_to_high_priority_queries = time_allocation_pct_to_high_priority_queries;

	_run_queries_time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (double)_run_queries_time_budget_per_frame);
	_run_queries_time_budget_per_frame_regular_queries = _run_queries_time_budget_per_frame - _run_queries_time_budget_per_frame_high_priority_queries;

	_post_query_time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (double)_post_query_time_budget_per_frame);
	_post_query_time_budget_per_frame_regular_queries = _post_query_time_budget_per_frame - _post_query_time_budget_per_frame_high_priority_queries;
}

float UtilityAINodeQuerySystem::get_time_allocation_pct_to_high_priority_queries() const {
	return _time_allocation_pct_to_high_priority_queries;
}

void UtilityAINodeQuerySystem::set_high_priority_query_per_frame_execute_query_time_budget_usec(int high_priority_query_per_frame_execute_query_time_budget_usec) {
	_high_priority_query_per_frame_execute_query_time_budget_usec = high_priority_query_per_frame_execute_query_time_budget_usec;
}

int UtilityAINodeQuerySystem::get_high_priority_query_per_frame_execute_query_time_budget_usec() const {
	return _high_priority_query_per_frame_execute_query_time_budget_usec;
}

void UtilityAINodeQuerySystem::set_regular_query_per_frame_execute_query_time_budget_usec(int regular_query_per_frame_execute_query_time_budget_usec) {
	_regular_query_per_frame_execute_query_time_budget_usec = regular_query_per_frame_execute_query_time_budget_usec;
}

int UtilityAINodeQuerySystem::get_regular_query_per_frame_execute_query_time_budget_usec() const {
	return _regular_query_per_frame_execute_query_time_budget_usec;
}

int UtilityAINodeQuerySystem::get_run_queries_time_elapsed_usec() const {
	return _run_queries_time_elapsed_usec;
}

int UtilityAINodeQuerySystem::get_post_queries_time_elapsed_usec() const {
	return (_post_high_priority_queries_time_elapsed_usec + _post_regular_queries_time_elapsed_usec);
}

// Handling methods.

void UtilityAINodeQuerySystem::initialize_performance_counters() {
	if (_is_performance_counter_initialized)
		return;
	Performance *perf = godot::Performance::get_singleton();
	if (perf == nullptr)
		return;
	perf->add_custom_monitor("NodeQuerySystem/Run queries time usec", Callable(this, "get_run_queries_time_elapsed_usec"));
	perf->add_custom_monitor("NodeQuerySystem/Post queries time usec", Callable(this, "get_post_queries_time_elapsed_usec"));
	_is_performance_counter_initialized = true;
}

void UtilityAINodeQuerySystem::run_queries() {
	uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();

	// Clear the post queries time measurement.
	_post_high_priority_queries_time_elapsed_usec = _current_post_high_priority_queries_time_elapsed_usec;
	_current_post_high_priority_queries_time_elapsed_usec = 0;

	_post_regular_queries_time_elapsed_usec = _current_post_regular_queries_time_elapsed_usec;
	_current_post_regular_queries_time_elapsed_usec = 0;

	// Then continue with the update.
	uint64_t frame_time_left = _run_queries_time_budget_per_frame;
	if (_high_priority_queries.size() == 0 && _regular_queries.size() == 0 ||
			_num_active_high_priority_queries == 0 && _num_active_regular_priority_queries == 0) {
		_run_queries_time_elapsed_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
		return;
	}

	//std::vector<int> queries_to_delete;
	if (_num_active_high_priority_queries > 0 && _high_priority_queries.size() > 0) {
		while (true) {
			if (_current_high_priority_query_index >= _high_priority_queries.size()) {
				_current_high_priority_query_index = 0;
			}
			//if( !UtilityFunctions::is_instance_valid(_nqs_search_space) )
			UtilityAINQSSearchSpaces *current_query = godot::Object::cast_to<UtilityAINQSSearchSpaces>(_high_priority_queries[_current_high_priority_query_index]);
			if (current_query != nullptr) {
				bool is_completed = current_query->execute_query(_high_priority_query_per_frame_execute_query_time_budget_usec);
				if (is_completed) {
					//queries_to_delete.push_back(_current_high_priority_query_index);
					_high_priority_queries[_current_high_priority_query_index] = nullptr;
					_available_high_priority_query_indexes.push_back(_current_high_priority_query_index);
					--_num_active_high_priority_queries;
					current_query->set_nqs_query_index(-1);
				}
			}

			++_current_high_priority_query_index;
			uint64_t time_used = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
			if (time_used >= _run_queries_time_budget_per_frame_high_priority_queries || _num_active_high_priority_queries == 0) {
				break;
			}
		} //endwhile run queries
	} //endif high priority queries are running
	uint64_t regular_query_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();

	if (_num_active_regular_priority_queries > 0 && _regular_queries.size() > 0) {
		frame_time_left -= (regular_query_start_time_usec - method_start_time_usec);
		if (frame_time_left <= 0) {
			_run_queries_time_elapsed_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
			return; // Too bad, no time left for regular priority queries :(
		}

		while (true) {
			if (_current_regular_query_index >= _regular_queries.size()) {
				_current_regular_query_index = 0;
			}

			UtilityAINQSSearchSpaces *current_query = godot::Object::cast_to<UtilityAINQSSearchSpaces>(_regular_queries[_current_regular_query_index]);
			if (current_query != nullptr) {
				bool is_completed = current_query->execute_query(_regular_query_per_frame_execute_query_time_budget_usec);
				if (is_completed) {
					//queries_to_delete.push_back(_current_regular_query_index);
					_available_regular_query_indexes.push_back(_current_regular_query_index);
					_regular_queries[_current_regular_query_index] = nullptr;
					--_num_active_regular_priority_queries;
					current_query->set_nqs_query_index(-1);
				}
			}

			++_current_regular_query_index;
			uint64_t time_used = godot::Time::get_singleton()->get_ticks_usec() - regular_query_start_time_usec;
			if (time_used >= frame_time_left || _num_active_regular_priority_queries == 0) {
				break;
			}
		} //endwhile run queries
	} //endif regular queries exist

	_run_queries_time_elapsed_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
}

int UtilityAINodeQuerySystem::post_query(UtilityAINQSSearchSpaces *search_space, bool is_high_priority) {
	uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();

	if (is_high_priority) {
		if (search_space == nullptr) { //|| _post_high_priority_queries_time_elapsed_usec >= _post_query_time_budget_per_frame_high_priority_queries ) {
			_current_post_high_priority_queries_time_elapsed_usec += (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
			return -1;
		}
		// Bail out if the search space is already being queried.
		if (search_space->get_nqs_query_index() > -1) { //_high_priority_queries.has( search_space ) ){
			_current_post_high_priority_queries_time_elapsed_usec += (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
			return -1;
		}
		search_space->start_query();
		search_space->set_nqs_query_is_high_priority(true);
		if (_available_high_priority_query_indexes.size() == 0) {
			search_space->set_nqs_query_index(_high_priority_queries.size());
			_high_priority_queries.push_back(search_space);
		} else {
			int free_index = _available_high_priority_query_indexes.back();
			_available_high_priority_query_indexes.pop_back();
			search_space->set_nqs_query_index(free_index);
			_high_priority_queries[free_index] = search_space;
		}
		++_num_active_high_priority_queries;
		_current_post_high_priority_queries_time_elapsed_usec += (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
		return 1;
	}

	if (search_space == nullptr) { //} || _post_regular_queries_time_elapsed_usec >= _post_query_time_budget_per_frame_regular_queries ) {
		_current_post_regular_queries_time_elapsed_usec += (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
		return -1;
	}

	// Regular priority.

	// Bail out if the search space is already being queried.
	if (search_space->get_nqs_query_index() > -1) { ////_regular_queries.has( search_space ) ){
		_current_post_regular_queries_time_elapsed_usec += (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
		return -1;
	}
	search_space->start_query();
	search_space->set_nqs_query_is_high_priority(false);
	if (_available_regular_query_indexes.size() == 0) {
		search_space->set_nqs_query_index(_regular_queries.size());
		_regular_queries.push_back(search_space);
	} else {
		int free_index = _available_regular_query_indexes.back();
		_available_regular_query_indexes.pop_back();
		search_space->set_nqs_query_index(free_index);
		_regular_queries[free_index] = search_space;
	}
	++_num_active_regular_priority_queries;
	_current_post_regular_queries_time_elapsed_usec += (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
	return 1;
}

bool UtilityAINodeQuerySystem::stop_query(UtilityAINQSSearchSpaces *search_space) {
	if (search_space == nullptr) {
		return false; // Not stopped, nullptr.
	}
	if (search_space->get_nqs_query_index() < 0) {
		return false; // Not stopped, invalid index.
	}
	if (search_space->get_nqs_query_is_high_priority()) {
		_high_priority_queries[search_space->get_nqs_query_index()] = nullptr;
		_available_high_priority_query_indexes.push_back(search_space->get_nqs_query_index());
		search_space->set_nqs_query_index(-1);
		return true;
	}

	_regular_queries[search_space->get_nqs_query_index()] = nullptr;
	_available_regular_query_indexes.push_back(search_space->get_nqs_query_index());
	search_space->set_nqs_query_index(-1);
	return true;
}

void UtilityAINodeQuerySystem::clear_queries() {
	_high_priority_queries.clear();
	_regular_queries.clear();
	_available_high_priority_query_indexes.clear();
	_available_regular_query_indexes.clear();
}
