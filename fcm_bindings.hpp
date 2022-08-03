#ifndef FCM_BINDINGS_HPP
#define FCM_BINDINGS_HPP

internal void
fcm_setup_bindings_shared(Mapping *mapping) {
    // Setup Mapping
    MappingScope();
    SelectMapping(mapping);
    SelectMap(fcm_mapid_shared);
    
    // 4Coder Core
    BindCore(fcm_startup, CoreCode_Startup);
    BindCore(default_try_exit, CoreCode_TryExit);
    
    // Mode Switch
    Bind(fcm_mode_normal, KeyCode_Escape);
    
    // Modified 4Coder Bindings
    Bind2(fcm_interactive_open_or_new, KeyCode_Alt, KeyCode_O);
    Bind2(fcm_command_lister, KeyCode_Alt, KeyCode_X);
    Bind3(fcm_project_command_lister, KeyCode_Alt, KeyCode_Shift, KeyCode_X);
    Bind2(fcm_change_active_panel, KeyCode_Alt, KeyCode_Period);
    Bind2(fcm_change_active_panel_backwards, KeyCode_Alt, KeyCode_Comma);
    Bind2(save, KeyCode_Control, KeyCode_S);
    Bind2(exit_4coder, KeyCode_Alt, KeyCode_F4);
    
    // Functions Keys
    Bind(project_fkey_command, KeyCode_F1);
    Bind(project_fkey_command, KeyCode_F2);
    Bind(project_fkey_command, KeyCode_F3);
    Bind(project_fkey_command, KeyCode_F4);
    Bind(project_fkey_command, KeyCode_F5);
    Bind(project_fkey_command, KeyCode_F6);
    Bind(project_fkey_command, KeyCode_F7);
    Bind(project_fkey_command, KeyCode_F8);
    Bind(FCM_RESERVED_FUNCTION, KeyCode_F9);
    Bind(FCM_RESERVED_FUNCTION, KeyCode_F10);
    Bind(toggle_fullscreen, KeyCode_F11);
    Bind(toggle_filebar, KeyCode_F12);
    
    // Other Functional Keys (Home, End, etc.)
    Bind(goto_beginning_of_file, KeyCode_Home);
    Bind(goto_end_of_file, KeyCode_End);
    Bind(page_up, KeyCode_PageUp);
    Bind(page_down, KeyCode_PageDown);
}

