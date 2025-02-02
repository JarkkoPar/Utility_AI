#include "register_types.h"
#include <godot_cpp/classes/engine.hpp>

// Classes to include in to the gdextension module.

// Performance monitor singleton.
#include "performance_monitor_singleton.h"

// AI AGENT

// Core nodes
#include "agent_behaviours/behaviours.h"
#include "agent_behaviours/behaviour.h"
#include "agent_behaviours/behaviour_group.h"
#include "agent_behaviours/considerations.h"
#include "agent_behaviours/consideration_group.h"
#include "agent_behaviours/consideration.h"
#include "agent_behaviours/actions.h"
#include "agent_behaviours/action.h"
#include "agent_behaviours/action_group.h"
#include "agent_behaviours/agent.h"
#include "agent_behaviours/sensors.h"
#include "agent_behaviours/sensor.h"
#include "agent_behaviours/sensor_group.h"

// Special sensors
#include "agent_behaviours/sensors/boolean.h"
#include "agent_behaviours/sensors/float_range.h"
#include "agent_behaviours/sensors/int_range.h"
#include "agent_behaviours/sensors/angle_vector2.h"
#include "agent_behaviours/sensors/angle_vector3.h"
#include "agent_behaviours/sensors/distance_vector2.h"
#include "agent_behaviours/sensors/distance_vector3.h"
#include "agent_behaviours/sensors/area2d_visibility.h"
#include "agent_behaviours/sensors/area3d_visibility.h"

// Special considerations
#include "agent_behaviours/considerations/boolean.h"
#include "agent_behaviours/considerations/custom_property.h"

// Resource-based considerations
#include "resources/considerations/consideration_resources.h"
#include "resources/considerations/consideration_resource.h"
#include "resources/considerations/consideration_group_resource.h"


// BEHAVIOUR TREE
#include "behaviour_tree/nodes.h"
#include "behaviour_tree/root.h"

// Composites
#include "behaviour_tree/composite_nodes.h"
#include "behaviour_tree/random_sequence.h"
#include "behaviour_tree/random_selector.h"
#include "behaviour_tree/sequence.h"
#include "behaviour_tree/selector.h"
#include "behaviour_tree/parallel.h"
#include "behaviour_tree/score_based_picker.h"

// Decorators
#include "behaviour_tree/decorator_nodes.h"
#include "behaviour_tree/repeater.h"
#include "behaviour_tree/repeat_until.h"
#include "behaviour_tree/limiter.h"
#include "behaviour_tree/inverter.h"
#include "behaviour_tree/fixed_result.h"
#include "behaviour_tree/pass_through.h"
#include "behaviour_tree/cooldown_ticks.h"
#include "behaviour_tree/cooldown_msec.h"
#include "behaviour_tree/cooldown_usec.h"

// Tasks
#include "behaviour_tree/leaf.h"
#include "behaviour_tree/run_nqs_query.h"
#include "behaviour_tree/node_reference.h"
#include "behaviour_tree/pass_by.h"

// STATE TREE

//#include "state_tree/leaf.h"
#include "state_tree/nodes.h"
#include "state_tree/root.h"
#include "state_tree/node.h"


// NODE QUERY SYSTEM
#include "node_query_system/node_query_system.h"

// Search spaces
#include "node_query_system/search_spaces/nqs.h"
#include "node_query_system/search_spaces/node_group.h"
#include "node_query_system/search_spaces/node_children.h"

#include "node_query_system/search_spaces/area3d.h"
#include "node_query_system/search_spaces/area2d.h"

#include "node_query_system/search_spaces/point_grid/point_grid_3d.h"
#include "node_query_system/search_spaces/point_grid/point_grid_2d.h"

// Search criteria
#include "node_query_system/search_criteria/nqs.h"
#include "node_query_system/search_criteria/custom.h"
#include "node_query_system/search_criteria/metadata.h"

#include "node_query_system/search_criteria/distance_to_node3d.h"
#include "node_query_system/search_criteria/distance_to_node2d.h"

#include "node_query_system/search_criteria/distance_to_vector3.h"
#include "node_query_system/search_criteria/distance_to_vector2.h"

#include "node_query_system/search_criteria/angle_to_vector3_xz.h"
#include "node_query_system/search_criteria/angle_to_vector3.h"
#include "node_query_system/search_criteria/angle_to_vector2.h"

#include "node_query_system/search_criteria/dot_product_vector3.h"
#include "node_query_system/search_criteria/dot_product_vector2.h"

#include "node_query_system/search_criteria/dot_product_to_position_vector3.h"
#include "node_query_system/search_criteria/dot_product_to_position_vector2.h"


// Main header for UtilityAI.
#include "utility_ai.h"


