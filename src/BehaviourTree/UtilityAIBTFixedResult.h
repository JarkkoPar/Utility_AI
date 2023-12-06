#ifndef UtilityAIBTFixedResult_H_INCLUDED
#define UtilityAIBTFixedResult_H_INCLUDED 

#include "UtilityAIBTDecoratorNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTFixedResult : public UtilityAIBTDecoratorNodes {
    GDCLASS(UtilityAIBTFixedResult, UtilityAIBTDecoratorNodes)

private:
    
    int _fixed_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTFixedResult();
    ~UtilityAIBTFixedResult();
    
    
    // Getters and setters for attributes.

    void set_fixed_result( int fixed_result );
    int  get_fixed_result() const;
   
    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
