#ifndef UtilityAIActions_H_INCLUDED
#define UtilityAIActions_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIActions : public UtilityAI {
    GDCLASS(UtilityAIActions, UtilityAI)

private:
    
    bool _is_finished;
    
protected:
    static void _bind_methods();

public:
    UtilityAIActions();
    ~UtilityAIActions();
    
    
    // Getters and setters for attributes.
    
    void set_is_finished( bool is_finished );
    bool get_is_finished() const;

    
    // Handling functions.
    virtual Node* step_actions();

    virtual bool start_action();
    virtual bool end_action();
};

}


#endif 