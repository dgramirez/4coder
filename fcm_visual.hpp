#ifndef FCM_VISUAL_HPP
#define FCM_VISUAL_HPP

CUSTOM_COMMAND_SIG(fcm_mode_visual_highlight)
CUSTOM_DOC("") {
    fcm_set_mapid_mode(app, fcm_mapid_visual, FCM_MODE_VISUAL | FCM_VISUAL_HIGHLIGHT);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_BLUE;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xffffaacc;
    
    fcm_marks.count = 0;
    View_ID view = get_active_view(app, 0);
    fcm_marks.pos[fcm_marks.count++] = view_get_cursor_pos(app, view);
}

CUSTOM_COMMAND_SIG(fcm_mode_visual_line)
CUSTOM_DOC("") {
    fcm_set_mapid_mode(app, fcm_mapid_visual, FCM_MODE_VISUAL | FCM_VISUAL_LINE);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_BLUE;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xffffaacc;
    
    fcm_marks.count = 0;
    View_ID view = get_active_view(app, 0);
    fcm_marks.pos[fcm_marks.count++] = view_get_cursor_pos(app, view);
}

CUSTOM_COMMAND_SIG(fcm_mode_visual_marked)
CUSTOM_DOC("") {
    fcm_set_mapid_mode(app, fcm_mapid_visual, FCM_MODE_VISUAL | FCM_VISUAL_MARKED);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_BLUE;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xffffaacc;
    
    fcm_marks.count = 0;
    fcm_add_mark(app);
}

CUSTOM_COMMAND_SIG(fcm_add_mark)
CUSTOM_DOC("") {
    if (!HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
    
    View_ID view = get_active_view(app, 0);
    fcm_marks.pos[fcm_marks.count++] = view_get_cursor_pos(app, view);
    
    fcm_marks_quicksort(0, fcm_marks.count - 1);
}

CUSTOM_COMMAND_SIG(fcm_toggle_mode_visual)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_CAN_TYPE)) {
        fcm_flags = RemFlag(fcm_flags, FCM_VISUAL_CAN_TYPE);
        return;
    }
    
    fcm_marks.count = 0;
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        fcm_mode_visual_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_mode_visual_marked(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        fcm_mode_visual_highlight(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_back_to_normal_mode)
CUSTOM_DOC("") {
    fcm_marks.count = 0;
    fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_start_type)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_MARKED | FCM_VISUAL_LINE))
        fcm_flags = AddFlag(fcm_flags, FCM_VISUAL_CAN_TYPE);
}

CUSTOM_COMMAND_SIG(fcm_visual_copy)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        fcm_visual_copy_highlight(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_copy_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
    
    fcm_visual_back_to_normal_mode(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_cut)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        fcm_visual_cut_highlight(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_cut_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
    
    fcm_visual_back_to_normal_mode(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_delete)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        fcm_visual_delete_highlight(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_delete_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
    
    fcm_visual_back_to_normal_mode(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_paste)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        fcm_visual_paste_highlight(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_paste_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
    
    fcm_visual_back_to_normal_mode(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_type_or_copy)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_CAN_TYPE))
        fcm_write_text_and_auto_indent(app);
    else
        fcm_visual_copy(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_type_or_cut)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_CAN_TYPE))
        fcm_write_text_and_auto_indent(app);
    else
        fcm_visual_cut(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_type_or_delete)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_CAN_TYPE))
        fcm_write_text_and_auto_indent(app);
    else
        fcm_visual_delete(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_type_or_paste)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_CAN_TYPE))
        fcm_write_text_and_auto_indent(app);
    else
        fcm_visual_paste(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_replace_range)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        fcm_visual_replace_highlight(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_replace_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
    
    fcm_visual_back_to_normal_mode(app);
}

CUSTOM_COMMAND_SIG(fcm_visual_move_up)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        return;
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_move_up_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
}

CUSTOM_COMMAND_SIG(fcm_visual_move_down)
CUSTOM_DOC("") {
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT))
        return;
    else if (HasFlag(fcm_flags, FCM_VISUAL_LINE))
        fcm_visual_move_down_line(app);
    else if (HasFlag(fcm_flags, FCM_VISUAL_MARKED))
        return;
}

CUSTOM_COMMAND_SIG(fcm_visual_type_backspace)
CUSTOM_DOC("") {
    if (!HasFlag(fcm_flags, FCM_MODE_VISUAL))
        return;
    
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT)) {
        fcm_visual_delete(app);
        return;
    }
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    for (int i = 0; i < fcm_marks.count; ++i) {
        fcm_marks.pos[i] -= i;
        
        Range_i64 range;
        range.end = fcm_marks.pos[i];
        range.start = range.end - 1;
        
        buffer_replace_range(app, vb.buffer, range, string_u8_empty);
        --fcm_marks.pos[i];
    }
}

