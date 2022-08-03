#ifndef FCM_NORMAL_HPP
#define FCM_NORMAL_HPP

CUSTOM_COMMAND_SIG(fcm_mode_normal)
CUSTOM_DOC("Sets the modal state to \"Normal\" mode") {
    if (HasFlag(fcm_flags, FCM_TYPE_APPEND)) {
        fcm_vb vb;
        fcm_get_view_and_buffer(app, 0, &vb);
        
        fcm_buffer_type cursor;
        fcm_get_cursor_info(app, vb, &cursor);
        
        i64 line_start = get_line_side_pos(app, vb.buffer, cursor.line, Side_Min);
        if (line_start != cursor.pos)
            cursor.pos -= 1;
        
        view_set_cursor(app, vb.view, seek_pos(cursor.pos));
    }
    
    fcm_set_mapid_mode(app, fcm_mapid_normal, FCM_MODE_NORMAL);
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = FCM_COLOR_GREEN;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xffffaacc;
}

#endif // FCM_NORMAL_HPP