internal void
fcm_setup_bindings_normal(Mapping *mapping) {
    // Setup Mapping
    MappingScope();
    SelectMapping(mapping);
    SelectMap(fcm_mapid_normal);
    ParentMap(fcm_mapid_shared);
    
    // Mode Switch [15/18: 111111 11111 1111 1011]
    Bind(fcm_mode_type_insert, KeyCode_I);
    Bind2(fcm_mode_type_insert_append, KeyCode_Shift, KeyCode_I);
    Bind2(fcm_mode_type_insert_bol, KeyCode_Control, KeyCode_I);
    Bind2(fcm_mode_type_insert_eol, KeyCode_Alt, KeyCode_I);
    Bind3(fcm_mode_type_insert_new_line_above, KeyCode_Control, KeyCode_Alt, KeyCode_I);
    Bind3(fcm_mode_type_insert_new_line_below, KeyCode_Control, KeyCode_Shift, KeyCode_I);
    
    Bind(fcm_mode_type_replace, KeyCode_R);
    Bind2(fcm_mode_type_replace_append, KeyCode_Shift, KeyCode_R);
    Bind2(fcm_mode_type_replace_bol, KeyCode_Control, KeyCode_R);
    Bind2(fcm_mode_type_replace_eol, KeyCode_Alt, KeyCode_R);
    Bind3(fcm_mode_type_replace_char, KeyCode_Control, KeyCode_Shift, KeyCode_R);
    
    Bind(fcm_mode_buffer_copy, KeyCode_Y);
    Bind(fcm_mode_buffer_copy, KeyCode_C);
    Bind(fcm_mode_buffer_cut, KeyCode_X);
    Bind(fcm_mode_buffer_delete, KeyCode_D);
    
    Bind(fcm_mode_visual_highlight, KeyCode_V);
    Bind2(fcm_mode_visual_marked, KeyCode_Control, KeyCode_Space);
    Bind3(fcm_mode_visual_line, KeyCode_Control, KeyCode_Shift, KeyCode_Space);
    Bind3(fcm_mode_visual_line, KeyCode_Control, KeyCode_Shift, KeyCode_V);
    
    Bind2(fcm_command, KeyCode_Shift, KeyCode_Semicolon);
    
    // Arrow Keys [Check]
    Bind(fcm_move_up, KeyCode_Up);
    Bind2(FCM_RESERVED_FUNCTION, KeyCode_Shift, KeyCode_Up); // TODO(tiny): Maybe Visual Highlight & Move Up?
    Bind2(move_up_to_blank_line_end, KeyCode_Control, KeyCode_Up);
    Bind2(move_line_up, KeyCode_Alt, KeyCode_Up);
    Bind3(select_prev_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Up);
    
    Bind(fcm_move_down, KeyCode_Down);
    Bind2(FCM_RESERVED_FUNCTION, KeyCode_Shift, KeyCode_Down); // TODO(tiny): Maybe Visual Highlight & Move Down?
    Bind2(move_down_to_blank_line_end, KeyCode_Control, KeyCode_Down);
    Bind2(move_line_down, KeyCode_Alt, KeyCode_Down);
    Bind3(select_next_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Down);
    
    Bind(fcm_move_left, KeyCode_Left);
    Bind2(fcm_move_left_word, KeyCode_Shift, KeyCode_Left);
    Bind2(fcm_move_left_name, KeyCode_Control, KeyCode_Left);
    Bind2(fcm_move_left_bol, KeyCode_Alt, KeyCode_Left);
    Bind3(fcm_move_prev_top_most_scope, KeyCode_Control, KeyCode_Alt, KeyCode_Left);
    
    Bind(fcm_move_right, KeyCode_Right);
    Bind2(fcm_move_right_word, KeyCode_Shift, KeyCode_Right);
    Bind2(fcm_move_right_name, KeyCode_Control, KeyCode_Right);
    Bind2(fcm_move_right_eol, KeyCode_Alt, KeyCode_Right);
    Bind3(fcm_move_next_scope_after_current, KeyCode_Control, KeyCode_Alt, KeyCode_Right);
    
    // Type Shortcuts[Check]
    Bind(fcm_paste, KeyCode_P);
    Bind2(fcm_paste, KeyCode_Control, KeyCode_V);
    Bind2(fcm_paste_append, KeyCode_Shift, KeyCode_P);
    Bind2(fcm_paste_line_above, KeyCode_Control, KeyCode_P);
    Bind2(fcm_paste_line_below, KeyCode_Alt, KeyCode_P);
    
    Bind(undo, KeyCode_U);
    Bind2(undo, KeyCode_Control, KeyCode_Z);
    Bind2(redo, KeyCode_Control, KeyCode_Y);
    Bind3(redo, KeyCode_Control, KeyCode_Shift, KeyCode_Z);
    
    // Buffer Shortcuts [Check]
    Bind(backspace_char, KeyCode_Backspace);
    Bind(delete_char, KeyCode_Delete);
    Bind2(fcm_copy_line, KeyCode_Control, KeyCode_C);
    Bind2(fcm_cut_line, KeyCode_Control, KeyCode_X);
    Bind2(fcm_delete_line, KeyCode_Control, KeyCode_D);
    
    // Other Shortcuts [Check]
    Bind(fcm_select_location_same_panel, KeyCode_Return);
    Bind2(search, KeyCode_Control, KeyCode_F);
    Bind3(fcm_list_substring_locations_other_panel, KeyCode_Control, KeyCode_Shift, KeyCode_F);
    Bind2(goto_line, KeyCode_Control, KeyCode_G);
    Bind2(fcm_replace_one, KeyCode_Control, KeyCode_H);
    Bind3(replace_in_buffer, KeyCode_Control, KeyCode_Shift, KeyCode_H);
    Bind3(fcm_replace_in_all_buffers, KeyCode_Control, KeyCode_Alt, KeyCode_H);
    
    // (Vim Bindings) [Check]
    Bind2(seek_beginning_of_line, KeyCode_Shift, KeyCode_BackwardSlash);
    Bind2(seek_end_of_line, KeyCode_Shift, KeyCode_4);
    Bind2(move_up_to_blank_line_end, KeyCode_Shift, KeyCode_LeftBracket);
    Bind2(move_down_to_blank_line_end, KeyCode_Shift, KeyCode_RightBracket);
    Bind(goto_beginning_of_file, KeyCode_G);
    Bind2(goto_end_of_file, KeyCode_Shift, KeyCode_G);
    Bind(search, KeyCode_ForwardSlash);
    Bind2(reverse_search, KeyCode_Shift, KeyCode_ForwardSlash);
    
    Bind(fcm_mode_type_insert_append, KeyCode_A);
    Bind2(fcm_mode_type_insert_eol, KeyCode_Shift, KeyCode_A);
    Bind(fcm_mode_type_insert_new_line_above, KeyCode_O);
    Bind2(fcm_mode_type_insert_new_line_below, KeyCode_Shift, KeyCode_O);
}