// EDITOR PLUGIN CLASSES.
#ifdef DEBUG_ENABLED

//#include "editor/editor_plugin.h"
//#include "debugger/debugger_plugin.h"

#include "debugger/debugger_overlay.h"

#endif

// Standard headers.
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// Singletons
static UtilityAINodeQuerySystem* gpNodeQuerySystem;
static UtilityAIPerformanceMonitorSingleton* gpAIPerformanceMonitor;
#ifdef DEBUG_ENABLED
    static UtilityAIDebuggerOverlay* gpAIDebuggerOverlay;


#endif


void register_scene_classes() {
    GDREGISTER_VIRTUAL_CLASS(UtilityAI);
    GDREGISTER_VIRTUAL_CLASS(UtilityAIConsiderations);
    GDREGISTER_CLASS(UtilityAIConsiderationGroup);
    GDREGISTER_CLASS(UtilityAIConsideration);
    GDREGISTER_VIRTUAL_CLASS(UtilityAISensors);
    GDREGISTER_CLASS(UtilityAISensorGroup);
    GDREGISTER_CLASS(UtilityAISensor);
    GDREGISTER_VIRTUAL_CLASS(UtilityAIActions);
    GDREGISTER_CLASS(UtilityAIActionGroup);
    GDREGISTER_CLASS(UtilityAIAction);
    GDREGISTER_VIRTUAL_CLASS(UtilityAIBehaviours);
    GDREGISTER_CLASS(UtilityAIBehaviour);
    GDREGISTER_CLASS(UtilityAIBehaviourGroup);
    GDREGISTER_CLASS(UtilityAIAgent);

    // // Special sensors.
    GDREGISTER_CLASS(UtilityAIBooleanSensor);
    GDREGISTER_CLASS(UtilityAIFloatRangeSensor);
    GDREGISTER_CLASS(UtilityAIIntRangeSensor);
    GDREGISTER_CLASS(UtilityAIAngleVector2Sensor);
    GDREGISTER_CLASS(UtilityAIAngleVector3Sensor);
    GDREGISTER_CLASS(UtilityAIDistanceVector2Sensor);
    GDREGISTER_CLASS(UtilityAIDistanceVector3Sensor);
    GDREGISTER_CLASS(UtilityAIArea2DVisibilitySensor);
    GDREGISTER_CLASS(UtilityAIArea3DVisibilitySensor);

    // Special considerations.
    GDREGISTER_CLASS(UtilityAIBooleanConsideration);
    GDREGISTER_CLASS(UtilityAICustomPropertyConsideration);

    // Resource-based considerations.
    GDREGISTER_VIRTUAL_CLASS(UtilityAIConsiderationResources);
    GDREGISTER_CLASS(UtilityAIConsiderationResource);
    GDREGISTER_CLASS(UtilityAIConsiderationGroupResource);

    // Behaviour tree.
    GDREGISTER_VIRTUAL_CLASS(UtilityAIBehaviourTreeNodes);
    GDREGISTER_CLASS(UtilityAIBTRoot);

    GDREGISTER_VIRTUAL_CLASS(UtilityAIBTCompositeNodes);
    GDREGISTER_CLASS(UtilityAIBTSequence);
    GDREGISTER_CLASS(UtilityAIBTSelector);
    GDREGISTER_CLASS(UtilityAIBTParallel);
    GDREGISTER_CLASS(UtilityAIBTRandomSequence);
    GDREGISTER_CLASS(UtilityAIBTRandomSelector);
    GDREGISTER_CLASS(UtilityAIBTScoreBasedPicker);

    GDREGISTER_VIRTUAL_CLASS(UtilityAIBTDecoratorNodes);
    GDREGISTER_CLASS(UtilityAIBTRepeater);
    GDREGISTER_CLASS(UtilityAIBTRepeatUntil);
    GDREGISTER_CLASS(UtilityAIBTLimiter);
    GDREGISTER_CLASS(UtilityAIBTFixedResult);
    GDREGISTER_CLASS(UtilityAIBTInverter);
    GDREGISTER_CLASS(UtilityAIBTPassThrough);
    GDREGISTER_CLASS(UtilityAIBTCooldownTicks);
    GDREGISTER_CLASS(UtilityAIBTCooldownMsec);
    GDREGISTER_CLASS(UtilityAIBTCooldownUsec);

    GDREGISTER_VIRTUAL_CLASS(UtilityAIBTTaskNodes);
    GDREGISTER_CLASS(UtilityAIBTLeaf);
    GDREGISTER_CLASS(UtilityAIBTRunNQSQuery);
    GDREGISTER_CLASS(UtilityAIBTPassBy);
    GDREGISTER_CLASS(UtilityAIBTNodeReference);

    // State tree.
    GDREGISTER_VIRTUAL_CLASS(UtilityAIStateTreeNodes);
    GDREGISTER_CLASS(UtilityAISTRoot);
    GDREGISTER_CLASS(UtilityAISTNode);

    // Node Query System.
    GDREGISTER_CLASS(UtilityAINodeQuerySystem);

    GDREGISTER_VIRTUAL_CLASS(UtilityAINQSSearchSpaces);
    GDREGISTER_CLASS(UtilityAINodeGroupSearchSpace);
    GDREGISTER_CLASS(UtilityAINodeChildrenSearchSpace);

    GDREGISTER_CLASS(UtilityAIArea3DSearchSpace);
    GDREGISTER_CLASS(UtilityAIArea2DSearchSpace);

    GDREGISTER_CLASS(UtilityAIPointGrid3DSearchSpace);
    GDREGISTER_CLASS(UtilityAIPointGrid2DSearchSpace);

    GDREGISTER_VIRTUAL_CLASS(UtilityAINQSSearchCriteria);
    GDREGISTER_CLASS(UtilityAICustomSearchCriterion);
    GDREGISTER_CLASS(UtilityAIMetadataSearchCriterion);
    GDREGISTER_CLASS(UtilityAIDistanceToVector3SearchCriterion);
    GDREGISTER_CLASS(UtilityAIDistanceToVector2SearchCriterion);

    GDREGISTER_CLASS(UtilityAIDistanceToNode3DSearchCriterion);
    GDREGISTER_CLASS(UtilityAIDistanceToNode2DSearchCriterion);

    GDREGISTER_CLASS(UtilityAIAngleToVector3XZSearchCriterion);
    GDREGISTER_CLASS(UtilityAIAngleToVector3SearchCriterion);
    GDREGISTER_CLASS(UtilityAIAngleToVector2SearchCriterion);

    GDREGISTER_CLASS(UtilityAIDotProductVector3SearchCriterion);
    GDREGISTER_CLASS(UtilityAIDotProductVector2SearchCriterion);

    GDREGISTER_CLASS(UtilityAIDotProductToPositionVector3SearchCriterion);
    GDREGISTER_CLASS(UtilityAIDotProductToPositionVector2SearchCriterion);


    // Add singletons.
    gpNodeQuerySystem = memnew(UtilityAINodeQuerySystem);
    Engine::get_singleton()->register_singleton("NodeQuerySystem", gpNodeQuerySystem);

    GDREGISTER_CLASS(UtilityAIPerformanceMonitorSingleton);
    gpAIPerformanceMonitor = memnew(UtilityAIPerformanceMonitorSingleton);
    Engine::get_singleton()->register_singleton("AIPerformanceMonitor", gpAIPerformanceMonitor);


#ifdef DEBUG_ENABLED

    GDREGISTER_CLASS(UtilityAIDebuggerOverlay);
    gpAIDebuggerOverlay = memnew(UtilityAIDebuggerOverlay);
    Engine::get_singleton()->register_singleton("AIDebuggerOverlay", gpAIDebuggerOverlay);
#endif


}


