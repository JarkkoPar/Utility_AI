#ifndef UtilityAISearchCriterias_H_INCLUDED
#define UtilityAISearchCriterias_H_INCLUDED 
#include "UtilityAINodeQuerySystem.h"
//#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAISearchCriteria : public UtilityAINodeQuerySystem {
    GDCLASS(UtilityAISearchCriteria, UtilityAINodeQuerySystem )

private:
    bool    _is_filtered;
    bool    _is_scored;

    
protected:
    static void _bind_methods();

    bool   _filtering_result;
    double _scoring_result;

public:
    UtilityAISearchCriteria();
    ~UtilityAISearchCriteria();
    
    
    // Getters and setters for attributes.
    
    void set_is_filtered( bool is_filtered );
    bool get_is_filtered() const;

    void set_is_scored( bool is_filtered );
    bool get_is_scored() const;

    void set_filtering_result( bool filtering_result );
    bool get_filtering_result() const;

    void set_scoring_result( double scoring_result );
    double get_scoring_result() const;


    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score );

};

}


#endif 
