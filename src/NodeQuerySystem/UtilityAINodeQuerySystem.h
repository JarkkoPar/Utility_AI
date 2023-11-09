#ifndef UtilityAINodeQuerySystem_H_INCLUDED
#define UtilityAINodeQuerySystem_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAINodeQuerySystem : public UtilityAI {
    GDCLASS(UtilityAINodeQuerySystem, UtilityAI)

private:
    TypedArray<Node> _query_results;
    Node*            _search_definition_node;
    int              _top_n_to_find;

protected:
    static void _bind_methods();

public:
    UtilityAINodeQuerySystem();
    ~UtilityAINodeQuerySystem();
    
    
    // Getters and setters for attributes.
    void set_query_results(TypedArray<Node> query_results);
    TypedArray<Node> get_query_results() const;
    
    void set_top_n_to_find( int top_n_to_find );
    int  get_top_n_to_find() const;

    // Handling methods.

    void execute_query();

    // Godot virtuals.
    void _ready();
    
    
};

}


#endif 
