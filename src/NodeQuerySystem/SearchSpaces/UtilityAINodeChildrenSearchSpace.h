#ifndef UtilityAINodeChildrenSearchSpace_H_INCLUDED
#define UtilityAINodeChildrenSearchSpace_H_INCLUDED 

#include "UtilityAINQSSearchSpaces.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAINodeChildrenSearchSpace : public UtilityAINQSSearchSpaces {
    GDCLASS(UtilityAINodeChildrenSearchSpace, UtilityAINQSSearchSpaces)

private:
    Node*   _parent_node;
protected:
    static void _bind_methods();

    virtual void _initialize_search_space() override;
    virtual void _uninitialize_search_space() override;
public:
    UtilityAINodeChildrenSearchSpace();
    ~UtilityAINodeChildrenSearchSpace();
    
    
    // Getters and setters for attributes.
    void set_parent_node( Node* parent );
    Node* get_parent_node() const;

    virtual TypedArray<Node> get_searchspace_nodes() const override;

    // Godot virtuals.
    //void _ready();
};

}


#endif 
