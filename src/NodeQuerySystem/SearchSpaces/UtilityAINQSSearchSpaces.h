#ifndef UtilityAINQSSearchSpaces_H_INCLUDED
#define UtilityAINQSSearchSpaces_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAINQSSearchSpaces : public UtilityAI {
    GDCLASS(UtilityAINQSSearchSpaces, UtilityAI)

private:

protected:
    //static void _bind_methods();

public:
    UtilityAINQSSearchSpaces();
    ~UtilityAINQSSearchSpaces();
    
    
    // Getters and setters for attributes.
    virtual TypedArray<Node> get_searchspace_nodes() const;
    
    // Handling methods.

    //void execute_query();

    // Godot virtuals.
    //void _ready();
};

}


#endif 