internal void
fcm_setup_bindings_type(Mapping *mapping) {
    // Setup Mapping
    MappingScope();
    SelectMapping(mapping);
    SelectMap(fcm_mapid_type);
    ParentMap(fcm_mapid_shared);
    
    // Mode Switching [Check]
    Bind(fcm_toggle_mode_type, KeyCode_Insert);
    
    // Input [12/15: 1111 111100 11110]
    BindTextInput(fcm_write_text_and_auto_indent);
    Bind2(open_long_braces, KeyCode_Control, KeyCode_LeftBracket);
    Bind2(open_long_braces_semicolon, KeyCode_Alt, KeyCode_LeftBracket);
    Bind3(open_long_braces_break, KeyCode_Control, KeyCode_Alt, KeyCode_LeftBracket);
    
    Bind(backspace_char, KeyCode_Backspace);
    Bind2(fcm_type_delete_left_word, KeyCode_Shift, KeyCode_Backspace);
    Bind2(fcm_type_delete_left_name, KeyCode_Control, KeyCode_Backspace);
    Bind2(fcm_type_delete_bol, KeyCode_Alt, KeyCode_Backspace);
    Bind3(fcm_type_delete_top_most_scope, KeyCode_Alt, KeyCode_Shift, KeyCode_Backspace);
    Bind3(delete_current_scope, KeyCode_Control, KeyCode_Alt, KeyCode_Backspace);
    
    Bind(delete_char, KeyCode_Delete);
    Bind2(fcm_type_delete_right_word, KeyCode_Shift, KeyCode_Delete);
    Bind2(fcm_type_delete_right_name, KeyCode_Control, KeyCode_Delete);
    Bind2(fcm_type_delete_eol, KeyCode_Alt, KeyCode_Delete);
    Bind3(fcm_type_delete_next_scope_after_current, KeyCode_Alt, KeyCode_Shift, KeyCode_Delete);
    
    // Arrow Keys [Check]
    Bind(move_up, KeyCode_Up);
    Bind2(FCM_RESERVED_FUNCTION, KeyCode_Shift, KeyCode_Up); // TODO(tiny): Maybe Visual Highlight & Move Up?
    Bind2(move_up_to_blank_line_end, KeyCode_Control, KeyCode_Up);
    Bind2(move_line_up, KeyCode_Alt, KeyCode_Up);
    Bind3(select_prev_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Up);
    
    Bind(move_down, KeyCode_Down);
    Bind2(FCM_RESERVED_FUNCTION, KeyCode_Shift, KeyCode_Down); // TODO(tiny): Maybe Visual Highlight & Move Down?
    Bind2(move_down_to_blank_line_end, KeyCode_Control, KeyCode_Down);
    Bind2(move_line_down, KeyCode_Alt, KeyCode_Down);
    Bind3(select_next_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Down);
    
    Bind(move_left, KeyCode_Left);
    Bind2(fcm_move_left_word, KeyCode_Shift, KeyCode_Left);
    Bind2(fcm_move_left_name, KeyCode_Control, KeyCode_Left);
    Bind2(seek_beginning_of_line, KeyCode_Alt, KeyCode_Left);
    Bind3(select_prev_top_most_scope, KeyCode_Control, KeyCode_Alt, KeyCode_Left);
    
    Bind(move_right, KeyCode_Right);
    Bind2(fcm_move_right_word, KeyCode_Shift, KeyCode_Right);
    Bind2(fcm_move_right_name, KeyCode_Control, KeyCode_Right);
    Bind2(seek_end_of_line, KeyCode_Alt, KeyCode_Right);
    Bind3(select_next_scope_after_current, KeyCode_Control, KeyCode_Alt, KeyCode_Right);
    
    // Type Shortcuts [Check]
    Bind2(fcm_paste, KeyCode_Control, KeyCode_V);
    Bind2(undo, KeyCode_Control, KeyCode_Z);
    Bind2(redo, KeyCode_Control, KeyCode_Y);
    Bind3(redo, KeyCode_Control, KeyCode_Shift, KeyCode_Z);
    
    // Buffer Shortcuts [Check]
    Bind2(fcm_copy_line, KeyCode_Control, KeyCode_C);
    Bind2(fcm_cut_line, KeyCode_Control, KeyCode_X);
    Bind2(fcm_delete_line, KeyCode_Control, KeyCode_D);
}

