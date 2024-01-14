#include "debugger_plugin.h"
#include <godot_cpp/classes/label.hpp>
#include "../utility_ai.h"
#include "../behaviour_tree/root.h"
#include "../state_tree/root.h"
#include "../agent_behaviours/agent.h"


using namespace godot;

UtilityAIDebuggerPlugin::UtilityAIDebuggerPlugin() {

}

UtilityAIDebuggerPlugin::~UtilityAIDebuggerPlugin() {
    
}


void UtilityAIDebuggerPlugin::_bind_methods() {

}


void UtilityAIDebuggerPlugin::_setup_session(int32_t session_id) {
    Label* debugger_label = memnew(Label);
    ERR_FAIL_COND_MSG(debugger_label == nullptr, "UtilityAIDebuggerPlugin::_setup_session(): Failed to create the debugger label - Out of memory?");
    debugger_label->set_name("UtilityAI Debugger");
    debugger_label->set_name("UtilityAI Debugger");
    //Ref<EditorDebuggerSession> uai_session = get_session(session_id);
    _debugger_session = get_session(session_id);
    if( !_debugger_session.is_valid() ) {//uai_session.is_null() || !uai_session.is_valid() ) {
        memdelete( debugger_label );
        ERR_FAIL_MSG("UtilityAIDebuggerPlugin::_setup_session(): Failed to create the debugger label - Out of memory?");
    }
    
    //uai_session->add_session_tab(debugger_label);
    _debugger_session->add_session_tab(debugger_label);
}


bool UtilityAIDebuggerPlugin::_has_capture(const String &capture) const {
    return capture.begins_with("uai_");
}


bool UtilityAIDebuggerPlugin::_capture(const String &message, const Array &data, int32_t session_id) {
    //if( data.size() == 0 ) {
    //    return false;
    //}//
    //Ref<EditorDebuggerSession> uai_session = get_session(session_id);
    if(message == "uai_select_root") {
        if( UtilityAIBTRoot* btroot = godot::Object::cast_to<UtilityAIBTRoot>(data[0])) {
            WARN_PRINT("Got BT Root!");
            
        } else if( UtilityAISTRoot* stroot = godot::Object::cast_to<UtilityAISTRoot>(data[0])) {
            WARN_PRINT("Got ST Root!");
        } else if( UtilityAIAgent* agent = godot::Object::cast_to<UtilityAIAgent>(data[0])) {
            WARN_PRINT("Got Agent!");
        }  
        return true;
    } else if( message == "") {
        return true;
    }//endif message
    return false;
}


void UtilityAIDebuggerPlugin::_notification(int p_what) {

}
