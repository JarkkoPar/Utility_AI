#ifndef UtilityAIBTAgent_H_INCLUDED
#define UtilityAIBTAgent_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTAgent : public UtilityAI {
    GDCLASS(UtilityAIBTAgent, UtilityAI)

private:
    

    
protected:
    static void _bind_methods();

public:
    UtilityAIBTAgent();
    ~UtilityAIBTAgent();
    
    
    // Getters and setters for attributes.
        
    //void  set_has_vetoed( bool has_vetoed );
    //bool  get_has_vetoed() const;

    //void set_score( double score );
    //double get_score() const;

    // Handling functions.

    int tick();
};

}


#endif 
