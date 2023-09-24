#include "register_types.h"

// Classes to include in to the gdextension module.
#include "AIBehaviour.h"
#include "AIConsiderationBase.h"
#include "AIConsiderationGroup.h"
#include "AIConsideration.h"
#include "AIAction.h"
//#include "utility_aiStateAction.h"

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
    ClassDB::register_class<AIConsiderationBase>();
    ClassDB::register_class<AIConsiderationGroup>();
    ClassDB::register_class<AIConsideration>();
    ClassDB::register_class<AIAction>();
    ClassDB::register_class<AIBehaviour>();
    
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
