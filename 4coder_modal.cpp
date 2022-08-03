/*
4coder_modal.cpp - Supplies the default bindings used for default 4coder behavior.
*/

// TOP

#if !defined(FCODER_MODAL_DEFAULT_BINDINGS_CPP)
#define FCODER_MODAL_DEFAULT_BINDINGS_CPP

#include "../4coder_default_include.cpp"

#if !defined(META_PASS)
// NOTE(allen): Users can declare their own managed IDs here.
#include "generated/managed_id_metadata.cpp"
#endif

#include "4coder_modal.h"
#include "fcm_4coder_modification.hpp"
#include "fcm_bindings.hpp"
#include "fcm_buffer.hpp"
#include "fcm_command.hpp"
#include "fcm_movement.hpp"
#include "fcm_normal.hpp"
#include "fcm_other_commands.hpp"
#include "fcm_type.hpp"
#include "fcm_visual.hpp"

void
custom_layer_init(Application_Links *app){
    Thread_Context *tctx = get_thread_context(app);
    
    // NOTE(allen): setup for default framework
    default_framework_init(app);
    
    // NOTE(allen): default hooks and command maps
    fcm_set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
#if OS_MAC
    setup_mac_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#else
    setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#endif
    setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
    
    fcm_mapid_shared = vars_save_string_lit("shared_mode");
    fcm_mapid_normal = vars_save_string_lit("normal_mode");
    fcm_mapid_type = vars_save_string_lit("type_mode");
    fcm_mapid_buffer = vars_save_string_lit("buffer_mode");
    fcm_mapid_visual = vars_save_string_lit("visual_mode");
    
    fcm_setup_bindings_shared(&framework_mapping);
    fcm_setup_bindings_normal(&framework_mapping);
    fcm_setup_bindings_type(&framework_mapping);
    fcm_setup_bindings_buffer(&framework_mapping);
    fcm_setup_bindings_visual(&framework_mapping);
    
    /* This is to make sure that the default bindings on the buffers will be mapid_normal. */
    fcm_setup_binding_parent(&framework_mapping, file_map_id);
    fcm_setup_binding_parent(&framework_mapping, code_map_id);
}

#endif // FCODER_MODAL_DEFAULT_BINDINGS_CPP

// BOTTOM
