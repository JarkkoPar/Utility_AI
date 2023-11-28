#ifndef UtilityAIBTSequence_H_INCLUDED
#define UtilityAIBTSequence_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTSequence : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTSequence, UtilityAIBehaviourTreeNodes )

private:
    
    int _current_child_index;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTSequence();
    ~UtilityAIBTSequence();
    
    
    // Getters and setters for attributes.
        
    //void  set_has_vetoed( bool has_vetoed );
    //bool  get_has_vetoed() const;

    //void set_score( double score );
    //double get_score() const;

    // Handling functions.

    virtual int tick() override;
};

}


#endif 
