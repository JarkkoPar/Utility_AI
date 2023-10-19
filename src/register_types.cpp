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
#include "SpecialSensors/UtilityAIDistanceVector2Sensor.h"
#include "SpecialSensors/UtilityAIDistanceVector3Sensor.h"

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
    ClassDB::register_class<UtilityAIDistanceVector2Sensor>();
    ClassDB::register_class<UtilityAIDistanceVector3Sensor>();
    
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
