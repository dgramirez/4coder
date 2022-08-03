#ifndef FCM_OTHER_COMMANDS_HPP
#define FCM_OTHER_COMMANDS_HPP

CUSTOM_COMMAND_SIG(FCM_RESERVED_FUNCTION)
CUSTOM_DOC("") {
    
}

CUSTOM_COMMAND_SIG(fcm_paste)
CUSTOM_DOC("") {
    clipboard_update_history_from_system(app, 0);
    i32 count = clipboard_count(0);
    if (count) {
        View_ID view = get_active_view(app, Access_ReadWriteVisible);
        if_view_has_highlighted_range_delete_range(app, view);
        
        set_next_rewrite(app, view, Rewrite_Paste);
        
        Managed_Scope scope = view_get_managed_scope(app, view);
        i32 *paste_index = scope_attachment(app, scope, view_paste_index_loc, i32);
        if (paste_index != 0) {
            *paste_index = 0;
            
            Scratch_Block scratch(app);
            String_Const_u8 string = push_clipboard_index(scratch, 0, *paste_index);
            if (string.size > 0) {
                Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
                i64 pos = view_get_cursor_pos(app, view);
                
                if (string.str[string.size - 1] == '\n') {
                    i64 line = get_line_number_from_pos(app, buffer, pos);
                    pos = get_line_side_pos(app, buffer, line, Side_Min);
                }
                else if (string.str[0] == '\n') {
                    i64 line = get_line_number_from_pos(app, buffer, pos);
                    pos = get_line_side_pos(app, buffer, line, Side_Max);
                }
                
                buffer_replace_range(app, buffer, Ii64(pos), string);
                view_set_mark(app, view, seek_pos(pos));
                view_set_cursor_and_preferred_x(app, view, seek_pos(pos + (i32)string.size));
                
                ARGB_Color argb = fcolor_resolve(fcolor_id(defcolor_paste));
                buffer_post_fade(app, buffer, 0.667f, Ii64_size(pos, string.size), argb);
            }
        }
    }
}

CUSTOM_COMMAND_SIG(fcm_paste_append)
CUSTOM_DOC("") {
    clipboard_update_history_from_system(app, 0);
    i32 count = clipboard_count(0);
    if (count) {
        View_ID view = get_active_view(app, Access_ReadWriteVisible);
        
        if_view_has_highlighted_range_delete_range(app, view);
        
        set_next_rewrite(app, view, Rewrite_Paste);
        
        Managed_Scope scope = view_get_managed_scope(app, view);
        i32 *paste_index = scope_attachment(app, scope, view_paste_index_loc, i32);
        if (paste_index != 0) {
            *paste_index = 0;
            
            Scratch_Block scratch(app);
            String_Const_u8 string = push_clipboard_index(scratch, 0, *paste_index);
            if (string.size > 0) {
                Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
                i64 pos = view_get_cursor_pos(app, view) + 1;
                
                if (string.str[string.size - 1] == '\n') {
                    i64 line = get_line_number_from_pos(app, buffer, pos);
                    pos = get_line_side_pos(app, buffer, line, Side_Min);
                }
                else if (string.str[0] == '\n') {
                    i64 line = get_line_number_from_pos(app, buffer, pos);
                    pos = get_line_side_pos(app, buffer, line, Side_Max);
                }
                
                buffer_replace_range(app, buffer, Ii64(pos), string);
                view_set_mark(app, view, seek_pos(pos));
                view_set_cursor_and_preferred_x(app, view, seek_pos(pos + (i32)string.size));
                
                ARGB_Color argb = fcolor_resolve(fcolor_id(defcolor_paste));
                buffer_post_fade(app, buffer, 0.667f, Ii64_size(pos, string.size), argb);
            }
        }
    }
}

