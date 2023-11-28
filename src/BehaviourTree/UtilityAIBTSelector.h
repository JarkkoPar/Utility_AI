#ifndef UtilityAIBTSelector_H_INCLUDED
#define UtilityAIBTSelector_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTSelector : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTSelector, UtilityAIBehaviourTreeNodes)

private:
    

    
protected:
    static void _bind_methods();

public:
    UtilityAIBTSelector();
    ~UtilityAIBTSelector();
    
    
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
