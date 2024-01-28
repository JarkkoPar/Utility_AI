#ifndef UtilityAIConsiderations_H_INCLUDED
#define UtilityAIConsiderations_H_INCLUDED 

#include "../utility_ai.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIConsiderations : public UtilityAI {
    GDCLASS(UtilityAIConsiderations, UtilityAI)

private:
    

    
protected:
    static void _bind_methods();

    float _score;
    bool _has_vetoed;
    #ifdef DEBUG_ENABLED
    uint64_t     _last_evaluated_timestamp;
    uint64_t     _last_visited_timestamp;
    #endif
public:
    UtilityAIConsiderations();
    ~UtilityAIConsiderations();
    
    
    // Getters and setters for attributes.

    #ifdef DEBUG_ENABLED
    inline uint64_t get_last_visited_timestamp() const {return _last_visited_timestamp;};
    inline uint64_t get_last_evaluated_timestamp() const {return _last_evaluated_timestamp;};
    #endif
        
    void  set_has_vetoed( bool has_vetoed );
    bool  get_has_vetoed() const;

    void set_score( float score );
    float get_score() const;

    // Handling functions.

    virtual float evaluate();
};

}


#endif 