CUSTOM_COMMAND_SIG(fcm_paste_line_above)
CUSTOM_DOC("") {
    clipboard_update_history_from_system(app, 0);
    i32 count = clipboard_count(0);
    if (count) {
        fcm_vb vb;
        fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
        if_view_has_highlighted_range_delete_range(app, vb.view);
        
        set_next_rewrite(app, vb.view, Rewrite_Paste);
        
        Managed_Scope scope = view_get_managed_scope(app, vb.view);
        i32 *paste_index = scope_attachment(app, scope, view_paste_index_loc, i32);
        if (paste_index != 0) {
            *paste_index = 0;
            
            Scratch_Block scratch(app);
            String_Const_u8 string = push_clipboard_index(scratch, 0, *paste_index);
            if (string.size > 0) {
                fcm_buffer_type cursor;
                fcm_get_cursor_info(app, vb, &cursor);
                
                string = push_u8_stringf(scratch, "%.*s\n", string_expand(string));
                
                i64 line_min = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
                buffer_replace_range(app, vb.buffer, Ii64(line_min), string);
                
                view_set_mark(app, vb.view, seek_pos(line_min));
                view_set_cursor_and_preferred_x(app, vb.view, seek_pos(line_min + (i32)string.size));
                
                ARGB_Color argb = fcolor_resolve(fcolor_id(defcolor_paste));
                buffer_post_fade(app, vb.buffer, 0.667f, Ii64_size(line_min, string.size), argb);
            }
        }
    }
}

CUSTOM_COMMAND_SIG(fcm_paste_line_below)
CUSTOM_DOC("") {
    clipboard_update_history_from_system(app, 0);
    i32 count = clipboard_count(0);
    if (count) {
        fcm_vb vb;
        fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
        if_view_has_highlighted_range_delete_range(app, vb.view);
        
        set_next_rewrite(app, vb.view, Rewrite_Paste);
        
        Managed_Scope scope = view_get_managed_scope(app, vb.view);
        i32 *paste_index = scope_attachment(app, scope, view_paste_index_loc, i32);
        if (paste_index != 0) {
            *paste_index = 0;
            
            Scratch_Block scratch(app);
            String_Const_u8 string = push_clipboard_index(scratch, 0, *paste_index);
            if (string.size > 0) {
                fcm_buffer_type cursor;
                fcm_get_cursor_info(app, vb, &cursor);
                
                string = push_u8_stringf(scratch, "\n%.*s", string_expand(string));
                
                i64 line_max = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
                buffer_replace_range(app, vb.buffer, Ii64(line_max), string);
                
                view_set_mark(app, vb.view, seek_pos(line_max));
                view_set_cursor_and_preferred_x(app, vb.view, seek_pos(line_max + (i32)string.size));
                
                ARGB_Color argb = fcolor_resolve(fcolor_id(defcolor_paste));
                buffer_post_fade(app, vb.buffer, 0.667f, Ii64_size(line_max, string.size), argb);
            }
        }
    }
}

CUSTOM_COMMAND_SIG(fcm_substitute_one_in_file)
CUSTOM_DOC("") {
    
}

CUSTOM_COMMAND_SIG(fcm_substitute_all_in_file)
CUSTOM_DOC("") {
    
}

CUSTOM_COMMAND_SIG(fcm_substitute_all_in_project_buffer)
CUSTOM_DOC("") {
    
}



CUSTOM_COMMAND_SIG(fcm_replace_one)
CUSTOM_DOC("") {
    // Query Bar Setup
    Query_Bar_Group group(app);
    Query_Bar bar = {};
    
    // replace
    u8 replace_string_space[256];
    bar.prompt = string_u8_litexpr("Replace with: ");
    bar.string = SCu8(replace_string_space, (u64)0);
    bar.string_capacity = sizeof(replace_string_space);
    
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    i64 cursor_pos = view_get_cursor_pos(app, view);
    if (query_user_string(app, &bar))
        fcm_search_and_replace(app, Scan_Forward, cursor_pos, SCu8(), bar.string);
}

CUSTOM_COMMAND_SIG(fcm_replace_one_reverse)
CUSTOM_DOC("") {
    // Query Bar Setup
    Query_Bar_Group group(app);
    Query_Bar bar = {};
    
    // replace
    u8 replace_string_space[256];
    bar.prompt = string_u8_litexpr("Replace with: ");
    bar.string = SCu8(replace_string_space, (u64)0);
    bar.string_capacity = sizeof(replace_string_space);
    
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    i64 cursor_pos = view_get_cursor_pos(app, view);
    if (query_user_string(app, &bar))
        fcm_search_and_replace(app, Scan_Backward, cursor_pos, SCu8(), bar.string);
}

