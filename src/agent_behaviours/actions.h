#ifndef UtilityAIActions_H_INCLUDED
#define UtilityAIActions_H_INCLUDED

#include "../utility_ai.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIActions : public UtilityAI {
	GDCLASS(UtilityAIActions, UtilityAI)

private:
	bool _is_finished;
	bool _has_failed;
	//bool _has_previous_step_failed;

protected:
	static void _bind_methods();
#ifdef DEBUG_ENABLED
	uint64_t _last_evaluated_timestamp;
	uint64_t _last_visited_timestamp;
#endif
public:
	UtilityAIActions();
	~UtilityAIActions();

// Getters and setters for attributes.
#ifdef DEBUG_ENABLED
	inline uint64_t get_last_visited_timestamp() const { return _last_visited_timestamp; };
	inline uint64_t get_last_evaluated_timestamp() const { return _last_evaluated_timestamp; };
	inline void set_last_visited_timestamp(uint64_t new_timestamp) { _last_visited_timestamp = new_timestamp; };
	inline void set_last_evaluated_timestamp(uint64_t new_timestamp) { _last_evaluated_timestamp = new_timestamp; };
#endif

	void set_is_finished(bool is_finished);
	bool get_is_finished() const;

	void set_has_failed(bool has_failed);
	bool get_has_failed() const;

	//void set_has_previous_step_failed( bool has_previous_step_failed );
	//bool get_has_previous_step_failed() const;

	// Handling functions.
	virtual Node *step_actions();

	virtual bool start_action();
	virtual bool end_action();
};

} //namespace godot

#endif
