#ifndef UtilityAIGroupSearchSpace_H_INCLUDED
#define UtilityAIGroupSearchSpace_H_INCLUDED 

#include "UtilityAINQSSearchSpaces.h"


namespace godot {

class UtilityAIGroupSearchSpace : public UtilityAINQSSearchSpaces {
    GDCLASS(UtilityAIGroupSearchSpace, UtilityAINQSSearchSpaces)

private:
    StringName _searchspace_node_group;
protected:
    static void _bind_methods();

public:
    UtilityAIGroupSearchSpace();
    ~UtilityAIGroupSearchSpace();
    
    
    // Getters and setters for attributes.
    void set_searchspace_node_group( StringName searchspace_node_group );
    StringName get_searchspace_node_group() const;

    virtual TypedArray<Node> get_searchspace_nodes() const;
    
    // Handling methods.

    //void execute_query();

    // Godot virtuals.
    //void _ready();
};

}


#endif 
