#ifndef FCM_TYPE_HPP
#define FCM_TYPE_HPP

internal void
fcm_set_mode_type_insert(Application_Links *app, i64 type_flags) {
    fcm_set_mapid_mode(app, fcm_mapid_type, FCM_MODE_TYPE | FCM_TYPE_INSERT | type_flags);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_CYAN;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff293134;
}

internal void
fcm_set_mode_type_replace(Application_Links *app, i64 type_flags) {
    fcm_set_mapid_mode(app, fcm_mapid_type, FCM_MODE_TYPE | FCM_TYPE_REPLACE | type_flags);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_MAGENTA;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff293134;
}

CUSTOM_COMMAND_SIG(fcm_mode_type_insert)
CUSTOM_DOC("") {
    fcm_set_mode_type_insert(app, 0);
}

CUSTOM_COMMAND_SIG(fcm_mode_type_insert_append)
CUSTOM_DOC("") {
    fcm_set_mode_type_insert(app, FCM_TYPE_APPEND);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 line_buffer = get_line_pos_range(app, vb.buffer, cursor.line);
    if (cursor.line != line_buffer.start && cursor.line != line_buffer.end)
        view_set_cursor(app, vb.view, seek_pos(cursor.pos + 1));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_insert_bol)
CUSTOM_DOC("") {
    fcm_set_mode_type_insert(app, 0);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    i64 bol = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    view_set_cursor(app, vb.view, seek_pos(bol));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_insert_eol)
CUSTOM_DOC("") {
    fcm_set_mode_type_insert(app, FCM_TYPE_APPEND);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    i64 eol = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
    view_set_cursor(app, vb.view, seek_pos(eol));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_insert_new_line_above)
CUSTOM_DOC("") {
    fcm_set_mode_type_insert(app, 0);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Scratch_Block scratch(app);
    String_Const_u8 new_line = push_u8_stringf(scratch, "\n");
    
    i64 line_min = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    buffer_replace_range(app, vb.buffer, Ii64(line_min), new_line);
    view_set_cursor(app, vb.view, seek_pos(line_min));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_insert_new_line_below)
CUSTOM_DOC("") {
    fcm_set_mode_type_insert(app, 0);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Scratch_Block scratch(app);
    String_Const_u8 new_line = push_u8_stringf(scratch, "\n");
    
    i64 line_max = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
    buffer_replace_range(app, vb.buffer, Ii64(line_max), new_line);
    view_set_cursor(app, vb.view, seek_pos(line_max+1));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_replace)
CUSTOM_DOC("") {
    fcm_set_mode_type_replace(app, 0);
}

CUSTOM_COMMAND_SIG(fcm_mode_type_replace_char)
CUSTOM_DOC("") {
    fcm_set_mode_type_replace(app, FCM_TYPE_REPLACE_CHAR);
}

CUSTOM_COMMAND_SIG(fcm_mode_type_replace_append)
CUSTOM_DOC("") {
    fcm_set_mode_type_replace(app, FCM_TYPE_APPEND);
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 line_buffer = get_line_pos_range(app, vb.buffer, cursor.line);
    if (cursor.line != line_buffer.start && cursor.line != line_buffer.end)
        view_set_cursor(app, vb.view, seek_pos(cursor.pos + 1));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_replace_bol)
CUSTOM_DOC("") {
    fcm_set_mode_type_replace(app, 0);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    i64 bol = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    view_set_cursor(app, vb.view, seek_pos(bol));
}

CUSTOM_COMMAND_SIG(fcm_mode_type_replace_eol)
CUSTOM_DOC("") {
    fcm_set_mode_type_replace(app, FCM_TYPE_APPEND);
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    i64 eol = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
    view_set_cursor(app, vb.view, seek_pos(eol));
}

CUSTOM_COMMAND_SIG(fcm_toggle_mode_type)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_TYPE_REPLACE_CHAR))
        return;
    
    i64 HasAppend = HasFlag(fcm_flags, FCM_TYPE_APPEND);
    if (HasFlag(fcm_flags, FCM_TYPE_INSERT))
        fcm_mode_type_replace(app);
    else
        fcm_mode_type_insert(app);
    
    if (HasAppend)
        fcm_flags |= FCM_TYPE_APPEND;
}

CUSTOM_COMMAND_SIG(fcm_type_delete_left_word)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_delete_left_boundary(app, func);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_right_word)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_delete_right_boundary(app, func);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_left_name)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_name_scan);
    fcm_delete_left_boundary(app, func);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_right_name)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_name_scan);
    fcm_delete_right_boundary(app, func);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_bol)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    range.end = cursor.pos;
    
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_eol)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = cursor.pos;
    range.end = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
    
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_top_most_scope)
CUSTOM_DOC("") {
    //select_prev_scope_absolute(app);
    //select_surrounding_scope_maximal(app);
}

CUSTOM_COMMAND_SIG(fcm_type_delete_next_scope_after_current)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    fcm_type_delete_next_scope_after_pos(app, vb, cursor_pos);
}

internal void
fcm_delete_left_boundary(Application_Links *app, Boundary_Function_List func) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range = fcm_setup_range_left_boundary(app, vb, func);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_delete_right_boundary(Application_Links *app, Boundary_Function_List func) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range = fcm_setup_range_right_boundary(app, vb, func);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_type_delete_next_scope_after_pos(Application_Links *app, fcm_vb vb, i64 cursor_pos) {
    Find_Nest_Flag flags = FindNest_Scope;
    Range_i64 range = {};
    if (find_nest_side(app, vb.buffer, cursor_pos + 1, flags, Scan_Forward, NestDelim_Open,
                       &range) &&
        find_nest_side(app, vb.buffer, range.end,
                       flags|FindNest_Balanced|FindNest_EndOfToken, Scan_Forward,
                       NestDelim_Close, &range.end)) {
        buffer_replace_range(app, vb.buffer, range, string_u8_empty);
    }
}

#endif // FCM_TYPE_HPP