void register_editor_classes() {
#ifdef DEBUG_ENABLED
    //GDREGISTER_CLASS(UtilityAIEditorPlugin);
    //ClassDB::register_class<UtilityAIEditorPlugin>();
    //EditorPlugins::add_by_type<UtilityAIEditorPlugin>();

    //ClassDB::register_class<UtilityAIDebuggerPlugin>();
    //EditorPlugins::add_by_type<UtilityAIDebuggerPlugin>();
#endif
}


void initialize_utility_ai_module(ModuleInitializationLevel p_level) {
    //if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    //    return;
    //}

    // Add the classes here.
    switch( p_level ) {
        case MODULE_INITIALIZATION_LEVEL_SCENE: {
            register_scene_classes();
        }
        break;
        case MODULE_INITIALIZATION_LEVEL_EDITOR: {
            //register_editor_classes();
        }
        break;

        default: {} break;
    }//endswitch p_level

}

void uninitialize_utility_ai_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    Engine::get_singleton()->unregister_singleton("NodeQuerySystem");
    memdelete(gpNodeQuerySystem);

    Engine::get_singleton()->unregister_singleton("AIPerformanceMonitor");
    memdelete(gpAIPerformanceMonitor);

#ifdef DEBUG_ENABLED
    Engine::get_singleton()->unregister_singleton("AIDebuggerOverlay");
    memdelete(gpAIDebuggerOverlay);
#endif
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT utility_ai_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_utility_ai_module);
    init_obj.register_terminator(uninitialize_utility_ai_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
