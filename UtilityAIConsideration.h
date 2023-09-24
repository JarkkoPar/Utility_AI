#ifndef UtilityAIConsideration_H_INCLUDED
#define UtilityAIConsideration_H_INCLUDED 

#include "UtilityAIConsiderationBase.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIConsideration : public UtilityAIConsiderationBase {
    GDCLASS(UtilityAIConsideration, UtilityAIConsiderationBase )

private:

    
protected:
    static void _bind_methods();

public:
    UtilityAIConsideration();
    ~UtilityAIConsideration();
    
    
    // Getters and setters for attributes.
    /**
    
    void set_update_method( int update_method );
    int  get_update_method() const;
        
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */

    // Handling functions.

    virtual float evaluate() override;
};

}


#endif 