CUSTOM_COMMAND_SIG(fcm_visual_type_delete)
CUSTOM_DOC("") {
    if (!HasFlag(fcm_flags, FCM_MODE_VISUAL))
        return;
    
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT)) {
        fcm_visual_delete(app);
        return;
    }
    
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    for (int i = 0; i < fcm_marks.count; ++i) {
        fcm_marks.pos[i] -= i;
        
        Range_i64 range;
        range.start = fcm_marks.pos[i];
        range.end = range.start + 1;
        
        buffer_replace_range(app, vb.buffer, range, string_u8_empty);
    }
}

internal void
fcm_visual_copy_highlight(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = fcm_marks.pos[0];
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos) + 1;
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
}

internal void
fcm_visual_cut_highlight(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = fcm_marks.pos[0];
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos) + 1;
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_visual_delete_highlight(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = fcm_marks.pos[0];
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos) + 1;
    
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_visual_paste_highlight(Application_Links *app) {
    fcm_visual_delete_highlight(app);
    fcm_paste(app);
}

internal void
fcm_visual_replace_highlight(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range = get_view_range(app, vb.view);
    replace_in_range_query_user(app, vb.buffer, range);
}

internal void
fcm_visual_copy_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 mark_start_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[0]);
    i64 mark_end_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[fcm_marks.count - 1]);
    
    i64 min_line = Min(mark_start_line, mark_end_line);
    i64 max_line = Max(mark_start_line, mark_end_line);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, min_line, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, max_line, Side_Max);
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
}

internal void
fcm_visual_cut_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 mark_start_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[0]);
    i64 mark_end_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[fcm_marks.count - 1]);
    
    i64 min_line = Min(mark_start_line, mark_end_line);
    i64 max_line = Max(mark_start_line, mark_end_line);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, min_line, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, max_line, Side_Max);
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_visual_delete_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 mark_start_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[0]);
    i64 mark_end_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[fcm_marks.count - 1]);
    
    i64 min_line = Min(mark_start_line, mark_end_line);
    i64 max_line = Max(mark_start_line, mark_end_line);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, min_line, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, max_line, Side_Max);
    
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_visual_paste_line(Application_Links *app) {
    fcm_visual_delete_line(app);
    fcm_paste(app);
}

internal void
fcm_visual_replace_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 mark_start_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[0]);
    i64 mark_end_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[fcm_marks.count - 1]);
    
    i64 min_line = Min(mark_start_line, mark_end_line);
    i64 max_line = Max(mark_start_line, mark_end_line);
    
    Range_i64 range;
    range.start = get_line_side_pos(app, vb.buffer, min_line, Side_Min);
    range.end = get_line_side_pos(app, vb.buffer, max_line, Side_Max);
    
    replace_in_range_query_user(app, vb.buffer, range);
}

internal void
fcm_visual_move_up_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = view_get_mark_pos(app, vb.view);
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos);
    
    i64 line_num_at_start_pos = get_line_number_from_pos(app, vb.buffer, range.start);
    if (line_num_at_start_pos <= 1)
        return;
    
    i64 line_num_at_end_pos = get_line_number_from_pos(app, vb.buffer, range.end);
    line_num_at_end_pos = get_line_side_pos(app, vb.buffer, line_num_at_end_pos, Side_Max);
    
    Scratch_Block scratch(app);
    Range_i64 line_above = get_line_pos_range(app, vb.buffer, line_num_at_start_pos - 1);
    String_Const_u8 line_to_move = push_buffer_range(app, scratch, vb.buffer, line_above);
    line_to_move = push_u8_stringf(scratch, "\n%.*s", string_expand(line_to_move));
    line_above.end += 1;
    
    History_Group group = history_group_begin(app, vb.buffer);
    buffer_replace_range(app, vb.buffer, Ii64(line_num_at_end_pos), line_to_move);
    buffer_replace_range(app, vb.buffer, line_above, string_u8_empty);
    history_group_end(group);
}

internal void
fcm_visual_move_down_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = view_get_mark_pos(app, vb.view);
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos);
    
    i64 line_num_at_start_pos = get_line_number_from_pos(app, vb.buffer, range.start);
    line_num_at_start_pos = get_line_side_pos(app, vb.buffer, line_num_at_start_pos, Side_Min);
    
    fcm_buffer_type buffer_end;
    fcm_get_end_of_buffer(app, vb, &buffer_end);
    
    i64 line_num_at_end_pos = get_line_number_from_pos(app, vb.buffer, range.end);
    if (line_num_at_end_pos >= buffer_end.line)
        return;
    
    Scratch_Block scratch(app);
    Range_i64 line_below = get_line_pos_range(app, vb.buffer, line_num_at_end_pos + 1);
    String_Const_u8 line_to_move = push_buffer_range(app, scratch, vb.buffer, line_below);
    line_to_move = push_u8_stringf(scratch, "%.*s\n", string_expand(line_to_move));
    line_below.start -= 1;
    
    History_Group group = history_group_begin(app, vb.buffer);
    buffer_replace_range(app, vb.buffer, line_below, string_u8_empty);
    buffer_replace_range(app, vb.buffer, Ii64(line_num_at_start_pos), line_to_move);
    history_group_end(group);
    
    i64 new_start_pos = line_num_at_start_pos + line_to_move.size;
    if (range.start == cursor_pos) {
        view_set_cursor_and_preferred_x(app, vb.view, seek_pos(new_start_pos));
    }
    else if (range.start == mark_pos) {
        view_set_mark(app, vb.view, seek_pos(new_start_pos));
    }
}

