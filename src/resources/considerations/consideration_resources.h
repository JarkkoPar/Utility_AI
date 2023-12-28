#ifndef UTILITY_AI_CONSIDERATION_RESOURCES_H_INCLUDED
#define UTILITY_AI_CONSIDERATION_RESOURCES_H_INCLUDED

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/curve.hpp>
#include "../../agent_behaviours/sensors.h"

namespace godot {

class UtilityAIConsiderationResources : public Resource {
    GDCLASS(UtilityAIConsiderationResources, Resource )

private:
    bool _is_active;
    //bool _has_vetoed;
protected:
    static void _bind_methods();

public:
    UtilityAIConsiderationResources();
    ~UtilityAIConsiderationResources();
    
    
    // Getters and setters for attributes.
    /**/
    void  set_is_active( bool is_active );
    bool  get_is_active() const;

    //void  set_has_vetoed( bool has_vetoed );
    //bool  get_has_vetoed() const;

    // Handling functions.
    
    virtual float evaluate(bool& has_vetoed, Node* parent_node );
  
};

}


#endif 