internal void
fcm_setup_bindings_buffer(Mapping *mapping) {
    // Setup Mapping
    MappingScope();
    SelectMapping(mapping);
    SelectMap(fcm_mapid_buffer);
    ParentMap(fcm_mapid_shared);
    
    // Mode Switching [Check]
    Bind(fcm_mode_buffer_toggle, KeyCode_Insert);
    
    // Buffer Manipulation [Check]
    Bind2(fcm_buffer_do_left_word, KeyCode_Shift, KeyCode_Left);
    Bind2(fcm_buffer_do_right_word, KeyCode_Shift, KeyCode_Right);
    Bind2(fcm_buffer_do_left_name, KeyCode_Control, KeyCode_Left);
    Bind2(fcm_buffer_do_right_name, KeyCode_Control, KeyCode_Right);
    Bind2(fcm_buffer_do_bol, KeyCode_Alt, KeyCode_Left);
    Bind2(fcm_buffer_do_eol, KeyCode_Alt, KeyCode_Right);
    
    Bind(fcm_buffer_do_current_line_and_above, KeyCode_Up);
    Bind(fcm_buffer_do_current_line_and_below, KeyCode_Down);
    
    /* TODO(tiny)
    Bind3(fcm_buffer_do_top_most_scope, KeyCode_Control, KeyCode_Alt, KeyCode_Left);
Bind3(fcm_buffer_do_next_scope_after_current, KeyCode_Control, KeyCode_Alt, KeyCode_Right);

        Bind2(fcm_buffer_do_up_to_blank_line_end, KeyCode_Control, KeyCode_Up);
        Bind2(fcm_buffer_do_down_to_blank_line_end, KeyCode_Control, KeyCode_Down);
        Bind3(fcm_buffer_do_prev_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Up);
        Bind3(fcm_buffer_do_next_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Down);
        */
    
    // (Vim Bindings) [8/10: 110011 1111]
    Bind2(fcm_buffer_do_bol, KeyCode_Shift, KeyCode_BackwardSlash);
    Bind2(fcm_buffer_do_eol, KeyCode_Shift, KeyCode_4);
    //Bind2(fcm_buffer_do_up_to_blank_line_end, KeyCode_Shift, KeyCode_LeftBracket);
    //Bind2(fcm_buffer_do_down_to_blank_line_end, KeyCode_Shift, KeyCode_RightBracket);
    Bind(fcm_buffer_do_all_lines_on_and_above, KeyCode_G);
    Bind2(fcm_buffer_do_all_lines_on_and_below, KeyCode_Shift, KeyCode_G);
    
    Bind(fcm_buffer_cut_current_line, KeyCode_X);
    Bind(fcm_buffer_copy_current_line, KeyCode_Y);
    Bind(fcm_buffer_copy_current_line, KeyCode_C);
    Bind(fcm_buffer_delete_current_line, KeyCode_D);
}

