#ifndef UtilityAIBTRunNQSQuery_H_INCLUDED
#define UtilityAIBTRunNQSQuery_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>
#include "../NodeQuerySystem/SearchSpaces/UtilityAINQSSearchSpaces.h"


namespace godot {

class UtilityAIBTRunNQSQuery : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTRunNQSQuery, UtilityAIBehaviourTreeNodes)

private:
    NodePath _nqs_search_space_node_path;
    UtilityAINQSSearchSpaces* _nqs_search_space_node;
    int _time_budget_usec;
protected:
    static void _bind_methods();

public:
    UtilityAIBTRunNQSQuery();
    ~UtilityAIBTRunNQSQuery();
    
    
    // Getters and setters for attributes.
        
    void set_nqs_search_space_node_path( NodePath nqs_search_space_node_path );
    NodePath get_nqs_search_space_node_path() const;

    void set_time_budget_usec( int time_budget_usec );
    int  get_time_budget_usec() const;


    // Handling functions.

    virtual int tick() override;

    // Godot virtuals.

    void _ready();
    //void _exit_tree();
};

}


#endif 