internal void
fcm_get_view_and_buffer(Application_Links *app, Access_Flag access, fcm_vb *data) {
    data->view = get_active_view(app, access);
    data->buffer = view_get_buffer(app, data->view, access);
}

internal void
fcm_get_cursor_info(Application_Links *app, fcm_vb vb, fcm_buffer_type *cursor) {
    cursor->pos = view_get_cursor_pos(app, vb.view);
    cursor->line = get_line_number_from_pos(app, vb.buffer, cursor->pos);
}

internal void
fcm_get_mark_info(Application_Links *app, fcm_vb vb, fcm_buffer_type *mark) {
    mark->pos = view_get_mark_pos(app, vb.view);
    mark->line = get_line_number_from_pos(app, vb.buffer, mark->pos);
}

internal void
fcm_get_end_of_buffer(Application_Links *app, fcm_vb vb, fcm_buffer_type *buffer) {
    buffer->pos = buffer_get_size(app, vb.buffer);
    buffer->line = get_line_number_from_pos(app, vb.buffer, buffer->pos);
}

internal void 
fcm_set_mapid_mode(Application_Links* app, Command_Map_ID mapid, i64 flags) {
    fcm_vb data;
    fcm_get_view_and_buffer(app, 0, &data);
    Managed_Scope scope = buffer_get_managed_scope(app, data.buffer);
    Command_Map_ID* map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID );
    
    *map_id_ptr = mapid;
    fcm_flags = flags;
}

