#ifndef UtilityAINQSSearchCriterias_H_INCLUDED
#define UtilityAINQSSearchCriterias_H_INCLUDED 
#include "../UtilityAI.h"
//#include "UtilityAINodeQuerySystem.h"
//#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAINQSSearchCriteria : public UtilityAI { //NodeQuerySystem {
    GDCLASS(UtilityAINQSSearchCriteria, UtilityAI ) //NodeQuerySystem )

private:
    bool    _use_for_scoring;
    bool    _use_for_filtering;
    
protected:
    static void _bind_methods();

    //bool   _filtering_result;
    //double _scoring_result;
    double  _score;
    bool    _is_filtered;


public:
    UtilityAINQSSearchCriteria();
    ~UtilityAINQSSearchCriteria();
    
    
    // Getters and setters for attributes.
    
    void set_use_for_scoring( bool use_for_scoring );
    bool get_use_for_scoring() const;

    void set_use_for_filtering( bool use_for_filtering );
    bool get_use_for_filtering() const;

    void set_is_filtered( bool is_filtered );
    bool get_is_filtered() const;

    void set_score( double score );
    double get_score() const;


    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score );

};

}


#endif 
