#ifndef UtilityAIBTRunNQSQuery_H_INCLUDED
#define UtilityAIBTRunNQSQuery_H_INCLUDED 

#include "task_nodes.h"
#include <godot_cpp/classes/node.hpp>
#include "../node_query_system/search_spaces/nqs.h"
#include "../node_query_system/node_query_system.h"

#define QS_IDLE         0
#define QS_RUNNING      1
#define QS_COMPLETED    2

namespace godot {

class UtilityAIBTRunNQSQuery : public UtilityAIBTTaskNodes {
    GDCLASS(UtilityAIBTRunNQSQuery, UtilityAIBTTaskNodes)

private:
    UtilityAINQSSearchSpaces* _nqs_search_space;
    UtilityAINodeQuerySystem* _nqs;

    int  _time_budget_usec;
    int  _top_n_to_find;
    bool _is_high_priority;

    int _query_state;
protected:
    static void _bind_methods();

public:
    UtilityAIBTRunNQSQuery();
    ~UtilityAIBTRunNQSQuery();
    
    
    // Getters and setters for attributes.
        
    void set_nqs_search_space( UtilityAINQSSearchSpaces* nqs_search_space );
    UtilityAINQSSearchSpaces* get_nqs_search_space() const;

    void set_time_budget_usec( int time_budget_usec );
    int  get_time_budget_usec() const;

    void set_top_n_to_find( int top_n_to_find );
    int  get_top_n_to_find() const;

    void set_is_high_priority( bool is_high_priority );
    bool get_is_high_priority() const;

    // Handling functions.
    virtual void reset_bt_node() override;
    virtual int tick(Variant user_data, float delta) override;

    // Godot virtuals.

    void _ready();
    void _physics_process(float delta );
    //void _exit_tree();
};

}


#endif 
