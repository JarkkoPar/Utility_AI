#ifndef UtilityAIConsiderations_H_INCLUDED
#define UtilityAIConsiderations_H_INCLUDED 

#include "../utility_ai.h"
#include "agent.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIConsiderations : public UtilityAI {
    GDCLASS(UtilityAIConsiderations, UtilityAI)

private:
    

    
protected:
    static void _bind_methods();

    double _score;
    bool _has_vetoed;

public:
    UtilityAIConsiderations();
    ~UtilityAIConsiderations();
    
    
    // Getters and setters for attributes.
        
    void  set_has_vetoed( bool has_vetoed );
    bool  get_has_vetoed() const;

    void set_score( double score );
    double get_score() const;

    // Handling functions.

    virtual double evaluate();
};

}


#endif 
