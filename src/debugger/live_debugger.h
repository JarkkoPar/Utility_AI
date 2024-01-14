#ifndef UTILITYAI_LIVE_DEBUGGER_H_INCLUDED
#define UTILITYAI_LIVE_DEBUGGER_H_INCLUDED

#include <godot_cpp/classes/node.hpp>


namespace godot {

class UtilityAILiveDebugger : public Node {
    GDCLASS(UtilityAILiveDebugger, Node)

private:
    
    
protected:
    static void _bind_methods();


public:
    UtilityAILiveDebugger();
    ~UtilityAILiveDebugger();
    
    // Godot virtuals.

    void _notification( int p_what );


    // Handling methods.


    
};

}

#endif
