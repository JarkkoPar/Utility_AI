#include "register_types.h"

// Classes to include in to the gdextension module.
#include "UtilityAIBehaviour.h"
#include "UtilityAIBehaviourGroup.h"
#include "UtilityAIConsiderations.h"
#include "UtilityAIConsiderationGroup.h"
#include "UtilityAIConsideration.h"
#include "UtilityAIActions.h"
#include "UtilityAIAction.h"
#include "UtilityAIActionGroup.h"
#include "UtilityAIAgent.h"
#include "UtilityAISensors.h"
#include "UtilityAISensor.h"
#include "UtilityAISensorGroup.h"

// Special sensors.
#include "SpecialSensors/UtilityAIBooleanSensor.h"
#include "SpecialSensors/UtilityAIFloatRangeSensor.h"
#include "SpecialSensors/UtilityAIIntRangeSensor.h"
#include "SpecialSensors/UtilityAIAngleVector2Sensor.h"
#include "SpecialSensors/UtilityAIAngleVector3Sensor.h"
#include "SpecialSensors/UtilityAIDistanceVector2Sensor.h"
#include "SpecialSensors/UtilityAIDistanceVector3Sensor.h"
#include "SpecialSensors/UtilityAIArea2DVisibilitySensor.h"
#include "SpecialSensors/UtilityAIArea3DVisibilitySensor.h"

// Special considerations.
#include "SpecialConsiderations/UtilityAIBooleanConsideration.h"

// Node Query System.

#include "NodeQuerySystem/SearchSpaces/UtilityAINQSSearchSpaces.h"
#include "NodeQuerySystem/SearchSpaces/UtilityAINodeGroupSearchSpace.h"
#include "NodeQuerySystem/SearchSpaces/UtilityAINodeChildrenSearchSpace.h"

#include "NodeQuerySystem/SearchSpaces/UtilityAIArea3DSearchSpace.h"
#include "NodeQuerySystem/SearchSpaces/UtilityAIArea2DSearchSpace.h"


#include "NodeQuerySystem/SearchCriteria/UtilityAINQSSearchCriteria.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAICustomSearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIMetadataSearchCriterion.h"

#include "NodeQuerySystem/SearchCriteria/UtilityAIDistanceToNode3DSearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIDistanceToNode2DSearchCriterion.h"

#include "NodeQuerySystem/SearchCriteria/UtilityAIDistanceToVector3SearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIDistanceToVector2SearchCriterion.h"

#include "NodeQuerySystem/SearchCriteria/UtilityAIAngleToVector3XZSearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIAngleToVector3SearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIAngleToVector2SearchCriterion.h"

#include "NodeQuerySystem/SearchCriteria/UtilityAIDotProductVector3SearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIDotProductVector2SearchCriterion.h"

#include "NodeQuerySystem/SearchCriteria/UtilityAIDotProductToPositionVector3SearchCriterion.h"
#include "NodeQuerySystem/SearchCriteria/UtilityAIDotProductToPositionVector2SearchCriterion.h"

#include "NodeQuerySystem/SearchSpaces/PointGridSearchSpaces/UtilityAINavigation3DPointGridSearchSpaces.h"
#include "NodeQuerySystem/SearchSpaces/PointGridSearchSpaces/UtilityAINavigation3DRectangularPointGridSearchSpace.h"

// Main header for UtilityAI.
#include "UtilityAI.h"

// Standard headers.
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_utility_ai_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Add the classes here.
    ClassDB::register_class<UtilityAI>(true);
    ClassDB::register_class<UtilityAIConsiderations>(true);
    ClassDB::register_class<UtilityAIConsiderationGroup>();
    ClassDB::register_class<UtilityAIConsideration>();
    ClassDB::register_class<UtilityAISensors>(true);
    ClassDB::register_class<UtilityAISensorGroup>();
    ClassDB::register_class<UtilityAISensor>();
    ClassDB::register_class<UtilityAIActions>(true);
    ClassDB::register_class<UtilityAIActionGroup>();
    ClassDB::register_class<UtilityAIAction>();
    ClassDB::register_class<UtilityAIBehaviour>();
    ClassDB::register_class<UtilityAIBehaviourGroup>();
    ClassDB::register_class<UtilityAIAgent>();
    
    // Special sensors.
    ClassDB::register_class<UtilityAIBooleanSensor>();
    ClassDB::register_class<UtilityAIFloatRangeSensor>();
    ClassDB::register_class<UtilityAIIntRangeSensor>();
    ClassDB::register_class<UtilityAIAngleVector2Sensor>();
    ClassDB::register_class<UtilityAIAngleVector3Sensor>();
    ClassDB::register_class<UtilityAIDistanceVector2Sensor>();
    ClassDB::register_class<UtilityAIDistanceVector3Sensor>();
    ClassDB::register_class<UtilityAIArea2DVisibilitySensor>();
    ClassDB::register_class<UtilityAIArea3DVisibilitySensor>();    

    // Special considerations.
    ClassDB::register_class<UtilityAIBooleanConsideration>();

    // Node Query System.
    ClassDB::register_class<UtilityAINQSSearchSpaces>(true);
    ClassDB::register_class<UtilityAINodeGroupSearchSpace>();
    ClassDB::register_class<UtilityAINodeChildrenSearchSpace>();

    ClassDB::register_class<UtilityAIArea3DSearchSpace>();
    ClassDB::register_class<UtilityAIArea2DSearchSpace>();

    //ClassDB::register_class<UtilityAINavigation3DPointGridSearchSpaces>(true);
    //ClassDB::register_class<UtilityAINavigation3DRectangularPointGridSearchSpace>();

    ClassDB::register_class<UtilityAINQSSearchCriteria>(true);
    ClassDB::register_class<UtilityAICustomSearchCriterion>();
    ClassDB::register_class<UtilityAIMetadataSearchCriterion>();
    ClassDB::register_class<UtilityAIDistanceToVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIDistanceToVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIDistanceToNode3DSearchCriterion>();
    ClassDB::register_class<UtilityAIDistanceToNode2DSearchCriterion>();

    ClassDB::register_class<UtilityAIAngleToVector3XZSearchCriterion>();
    ClassDB::register_class<UtilityAIAngleToVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIAngleToVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIDotProductVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIDotProductVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIDotProductToPositionVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIDotProductToPositionVector2SearchCriterion>();

}

void uninitialize_utility_ai_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
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
