#ifndef UtilityAIGroupSearchSpace_H_INCLUDED
#define UtilityAIGroupSearchSpace_H_INCLUDED 

#include "UtilityAINQSSearchSpaces.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIGroupSearchSpace : public UtilityAINQSSearchSpaces {
    GDCLASS(UtilityAIGroupSearchSpace, UtilityAINQSSearchSpaces)

private:
    StringName _group_name;
protected:
    static void _bind_methods();

    
public:
    UtilityAIGroupSearchSpace();
    ~UtilityAIGroupSearchSpace();
    
    
    // Getters and setters for attributes.
    void set_group_name( StringName group_name );
    StringName get_group_name() const;

    virtual TypedArray<Node> get_searchspace_nodes() const override;

};

}


#endif 
