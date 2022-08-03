#ifndef FCM_COMMAND_HPP
#define FCM_COMAND_HPP

CUSTOM_COMMAND_SIG(fcm_command)
CUSTOM_DOC("") {
    // Query Bar Setup
    Query_Bar_Group group(app);
    Query_Bar bar = {};
    
    // replace
    u8 replace_string_space[256];
    bar.prompt = string_u8_litexpr("Command: ");
    bar.string = SCu8(replace_string_space, (u64)0);
    bar.string_capacity = sizeof(replace_string_space);
    
    if (query_user_string(app, &bar)) {
        fcm_command_parse(app, bar.string);
    }
}

internal b32
fcm_command_parse(Application_Links *app, String_Const_u8 s) {
    if (s.size == 0)
        return true;
    
    if (fcm_is_number(s))
        return fcm_command_line_goto(app, s);
    
    if (s.str[0] == 'y')
        return fcm_command_copy(app, s);
    
    if (s.str[0] == 'x')
        return fcm_command_cut(app, s);
    
    if (s.str[0] == 'd')
        return fcm_command_delete(app, s);
    
    if (s.str[0] == 'q')
        return fcm_command_quit(app, s);
    
    b32 percent = false;
    if (s.str[0] == '%') {
        percent = true;
        ++s.str;
        --s.size;
    }
    
    if (s.str[0] == 'w')
        return fcm_command_save(app, s, percent);
    
    if (s.str[0] == '%' || s.str[0] == 's')
        return fcm_command_substitute(app, s, percent);
    
    return false;
}

internal b32
fcm_command_line_goto(Application_Links *app, String_Const_u8 s) {
    i32 line_number = (i32)string_to_integer(s, 10);
    View_ID view = get_active_view(app, Access_ReadVisible);
    view_set_cursor_and_preferred_x(app, view, seek_line_col(line_number, 0));
    
    return true;
}

internal b32
fcm_command_copy(Application_Links *app, String_Const_u8 s) {
    if (s.size == 1) {
        fcm_copy_line(app);
        return true;
    }
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range;
    if (!fcm_command_buffer_get_range(app, vb, s, &range))
        return false;
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
    
    return true;
}

internal b32
fcm_command_cut(Application_Links *app, String_Const_u8 s) {
    if (s.size == 1) {
        fcm_cut_line(app);
        return true;
    }
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range;
    if (!fcm_command_buffer_get_range(app, vb, s, &range))
        return false;
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
    
    return true;
}

internal b32
fcm_command_delete(Application_Links *app, String_Const_u8 s) {
    if (s.size == 1) {
        fcm_delete_line(app);
        return true;
    }
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range;
    if (!fcm_command_buffer_get_range(app, vb, s, &range))
        return false;
    
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
    
    return true;
}

internal b32
fcm_command_quit(Application_Links *app, String_Const_u8 s) {
    if (s.size == 1) {
        exit_4coder(app);
        return true;
    }
    else if (s.size == 2 && s.str[1] == '!') {
        hard_exit(app);
        return true;
    }
    
    return false;
}

internal b32
fcm_command_save(Application_Links *app, String_Const_u8 s, b32 percent) {
    // TODO(tiny): Perhaps if there is a space with a file name, then save to a new file name based on directory.
    //             Priority: Low [Reason: A Short Work Around is Available. Will do later for convenience]
    if (percent)
        save_all_dirty_buffers(app);
    else
        save(app);
    
    if (s.size > 1 && s.str[1] == 'q') {
        ++s.str;
        --s.size;
        return fcm_command_quit(app, s);
    }
    
    return true;
}

internal b32
fcm_command_substitute(Application_Links *app, String_Const_u8 s, b32 percent) {
    // TODO(tiny): Do Substitution based on :s/old/new/g OR :%s/old/new/g.
    //             Priority: Low [Reason: Ctrl + Shift + H Exists. Will do later for convenience]
    return true;
}

function b32
fcm_is_number(String_Const_u8 s) {
    while (s.size) {
        if (s.str[0] < '0' || s.str[0] > '9')
            return 0;
        
        ++s.str;
        --s.size;
    }
    return 1;
}

function b32
fcm_command_buffer_get_range(Application_Links *app, fcm_vb vb, String_Const_u8 s, Range_i64 *range) {
    // Getting Direction
    i64 direction = 0;
    if (s.str[s.size - 1] == 'j')
        direction = FCM_DOWN;
    else if (s.str[s.size - 1] == 'k')
        direction = FCM_UP;
    else
        return false;
    
    // Error Check: Ensure somethign like dj or dk is not used.
    s.size -= 2;
    if (!s.size)
        return false;
    ++s.str;
    
    // Get Line Count
    i64 line_count = 0;
    if (fcm_is_number(s))
        line_count = (i32)string_to_integer(s, 10);
    else
        return false;
    
    // Get Current Line
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    if (direction == FCM_UP) {
        range->start = get_line_side_pos(app, vb.buffer, cursor.line - line_count, Side_Min);
        range->end = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max) + 1;
    }
    else {
        range->start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
        range->end = get_line_side_pos(app, vb.buffer, cursor.line + line_count, Side_Max) + 1;
    }
    
    return true;
}


#endif // FCM_COMMAND_HPP
