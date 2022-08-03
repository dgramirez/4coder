#ifndef FCM_MOVEMENT_HPP
#define FCM_MOVEMENT_HPP

CUSTOM_COMMAND_SIG(fcm_move_up)
CUSTOM_DOC("") {
    move_up(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_visual_update_marks_up_line(app);
}

CUSTOM_COMMAND_SIG(fcm_move_down)
CUSTOM_DOC("") {
    move_down(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_visual_update_marks_down_line(app);
}

CUSTOM_COMMAND_SIG(fcm_move_left)
CUSTOM_DOC("") {
    move_left(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_left_word)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_move_left_boundary(app, func);
    
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_left_underscore)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_move_left_boundary(app, func);
    
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_left_name)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_name_scan);
    fcm_move_left_boundary(app, func);
    
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_left_bol)
CUSTOM_DOC("") {
    seek_beginning_of_line(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_prev_top_most_scope)
CUSTOM_DOC("") {
    select_prev_top_most_scope(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_right)
CUSTOM_DOC("") {
    move_right(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_right_word)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_move_right_boundary(app, func);
    
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_right_underscore)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_word_scan);
    fcm_move_right_boundary(app, func);
    
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_right_name)
CUSTOM_DOC("") {
    Scratch_Block scratch(app);
    Boundary_Function_List func = push_boundary_list(scratch, fcm_boundary_for_name_scan);
    fcm_move_right_boundary(app, func);
    
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_right_eol)
CUSTOM_DOC("") {
    seek_end_of_line(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

CUSTOM_COMMAND_SIG(fcm_move_next_scope_after_current)
CUSTOM_DOC("") {
    select_next_scope_after_current(app);
    if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_LINE))
        fcm_sync_mark_x_to_cursor_x(app);
}

internal void
fcm_move_left_boundary(Application_Links *app, Boundary_Function_List func) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_Visible, &vb);
    
    Range_i64 range = fcm_setup_range_left_boundary(app, vb, func);
    view_set_cursor(app, vb.view, seek_pos(range.first));
}

internal void
fcm_move_right_boundary(Application_Links *app, Boundary_Function_List func) {
    fcm_vb vb;
    fcm_get_view_and_buffer(app, Access_Visible, &vb);
    
    Range_i64 range = fcm_setup_range_right_boundary(app, vb, func);
    view_set_cursor(app, vb.view, seek_pos(range.one_past_last));
}

#endif // FCM_MOVEMENT_HPP