internal void
fcm_visual_copy_line_marked(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = view_get_mark_pos(app, vb.view);
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos);
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
}

internal void
fcm_visual_cut_line_marked(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = view_get_mark_pos(app, vb.view);
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos);
    
    clipboard_post_buffer_range(app, 0, vb.buffer, range);
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_visual_delete_line_marked(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    i64 cursor_pos = view_get_cursor_pos(app, vb.view);
    i64 mark_pos = view_get_mark_pos(app, vb.view);
    
    Range_i64 range;
    range.start = Min(cursor_pos, mark_pos);
    range.end = Max(cursor_pos, mark_pos);
    
    buffer_replace_range(app, vb.buffer, range, string_u8_empty);
}

internal void
fcm_visual_paste_line_marked(Application_Links *app) {
    fcm_visual_delete_line_marked(app);
    fcm_paste(app);
}

internal void
fcm_visual_replace_line_marked(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    Range_i64 range = get_view_range(app, vb.view);
    replace_in_range_query_user(app, vb.buffer, range);
}

internal void
fcm_sync_mark_x_to_cursor_x(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_ReadWriteVisible, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    i64 cursor_offset = cursor.pos - get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
    
    for (int i = 0; i < fcm_marks.count; ++i) {
        i64 mark_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[i]);
        i64 mark_min = get_line_side_pos(app, vb.buffer, mark_line, Side_Min);
        i64 mark_max = get_line_side_pos(app, vb.buffer, mark_line, Side_Max);
        
        if (mark_min + cursor_offset > mark_max)
            fcm_marks.pos[i] = mark_max;
        else
            fcm_marks.pos[i] = mark_min + cursor_offset;
    }
}


// TODO(tiny): Whenever I get a chance, Fix the tab issue
internal void
fcm_visual_update_marks_up_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, 0, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    i64 first_mark_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[0]);
    i64 line_delta = cursor.line - first_mark_line;
    if (line_delta >= 0)
        --fcm_marks.count;
    else
        fcm_marks.pos[fcm_marks.count++] = cursor.pos;
    
    fcm_sync_mark_x_to_cursor_x(app);
}

// TODO(tiny): Whenever I get a chance, Fix the tab issue
internal void
fcm_visual_update_marks_down_line(Application_Links *app) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, 0, &vb);
    
    fcm_buffer_type cursor;
    fcm_get_cursor_info(app, vb, &cursor);
    
    i64 first_mark_line = get_line_number_from_pos(app, vb.buffer, fcm_marks.pos[0]);
    i64 line_delta = cursor.line - first_mark_line;
    
    if (line_delta <= 0)
        --fcm_marks.count;
    else
        fcm_marks.pos[fcm_marks.count++] = cursor.pos;
    
    fcm_sync_mark_x_to_cursor_x(app);
}

function i64
fcm_marks_quicksort_partition(i64 index_low, i64 index_high) {
    i64 high_value = fcm_marks.pos[index_high];
    i64 i = index_low - 1;
    
    for (i64 j = index_low; j <= index_high - 1; ++j) {
        if (fcm_marks.pos[j] <= high_value) {
            i++;
            if (fcm_marks.pos[i] != fcm_marks.pos[j]) {
                fcm_marks.pos[i] ^= fcm_marks.pos[j];
                fcm_marks.pos[j] ^= fcm_marks.pos[i];
                fcm_marks.pos[i] ^= fcm_marks.pos[j];
            }
        }
    }
    
    i++;
    if (fcm_marks.pos[i] != fcm_marks.pos[index_high]) {
        fcm_marks.pos[i] ^= fcm_marks.pos[index_high];
        fcm_marks.pos[index_high] ^= fcm_marks.pos[i];
        fcm_marks.pos[i] ^= fcm_marks.pos[index_high];
    }
    
    return i;
}

function void
fcm_marks_quicksort(i64 index_low, i64 index_high) {
    if (index_low < index_high) {
        i64 partition = fcm_marks_quicksort_partition(index_low, index_high);
        fcm_marks_quicksort(index_low, partition - 1);
        fcm_marks_quicksort(partition + 1, index_high);
    }
}

#endif