internal void
fcm_setup_bindings_visual(Mapping *mapping) {
    // Setup Mapping
    MappingScope();
    SelectMapping(mapping);
    SelectMap(fcm_mapid_visual);
    ParentMap(fcm_mapid_shared);
    
    // Typing
    BindTextInput(fcm_write_text_and_auto_indent);
    Bind(fcm_visual_type_backspace, KeyCode_Backspace);
    Bind(fcm_visual_type_delete, KeyCode_Delete);
    
    // Arrow Keys [Check]
    Bind(fcm_move_up, KeyCode_Up);
    Bind2(FCM_RESERVED_FUNCTION, KeyCode_Shift, KeyCode_Up); // TODO(tiny): Maybe Visual Highlight & Move Up?
    Bind2(move_up_to_blank_line_end, KeyCode_Control, KeyCode_Up);
    Bind2(move_line_up, KeyCode_Alt, KeyCode_Up);
    Bind3(select_prev_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Up);
    
    Bind(fcm_move_down, KeyCode_Down);
    Bind2(FCM_RESERVED_FUNCTION, KeyCode_Shift, KeyCode_Down); // TODO(tiny): Maybe Visual Highlight & Move Down?
    Bind2(move_down_to_blank_line_end, KeyCode_Control, KeyCode_Down);
    Bind2(move_line_down, KeyCode_Alt, KeyCode_Down);
    Bind3(select_next_scope_absolute, KeyCode_Control, KeyCode_Alt, KeyCode_Down);
    
    Bind(fcm_move_left, KeyCode_Left);
    Bind2(fcm_move_left_word, KeyCode_Shift, KeyCode_Left);
    Bind2(fcm_move_left_name, KeyCode_Control, KeyCode_Left);
    Bind2(fcm_move_left_bol, KeyCode_Alt, KeyCode_Left);
    Bind3(fcm_move_prev_top_most_scope, KeyCode_Control, KeyCode_Alt, KeyCode_Left);
    
    Bind(fcm_move_right, KeyCode_Right);
    Bind2(fcm_move_right_word, KeyCode_Shift, KeyCode_Right);
    Bind2(fcm_move_right_name, KeyCode_Control, KeyCode_Right);
    Bind2(fcm_move_right_eol, KeyCode_Alt, KeyCode_Right);
    Bind3(fcm_move_next_scope_after_current, KeyCode_Control, KeyCode_Alt, KeyCode_Right);
    
    // Visual
    Bind(fcm_visual_back_to_normal_mode, KeyCode_Escape);
    Bind2(fcm_visual_start_type, KeyCode_Control, KeyCode_I);
    
    Bind2(fcm_visual_copy, KeyCode_Control, KeyCode_C);
    Bind2(fcm_visual_cut, KeyCode_Control, KeyCode_X);
    Bind2(fcm_visual_delete, KeyCode_Control, KeyCode_D);
    Bind2(fcm_visual_paste, KeyCode_Control, KeyCode_V);
    
    Bind(fcm_visual_type_or_copy, KeyCode_Y);
    Bind(fcm_visual_type_or_cut, KeyCode_X);
    Bind(fcm_visual_type_or_delete, KeyCode_D);
    Bind(fcm_visual_type_or_paste, KeyCode_P);
    
    Bind2(fcm_visual_move_up, KeyCode_Alt, KeyCode_Up);
    Bind2(fcm_visual_move_down, KeyCode_Alt, KeyCode_Down);
    Bind2(fcm_visual_replace_range, KeyCode_Control, KeyCode_H);
    
    Bind2(fcm_add_mark, KeyCode_Control, KeyCode_Space);
}

internal void
fcm_setup_binding_parent(Mapping *mapping, i64 mapid) {
    // Use shared mapid for any other mapping that exists
    MappingScope();
    SelectMapping(mapping);
    SelectMap(mapid);
    ParentMap(fcm_mapid_shared);
}

#endif // FCM_BINDINGS_HPP
