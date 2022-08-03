#ifndef FCM_BUFFER_HPP
#define FCM_BUFFER_HPP

CUSTOM_COMMAND_SIG(fcm_mode_buffer_copy)
CUSTOM_DOC("") {
    fcm_set_mapid_mode(app, fcm_mapid_buffer, FCM_MODE_BUFFER | FCM_BUFFER_COPY);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_YELLOW;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xffffaacc;
}

CUSTOM_COMMAND_SIG(fcm_mode_buffer_cut)
CUSTOM_DOC("") {
    fcm_set_mapid_mode(app, fcm_mapid_buffer, FCM_MODE_BUFFER | FCM_BUFFER_CUT);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_ORANGE;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff0000ff;
}

CUSTOM_COMMAND_SIG(fcm_mode_buffer_delete)
CUSTOM_DOC("") {
    fcm_set_mapid_mode(app, fcm_mapid_buffer, FCM_MODE_BUFFER | FCM_BUFFER_DELETE);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_RED;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xffffaacc;
}

CUSTOM_COMMAND_SIG(fcm_mode_buffer_toggle)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_BUFFER_COPY))
        fcm_mode_buffer_cut(app);
    else if (HasFlag(fcm_flags, FCM_BUFFER_CUT))
        fcm_mode_buffer_delete(app);
    else
        fcm_mode_buffer_copy(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_left_word)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_buffer_do_left_boundary(app, func, vb);
    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_right_word)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_buffer_do_right_boundary(app, func, vb);    
    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_left_name)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_name_scan);
    fcm_buffer_do_left_boundary(app, func, vb);    
    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_right_name)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_name_scan);
    fcm_buffer_do_right_boundary(app, func, vb);    
    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_bol)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    range.end = cursor.pos + 1;
    
    fcm_buffer_do_action(app, vb.buffer, range);    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_eol)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = cursor.pos;
    range.end = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
    
    fcm_buffer_do_action(app, vb.buffer, range);    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_current_line_and_above)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, cursor.line - 1, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max) + 1;
    
    fcm_buffer_do_action(app, vb.buffer, range);    
    fcm_mode_normal(app);
}


CUSTOM_COMMAND_SIG(fcm_buffer_do_current_line_and_below)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, cursor.line + 1, Side_Max) + 1;
    
    fcm_buffer_do_action(app, vb.buffer, range);    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_all_lines_on_and_above)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Range_i64 range;
    range.start = 0;
    range.end = get_line_side_pos(app, vb.buffer, cursor.line + 1, Side_Max) + 1;
    
    fcm_buffer_do_action(app, vb.buffer, range);    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_do_all_lines_on_and_below)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    fcm_buffer_type buffer_end;
    fcm_get_end_of_buffer(app, vb, &buffer_end);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    range.end = buffer_end.pos;
    
    fcm_buffer_do_action(app, vb.buffer, range);    
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_copy_current_line)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_BUFFER_CUT | FCM_BUFFER_DELETE))
        fcm_buffer_cut_current_line(app);
    else
        fcm_copy_line(app);
    
    fcm_mode_normal(app);
}


CUSTOM_COMMAND_SIG(fcm_buffer_cut_current_line)
CUSTOM_DOC("") {
    fcm_cut_line(app);
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_buffer_delete_current_line)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_BUFFER_COPY | FCM_BUFFER_CUT))
        fcm_buffer_cut_current_line(app);
    else
        fcm_delete_line(app);
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_copy_line)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Scratch_Block scratch(app);
    String_Const_u8 s = push_buffer_line(app, scratch, vb.buffer, cursor.line);
    s = push_u8_stringf(scratch, "%.*s\n", string_expand(s));
    
    clipboard_post(0, s);
}

CUSTOM_COMMAND_SIG(fcm_cut_line)
CUSTOM_DOC("") {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    Scratch_Block scratch(app);
    String_Const_u8 s = push_buffer_line(app, scratch, vb.buffer, cursor.line);
    s = push_u8_stringf(scratch, "%.*s\n", string_expand(s));
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, cursor.line, Side_Max);
    
    i64 buffer_size = buffer_get_size(app, vb.buffer);
    if (buffer_size != range.end)
        range.end += 1;
    
    History_Group group = history_group_begin(app, vb.buffer);
    clipboard_post(0, s);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
    history_group_end(group);
}

CUSTOM_COMMAND_SIG(fcm_delete_line)
CUSTOM_DOC("") {
    delete_line(app);
}

internal void
fcm_buffer_do_left_boundary(Application_Links *app, Boundary_Function_List func, fcm_vb data) {
    Range_i64 range = fcm_setup_range_left_boundary(app, data, func);
    fcm_buffer_do_action(app, data.buffer, range);
}

internal void
fcm_buffer_do_right_boundary(Application_Links *app, Boundary_Function_List func, fcm_vb data) {
    Range_i64 range = fcm_setup_range_right_boundary(app, data, func);
    fcm_buffer_do_action(app, data.buffer, range);
}

internal void
fcm_buffer_do_action(Application_Links *app, Buffer_ID buffer, Range_i64 range) {
    History_Group group = history_group_begin(app, buffer);
    
    if (HasFlag(fcm_flags, FCM_BUFFER_COPY | FCM_BUFFER_CUT))
        clipboard_post_buffer_range(app, 0, buffer, range);
    
    if (HasFlag(fcm_flags, FCM_BUFFER_DELETE | FCM_BUFFER_CUT))
        buffer_replace_range(app, buffer, range, string_u8_empty);
    
    history_group_end(group);
}

#endif // FCM_BUFFER_HPP
