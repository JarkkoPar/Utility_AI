#ifndef UtilityAIBehaviourTreeNodes_H_INCLUDED
#define UtilityAIBehaviourTreeNodes_H_INCLUDED 

#include "UtilityAI.h"
#include "UtilityAIBehaviourTreeDefinitions.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBehaviourTreeNodes : public UtilityAI {
    GDCLASS(UtilityAIBehaviourTreeNodes, UtilityAI)

private:
    

    
protected:
    static void _bind_methods();

public:
    UtilityAIBehaviourTreeNodes();
    ~UtilityAIBehaviourTreeNodes();
    
    
    // Getters and setters for attributes.
        
    //void  set_has_vetoed( bool has_vetoed );
    //bool  get_has_vetoed() const;

    //void set_score( double score );
    //double get_score() const;

    // Handling functions.

    virtual int tick();
};

}


#endif 