internal void
fcm_search_and_replace(Application_Links *app, Scan_Direction start_scan, i64 first_pos, 
                       String_Const_u8 query_init, String_Const_u8 replace_str) {
    
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
    if (!buffer_exists(app, buffer)){
        return;
    }
    
    i64 buffer_size = buffer_get_size(app, buffer);
    
    Query_Bar_Group group(app);
    Query_Bar bar = {};
    if (start_query_bar(app, &bar, 0) == 0){
        return;
    }
    
    Vec2_f32 old_margin = {};
    Vec2_f32 old_push_in = {};
    view_get_camera_bounds(app, view, &old_margin, &old_push_in);
    
    Vec2_f32 margin = old_margin;
    margin.y = clamp_bot(200.f, margin.y);
    view_set_camera_bounds(app, view, margin, old_push_in);
    
    Scan_Direction scan = start_scan;
    i64 pos = first_pos;
    
    u8 bar_string_space[256];
    bar.string = SCu8(bar_string_space, query_init.size);
    block_copy(bar.string.str, query_init.str, query_init.size);
    
    String_Const_u8 isearch_str = string_u8_litexpr("I-Search: ");
    String_Const_u8 rsearch_str = string_u8_litexpr("Reverse-I-Search: ");
    
    u64 match_size = bar.string.size;
    
    User_Input in = {};
    for (;;){
        switch (scan){
            case Scan_Forward:
            {
                bar.prompt = isearch_str;
            }break;
            case Scan_Backward:
            {
                bar.prompt = rsearch_str;
            }break;
        }
        isearch__update_highlight(app, view, Ii64_size(pos, match_size));
        
        in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
        if (in.abort){
            break;
        }
        
        String_Const_u8 string = to_writable(&in);
        
        b32 string_change = false;
        if (match_key_code(&in, KeyCode_Return) ||
            match_key_code(&in, KeyCode_Tab)){
            Input_Modifier_Set *mods = &in.event.key.modifiers;
            if (has_modifier(mods, KeyCode_Control)){
                bar.string.size = cstring_length(previous_isearch_query);
                block_copy(bar.string.str, previous_isearch_query, bar.string.size);
            }
            else if (has_modifier(mods, KeyCode_Shift)) {
                Range_i64 range;
                range.start = view_get_cursor_pos(app, view);
                range.end = range.start + bar.string.size;
                buffer_replace_range(app, buffer, range, replace_str);
                string_change = true;
            }
            else{
                Range_i64 range;
                range.start = view_get_cursor_pos(app, view);
                range.end = range.start + bar.string.size;
                buffer_replace_range(app, buffer, range, replace_str);
                break;
            }
        }
        else if (string.str != 0 && string.size > 0){
            String_u8 bar_string = Su8(bar.string, sizeof(bar_string_space));
            string_append(&bar_string, string);
            bar.string = bar_string.string;
            string_change = true;
        }
        else if (match_key_code(&in, KeyCode_Backspace)){
            if (is_unmodified_key(&in.event)){
                u64 old_bar_string_size = bar.string.size;
                bar.string = backspace_utf8(bar.string);
                string_change = (bar.string.size < old_bar_string_size);
            }
            else if (has_modifier(&in.event.key.modifiers, KeyCode_Control)){
                if (bar.string.size > 0){
                    string_change = true;
                    bar.string.size = 0;
                }
            }
        }
        
        b32 do_scan_action = false;
        b32 do_scroll_wheel = false;
        Scan_Direction change_scan = scan;
        if (!string_change){
            if (match_key_code(&in, KeyCode_PageDown) ||
                match_key_code(&in, KeyCode_Down)){
                change_scan = Scan_Forward;
                do_scan_action = true;
            }
            else if (match_key_code(&in, KeyCode_PageUp) ||
                     match_key_code(&in, KeyCode_Up)){
                change_scan = Scan_Backward;
                do_scan_action = true;
            }
            else{
                // NOTE(allen): is the user trying to execute another command?
                View_Context ctx = view_current_context(app, view);
                Mapping *mapping = ctx.mapping;
                Command_Map *map = mapping_get_map(mapping, ctx.map_id);
                Command_Binding binding = map_get_binding_recursive(mapping, map, &in.event);
                if (binding.custom != 0){
                    if (binding.custom == search){
                        change_scan = Scan_Forward;
                        do_scan_action = true;
                    }
                    else if (binding.custom == reverse_search){
                        change_scan = Scan_Backward;
                        do_scan_action = true;
                    }
                    else{
                        Command_Metadata *metadata = get_command_metadata(binding.custom);
                        if (metadata != 0){
                            if (metadata->is_ui){
                                view_enqueue_command_function(app, view, binding.custom);
                                break;
                            }
                        }
                        binding.custom(app);
                    }
                }
                else{
                    leave_current_input_unhandled(app);
                }
            }
        }
        
        if (string_change){
            switch (scan){
                case Scan_Forward:
                {
                    i64 new_pos = 0;
                    seek_string_insensitive_forward(app, buffer, pos - 1, 0, bar.string, &new_pos);
                    if (new_pos < buffer_size){
                        pos = new_pos;
                        match_size = bar.string.size;
                    }
                }break;
                
                case Scan_Backward:
                {
                    i64 new_pos = 0;
                    seek_string_insensitive_backward(app, buffer, pos + 1, 0, bar.string, &new_pos);
                    if (new_pos >= 0){
                        pos = new_pos;
                        match_size = bar.string.size;
                    }
                }break;
            }
        }
        else if (do_scan_action){
            scan = change_scan;
            switch (scan){
                case Scan_Forward:
                {
                    i64 new_pos = 0;
                    seek_string_insensitive_forward(app, buffer, pos, 0, bar.string, &new_pos);
                    if (new_pos < buffer_size){
                        pos = new_pos;
                        match_size = bar.string.size;
                    }
                }break;
                
                case Scan_Backward:
                {
                    i64 new_pos = 0;
                    seek_string_insensitive_backward(app, buffer, pos, 0, bar.string, &new_pos);
                    if (new_pos >= 0){
                        pos = new_pos;
                        match_size = bar.string.size;
                    }
                }break;
            }
        }
        else if (do_scroll_wheel){
            mouse_wheel_scroll(app);
        }
    }
    
    view_disable_highlight_range(app, view);
    
    if (in.abort){
        u64 size = bar.string.size;
        size = clamp_top(size, sizeof(previous_isearch_query) - 1);
        block_copy(previous_isearch_query, bar.string.str, size);
        previous_isearch_query[size] = 0;
    }
    
    view_set_camera_bounds(app, view, old_margin, old_push_in);
}

function b32
fcm_if_view_has_highlighted_range_delete_range(Application_Links *app, View_ID view_id) {
    b32 result = false;
    if (fcm_marks.count) {
        Range_i64 range = get_view_range(app, view_id);
        Buffer_ID buffer = view_get_buffer(app, view_id, Access_ReadWriteVisible);
        buffer_replace_range(app, buffer, range, string_u8_litexpr(""));
        result = true;
    }
    return(result);
}

#endif // FCM_OTHER_COMMANDS_HPP
