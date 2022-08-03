#ifndef FCM_FCODER_MODIFICATION_HPP
#define FCM_FCODER_MODIFICATION_HPP

CUSTOM_COMMAND_SIG(fcm_list_substring_locations_other_panel)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    list_all_substring_locations_case_insensitive(app);
}

CUSTOM_COMMAND_SIG(fcm_select_location_same_panel)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    if_read_only_goto_position_same_panel(app);
}

CUSTOM_COMMAND_SIG(fcm_interactive_open_or_new)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    interactive_open_or_new(app);
}

CUSTOM_COMMAND_SIG(fcm_command_lister)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    command_lister(app);
}

CUSTOM_COMMAND_SIG(fcm_project_command_lister)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    project_command_lister(app);
}

CUSTOM_COMMAND_SIG(fcm_change_active_panel)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    change_active_panel(app);
}

CUSTOM_COMMAND_SIG(fcm_change_active_panel_backwards)
CUSTOM_DOC("") {
    fcm_mode_normal(app);
    change_active_panel_backwards(app);
}

CUSTOM_COMMAND_SIG(fcm_write_text_and_auto_indent)
CUSTOM_DOC("") {
    b32 passes_check = HasFlag(fcm_flags, FCM_MODE_TYPE) || HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_CAN_TYPE);
    if (!passes_check)
        return;
    
    ProfileScope(app, "write and auto indent");
    User_Input in = get_current_input(app);
    String_Const_u8 insert = to_writable(&in);
    if (insert.str != 0 && insert.size > 0){
        b32 do_auto_indent = false;
        for (u64 i = 0; !do_auto_indent && i < insert.size; i += 1){
            switch (insert.str[i]){
                case ';': case ':':
                case '{': case '}':
                case '(': case ')':
                case '[': case ']':
                case '#':case '\n': case '\t':
                {
                    do_auto_indent = true;
                }break;
            }
        }
        if (do_auto_indent){
            View_ID view = get_active_view(app, Access_ReadWriteVisible);
            Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
            
            Range_i64 pos = {};
            if (view_has_highlighted_range(app, view)){
                pos = get_view_range(app, view);
            }
            else{
                pos.min = pos.max = view_get_cursor_pos(app, view);
            }
            
            fcm_write_text_input(app);
            
            i64 end_pos = view_get_cursor_pos(app, view);
            pos.min = Min(pos.min, end_pos);
            pos.max = Max(pos.max, end_pos);
            
            auto_indent_buffer(app, buffer, pos, 0);
            move_past_lead_whitespace(app, view, buffer);
        }
        else{
            fcm_write_text_input(app);
        }
    }
    
    if (HasFlag(fcm_flags, FCM_TYPE_REPLACE_CHAR))
        fcm_mode_normal(app);
}

CUSTOM_COMMAND_SIG(fcm_startup)
CUSTOM_DOC("Default command for responding to a startup event") {
    ProfileScope(app, "default startup");
    User_Input input = get_current_input(app);
    if (match_core_code(&input, CoreCode_Startup)){
        String_Const_u8_Array file_names = input.event.core.file_names;
        load_themes_default_folder(app);
        
        //Notes(tiny): This is a really weird setup...
        Face_Description description = get_face_description(app, 0);
        
        fcm_4coder_initialize(app, file_names,
                              description.parameters.pt_size,
                              description.parameters.hinting);
        default_4coder_side_by_side_panels(app, file_names);
        load_project(app);
        toggle_fullscreen(app);
    }
    
    {
        def_audio_init();
    }
    
    {
        def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
        clear_all_layouts(app);
    }
}

BUFFER_HOOK_SIG(fcm_begin_buffer) {
    ProfileScope(app, "begin buffer");
    
    Scratch_Block scratch(app);
    
    b32 treat_as_code = false;
    String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer_id);
    if (file_name.size > 0){
        String_Const_u8 treat_as_code_string = def_get_config_string(scratch, vars_save_string_lit("treat_as_code"));
        String_Const_u8_Array extensions = parse_extension_line_to_extension_list(app, scratch, treat_as_code_string);
        String_Const_u8 ext = string_file_extension(file_name);
        for (i32 i = 0; i < extensions.count; ++i){
            if (string_match(ext, extensions.strings[i])){
                
                if (string_match(ext, string_u8_litexpr("cpp")) ||
                    string_match(ext, string_u8_litexpr("h")) ||
                    string_match(ext, string_u8_litexpr("c")) ||
                    string_match(ext, string_u8_litexpr("hpp")) ||
                    string_match(ext, string_u8_litexpr("cc")) ||
                    string_match(ext, string_u8_litexpr("cs"))){
                    treat_as_code = true;
                }
                
#if 0
                treat_as_code = true;
                
                if (string_match(ext, string_u8_litexpr("cs"))){
                    if (parse_context_language_cs == 0){
                        init_language_cs(app);
                    }
                    parse_context_id = parse_context_language_cs;
                }
                
                if (string_match(ext, string_u8_litexpr("java"))){
                    if (parse_context_language_java == 0){
                        init_language_java(app);
                    }
                    parse_context_id = parse_context_language_java;
                }
                
                if (string_match(ext, string_u8_litexpr("rs"))){
                    if (parse_context_language_rust == 0){
                        init_language_rust(app);
                    }
                    parse_context_id = parse_context_language_rust;
                }
                
                if (string_match(ext, string_u8_litexpr("cpp")) ||
                    string_match(ext, string_u8_litexpr("h")) ||
                    string_match(ext, string_u8_litexpr("c")) ||
                    string_match(ext, string_u8_litexpr("cs")) ||
                    string_match(ext, string_u8_litexpr("hpp")) ||
                    string_match(ext, string_u8_litexpr("cc"))){
                    if (parse_context_language_cpp == 0){
                        init_language_cpp(app);
                    }
                    parse_context_id = parse_context_language_cpp;
                }
                
                // TODO(NAME): Real GLSL highlighting
                if (string_match(ext, string_u8_litexpr("glsl"))){
                    if (parse_context_language_cpp == 0){
                        init_language_cpp(app);
                    }
                    parse_context_id = parse_context_language_cpp;
                }
                
                // TODO(NAME): Real Objective-C highlighting
                if (string_match(ext, string_u8_litexpr("m"))){
                    if (parse_context_language_cpp == 0){
                        init_language_cpp(app);
                    }
                    parse_context_id = parse_context_language_cpp;
                }
#endif
                
                break;
            }
        }
    }
    
    // NOTE(tiny): Replaced the code_map_id and file_map_id with fcm_mapid_normal
    Command_Map_ID map_id = fcm_mapid_normal;
    Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
    Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
    *map_id_ptr = map_id;
    
    Line_Ending_Kind setting = guess_line_ending_kind_from_buffer(app, buffer_id);
    Line_Ending_Kind *eol_setting = scope_attachment(app, scope, buffer_eol_setting, Line_Ending_Kind);
    *eol_setting = setting;
    
    // NOTE(allen): Decide buffer settings
    b32 wrap_lines = true;
    b32 use_lexer = false;
    if (treat_as_code){
        wrap_lines = def_get_config_b32(vars_save_string_lit("enable_code_wrapping"));
        use_lexer = true;
    }
    
    String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer_id);
    if (buffer_name.size > 0 && buffer_name.str[0] == '*' && buffer_name.str[buffer_name.size - 1] == '*'){
        wrap_lines = def_get_config_b32(vars_save_string_lit("enable_output_wrapping"));
    }
    
    if (use_lexer){
        ProfileBlock(app, "begin buffer kick off lexer");
        Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);
        *lex_task_ptr = async_task_no_dep(&global_async_system, do_full_lex_async, make_data_struct(&buffer_id));
    }
    
    {
        b32 *wrap_lines_ptr = scope_attachment(app, scope, buffer_wrap_lines, b32);
        *wrap_lines_ptr = wrap_lines;
    }
    
    if (use_lexer){
        buffer_set_layout(app, buffer_id, layout_virt_indent_index_generic);
    }
    else{
        if (treat_as_code){
            buffer_set_layout(app, buffer_id, layout_virt_indent_literal_generic);
        }
        else{
            buffer_set_layout(app, buffer_id, layout_generic);
        }
    }
    
    // no meaning for return
    return(0);
}

CUSTOM_COMMAND_SIG(fcm_replace_in_all_buffers)
CUSTOM_DOC("Queries the user for a needle and string. Replaces all occurences of needle with string in all editable buffers.")
{
    global_history_edit_group_begin(app);
    
    Scratch_Block scratch(app);
    Query_Bar_Group group(app);
    String_Pair pair = query_user_replace_pair(app, scratch);
    
    if (pair.valid) {
        for (Buffer_ID buffer = get_buffer_next(app, 0, Access_ReadWriteVisible);
             buffer != 0;
             buffer = get_buffer_next(app, buffer, Access_ReadWriteVisible)){
            Range_i64 range = buffer_range(app, buffer);
            replace_in_range(app, buffer, range, pair.a, pair.b);
        }
    }
    
    global_history_edit_group_end(app);
}

internal void
fcm_set_all_default_hooks(Application_Links *app) {
    set_custom_hook(app, HookID_BufferViewerUpdate, default_view_adjust);
    
    set_custom_hook(app, HookID_ViewEventHandler, default_view_input_handler);
    set_custom_hook(app, HookID_Tick, default_tick);
    set_custom_hook(app, HookID_RenderCaller, fcm_render_caller);
    set_custom_hook(app, HookID_WholeScreenRenderCaller, default_whole_screen_render_caller);
    
    set_custom_hook(app, HookID_DeltaRule, fixed_time_cubic_delta);
    set_custom_hook_memory_size(app, HookID_DeltaRule,
                                delta_ctx_size(fixed_time_cubic_delta_memory_size));
    
    set_custom_hook(app, HookID_BufferNameResolver, default_buffer_name_resolution);
    
    set_custom_hook(app, HookID_BeginBuffer, fcm_begin_buffer);
    set_custom_hook(app, HookID_EndBuffer, end_buffer_close_jump_list);
    set_custom_hook(app, HookID_NewFile, default_new_file);
    set_custom_hook(app, HookID_SaveFile, default_file_save);
    set_custom_hook(app, HookID_BufferEditRange, default_buffer_edit_range);
    set_custom_hook(app, HookID_BufferRegion, default_buffer_region);
    set_custom_hook(app, HookID_ViewChangeBuffer, default_view_change_buffer);
    
    set_custom_hook(app, HookID_Layout, layout_unwrapped);
    //set_custom_hook(app, HookID_Layout, layout_wrap_anywhere);
    //set_custom_hook(app, HookID_Layout, layout_wrap_whitespace);
    //set_custom_hook(app, HookID_Layout, layout_virt_indent_unwrapped);
    //set_custom_hook(app, HookID_Layout, layout_unwrapped_small_blank_lines);
}

internal void
fcm_4coder_initialize(Application_Links *app, String_Const_u8_Array file_names, i32 override_font_size, b32 override_hinting) {
#define M \
"Welcome to " VERSION "\n" \
"If you're new to 4coder there is a built in tutorial\n" \
"Use the key combination [ X Alt ] (on mac [ X Control ])\n" \
"Type in 'hms_demo_tutorial' and press enter\n" \
"\n" \
"Direct bug reports and feature requests to https://github.com/4coder-editor/4coder/issues\n" \
"\n" \
"Other questions and discussion can be directed to editor@4coder.net or 4coder.handmade.network\n" \
"\n" \
"The change log can be found in CHANGES.txt\n" \
"\n"
    print_message(app, string_u8_litexpr(M));
#undef M
    
    Scratch_Block scratch(app);
    
    load_config_and_apply(app, &global_config_arena, override_font_size, override_hinting);
    
    String_Const_u8 bindings_file_name = string_u8_litexpr("bindings.4coder");
    String_Const_u8 mapping = def_get_config_string(scratch, vars_save_string_lit("mapping"));
    
    if (string_match(mapping, string_u8_litexpr("mac-default"))){
        bindings_file_name = string_u8_litexpr("mac-bindings.4coder");
    }
    else if (OS_MAC && string_match(mapping, string_u8_litexpr("choose"))){
        bindings_file_name = string_u8_litexpr("mac-bindings.4coder");
    }
    
    // TODO(tiny): Figure out why below crashes x.x
    //             Or perhaps, remove it and not think about it lol.
    
    /* TODO(allen): cleanup
        String_ID global_map_id = vars_save_string_lit("keys_global");
        String_ID file_map_id = vars_save_string_lit("keys_file");
        String_ID code_map_id = vars_save_string_lit("keys_code");
        
        if (dynamic_binding_load_from_file(app, &framework_mapping, bindings_file_name)){
            setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
        }
        else{
            setup_built_in_mapping(app, mapping, &framework_mapping, global_map_id, file_map_id, code_map_id);
        }
    */
    
    // open command line files
    String_Const_u8 hot_directory = push_hot_directory(app, scratch);
    for (i32 i = 0; i < file_names.count; i += 1){
        Temp_Memory_Block temp(scratch);
        String_Const_u8 input_name = file_names.vals[i];
        String_Const_u8 full_name = push_u8_stringf(scratch, "%.*s/%.*s",
                                                    string_expand(hot_directory),
                                                    string_expand(input_name));
        Buffer_ID new_buffer = create_buffer(app, full_name, BufferCreate_NeverNew|BufferCreate_MustAttachToFile);
        if (new_buffer == 0){
            create_buffer(app, input_name, 0);
        }
    }
    
    fcm_set_mapid_mode(app, fcm_mapid_normal, FCM_MODE_NORMAL);
}

internal void
fcm_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id) {
    ProfileScope(app, "default render caller");
    View_ID active_view = get_active_view(app, Access_Always);
    b32 is_active_view = (active_view == view_id);
    
    Rect_f32 region = draw_background_and_margin(app, view_id, is_active_view);
    Rect_f32 prev_clip = draw_set_clip(app, region);
    
    Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
    Face_ID face_id = get_face_id(app, buffer);
    Face_Metrics face_metrics = get_face_metrics(app, face_id);
    f32 line_height = face_metrics.line_height;
    f32 digit_advance = face_metrics.decimal_digit_advance;
    
    // NOTE(allen): file bar
    b64 showing_file_bar = false;
    if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar){
        Rect_f32_Pair pair = layout_file_bar_on_top(region, line_height);
        draw_file_bar(app, view_id, buffer, face_id, pair.min);
        region = pair.max;
    }
    
    Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);
    
    Buffer_Point_Delta_Result delta = delta_apply(app, view_id,
                                                  frame_info.animation_dt, scroll);
    if (!block_match_struct(&scroll.position, &delta.point)){
        block_copy_struct(&scroll.position, &delta.point);
        view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
    }
    if (delta.still_animating){
        animate_in_n_milliseconds(app, 0);
    }
    
    // NOTE(allen): query bars
    region = default_draw_query_bars(app, region, view_id, face_id);
    
    // NOTE(allen): FPS hud
    if (show_fps_hud){
        Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
        draw_fps_hud(app, frame_info, face_id, pair.max);
        region = pair.min;
        animate_in_n_milliseconds(app, 1000);
    }
    
    // NOTE(allen): layout line numbers
    b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
    Rect_f32 line_number_rect = {};
    if (show_line_number_margins){
        Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
        line_number_rect = pair.min;
        region = pair.max;
    }
    
    // NOTE(allen): begin buffer render
    Buffer_Point buffer_point = scroll.position;
    Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);
    
    // NOTE(allen): draw line numbers
    if (show_line_number_margins){
        draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
    }
    
    // NOTE(allen): draw the buffer
    fcm_render_buffer(app, view_id, face_id, buffer, text_layout_id, region);
    
    text_layout_free(app, text_layout_id);
    draw_set_clip(app, prev_clip);
}

function void
fcm_render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id,
                  Buffer_ID buffer, Text_Layout_ID text_layout_id,
                  Rect_f32 rect) {
    ProfileScope(app, "render buffer");
    
    View_ID active_view = get_active_view(app, Access_Always);
    b32 is_active_view = (active_view == view_id);
    Rect_f32 prev_clip = draw_set_clip(app, rect);
    
    Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
    
    // NOTE(allen): Cursor shape
    Face_Metrics metrics = get_face_metrics(app, face_id);
    u64 cursor_roundness_100 = def_get_config_u64(app, vars_save_string_lit("cursor_roundness"));
    f32 cursor_roundness = metrics.normal_advance*cursor_roundness_100*0.01f;
    f32 mark_thickness = (f32)def_get_config_u64(app, vars_save_string_lit("mark_thickness"));
    
    // NOTE(allen): Token colorizing
    Token_Array token_array = get_token_array_from_buffer(app, buffer);
    if (token_array.tokens != 0){
        draw_cpp_token_colors(app, text_layout_id, &token_array);
        
        // NOTE(allen): Scan for TODOs and NOTEs
        b32 use_comment_keyword = def_get_config_b32(vars_save_string_lit("use_comment_keyword"));
        if (use_comment_keyword){
            Comment_Highlight_Pair pairs[] = {
                {string_u8_litexpr("NOTE"), finalize_color(defcolor_comment_pop, 0)},
                {string_u8_litexpr("TODO"), finalize_color(defcolor_comment_pop, 1)},
            };
            draw_comment_highlights(app, buffer, text_layout_id, &token_array, pairs, ArrayCount(pairs));
        }
        
#if 0
        // TODO(allen): Put in 4coder_draw.cpp
        // NOTE(allen): Color functions
        
        Scratch_Block scratch(app);
        ARGB_Color argb = 0xFFFF00FF;
        
        Token_Iterator_Array it = token_iterator_pos(0, &token_array, visible_range.first);
        for (;;){
            if (!token_it_inc_non_whitespace(&it)){
                break;
            }
            Token *token = token_it_read(&it);
            String_Const_u8 lexeme = push_token_lexeme(app, scratch, buffer, token);
            Code_Index_Note *note = code_index_note_from_string(lexeme);
            if (note != 0 && note->note_kind == CodeIndexNote_Function){
                paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), argb);
            }
        }
#endif
    }
    else{
        paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
    }
    
    i64 cursor_pos = view_correct_cursor(app, view_id);
    view_correct_mark(app, view_id);
    
    // NOTE(allen): Scope highlight
    b32 use_scope_highlight = def_get_config_b32(vars_save_string_lit("use_scope_highlight"));
    if (use_scope_highlight){
        Color_Array colors = finalize_color_array(defcolor_back_cycle);
        draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
    }
    
    b32 use_error_highlight = def_get_config_b32(vars_save_string_lit("use_error_highlight"));
    b32 use_jump_highlight = def_get_config_b32(vars_save_string_lit("use_jump_highlight"));
    if (use_error_highlight || use_jump_highlight){
        // NOTE(allen): Error highlight
        String_Const_u8 name = string_u8_litexpr("*compilation*");
        Buffer_ID compilation_buffer = get_buffer_by_name(app, name, Access_Always);
        if (use_error_highlight){
            draw_jump_highlights(app, buffer, text_layout_id, compilation_buffer,
                                 fcolor_id(defcolor_highlight_junk));
        }
        
        // NOTE(allen): Search highlight
        if (use_jump_highlight){
            Buffer_ID jump_buffer = get_locked_jump_buffer(app);
            if (jump_buffer != compilation_buffer){
                draw_jump_highlights(app, buffer, text_layout_id, jump_buffer,
                                     fcolor_id(defcolor_highlight_white));
            }
        }
    }
    
    // NOTE(allen): Color parens
    b32 use_paren_helper = def_get_config_b32(vars_save_string_lit("use_paren_helper"));
    if (use_paren_helper){
        Color_Array colors = finalize_color_array(defcolor_text_cycle);
        draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
    }
    
    // NOTE(allen): Line highlight
    b32 highlight_line_at_cursor = def_get_config_b32(vars_save_string_lit("highlight_line_at_cursor"));
    if (highlight_line_at_cursor && is_active_view){
        i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
        draw_line_highlight(app, text_layout_id, line_number, fcolor_id(defcolor_highlight_cursor_line));
    }
    
    // NOTE(allen): Whitespace highlight
    b64 show_whitespace = false;
    view_get_setting(app, view_id, ViewSetting_ShowWhitespace, &show_whitespace);
    if (show_whitespace){
        if (token_array.tokens == 0){
            draw_whitespace_highlight(app, buffer, text_layout_id, cursor_roundness);
        }
        else{
            draw_whitespace_highlight(app, text_layout_id, &token_array, cursor_roundness);
        }
    }
    
    // NOTE(allen): Cursor
    if (HasFlag(fcm_flags, FCM_VISUAL_HIGHLIGHT)) {
        fcm_draw_i_bar_with_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
    }
    if (HasFlag(fcm_flags, FCM_MODE_TYPE | FCM_VISUAL_CAN_TYPE))
        fcm_draw_i_bar(app, view_id, text_layout_id);
    else {
        fcm_draw_original_4coder_style_cursor_mark_highlight(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);
    }
    
    if (HasFlag(fcm_flags, FCM_MODE_VISUAL)) {
        fcm_draw_original_4coder_style_mark(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);
    }
    
    // NOTE(allen): Fade ranges
    paint_fade_ranges(app, text_layout_id, buffer);
    
    // NOTE(allen): put the actual text on the actual screen
    draw_text_layout_default(app, text_layout_id);
    
    draw_set_clip(app, prev_clip);
}

function void
fcm_draw_original_4coder_style_cursor_mark_highlight(Application_Links *app, View_ID view_id, b32 is_active_view,
                                                     Buffer_ID buffer, Text_Layout_ID text_layout_id,
                                                     f32 roundness, f32 outline_thickness) {
    b32 has_highlight_range = draw_highlight_range(app, view_id, buffer, text_layout_id, roundness);
    if (!has_highlight_range){
        i32 cursor_sub_id = default_cursor_sub_id();
        
        i64 cursor_pos = view_get_cursor_pos(app, view_id);
        if (is_active_view){
            draw_character_block(app, text_layout_id, cursor_pos, roundness,
                                 fcolor_id(defcolor_cursor, cursor_sub_id));
            paint_text_color_pos(app, text_layout_id, cursor_pos,
                                 fcolor_id(defcolor_at_cursor));
            
            for (int i = 0; i < fcm_marks.count; ++i) {
                draw_character_wire_frame(app, text_layout_id, fcm_marks.pos[i],
                                          roundness, outline_thickness,
                                          fcolor_id(defcolor_mark));
            }
        }
        else{
            for (int i = 0; i < fcm_marks.count; ++i) {
                draw_character_wire_frame(app, text_layout_id, fcm_marks.pos[i],
                                          roundness, outline_thickness,
                                          fcolor_id(defcolor_mark));
            }
            
            draw_character_wire_frame(app, text_layout_id, cursor_pos,
                                      roundness, outline_thickness,
                                      fcolor_id(defcolor_cursor, cursor_sub_id));
        }
    }
}

function void
fcm_draw_original_4coder_style_mark(Application_Links *app, View_ID view_id, b32 is_active_view,
                                    Buffer_ID buffer, Text_Layout_ID text_layout_id,
                                    f32 roundness, f32 outline_thickness) {
    for (int i = 0; i < fcm_marks.count; ++i) {
        draw_character_wire_frame(app, text_layout_id, fcm_marks.pos[i],
                                  roundness, outline_thickness,
                                  fcolor_id(defcolor_mark));
    }
}

internal void
fcm_write_text_input(Application_Links *app) {
    User_Input in = get_current_input(app);
    String_Const_u8 insert = to_writable(&in);
    fcm_write_text(app, insert);
    
    if (HasFlag(fcm_flags, FCM_TYPE_REPLACE_CHAR))
        fcm_mode_normal(app);
}

internal void
fcm_write_text(Application_Links *app, String_Const_u8 insert) {
    ProfileScope(app, "write character");
    if (insert.str != 0 && insert.size > 0){
        View_ID view = get_active_view(app, Access_ReadWriteVisible);
        if_view_has_highlighted_range_delete_range(app, view);
        
        i64 pos = view_get_cursor_pos(app, view);
        pos = view_get_character_legal_pos_from_pos(app, view, pos);
        
        Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
        
        // NOTE(allen): consecutive inserts merge logic
        History_Record_Index first_index = buffer_history_get_current_state_index(app, buffer);
        b32 do_merge = false;
        if (insert.str[0] != '\n'){
            Record_Info record = get_single_record(app, buffer, first_index);
            if (record.error == RecordError_NoError && record.kind == RecordKind_Single){
                String_Const_u8 string = record.single_string_forward;
                i32 last_end = (i32)(record.single_first + string.size);
                if (last_end == pos && string.size > 0){
                    char c = string.str[string.size - 1];
                    if (c != '\n'){
                        if (character_is_whitespace(insert.str[0]) &&
                            character_is_whitespace(c)){
                            do_merge = true;
                        }
                        else if (character_is_alpha_numeric(insert.str[0]) && character_is_alpha_numeric(c)){
                            do_merge = true;
                        }
                    }
                }
            }
        }
        
        // NOTE(allen): perform the edit
        b32 edit_success = 0;
        if (HasAllFlag(fcm_flags, FCM_MODE_VISUAL | FCM_VISUAL_CAN_TYPE)) {
            History_Group group = history_group_begin(app, buffer);
            for (int i = 0; i < fcm_marks.count; ++i) {
                Range_i64 range = Ii64(fcm_marks.pos[i] + i);
                if (HasFlag(fcm_flags, FCM_TYPE_REPLACE))
                    range.end += 1;
                
                edit_success = buffer_replace_range(app, buffer, range, insert);
                fcm_marks.pos[i] += i + 1;
            }
            history_group_end(group);
            
            // NOTE(allen): finish merging records if necessary
            if (do_merge) {
                History_Record_Index last_index = buffer_history_get_current_state_index(app, buffer);
                buffer_history_merge_record_range(app, buffer, first_index, last_index, RecordMergeFlag_StateInRange_MoveStateForward);
            }
            
            // NOTE(allen): finish updating the cursor
            if (HasFlag(fcm_flags, FCM_VISUAL_LINE)) {
                if (edit_success){
                    view_set_cursor_and_preferred_x(app, view, seek_pos(fcm_marks.pos[fcm_marks.count - 1]));
                }
                fcm_sync_mark_x_to_cursor_x(app);
            }
        }
        else {
            Range_i64 range = Ii64(pos);
            if (HasFlag(fcm_flags, FCM_TYPE_REPLACE))
                range.end += 1;
            
            edit_success = buffer_replace_range(app, buffer, range, insert);
            
            // NOTE(allen): finish merging records if necessary
            if (do_merge) {
                History_Record_Index last_index = buffer_history_get_current_state_index(app, buffer);
                buffer_history_merge_record_range(app, buffer, first_index, last_index, RecordMergeFlag_StateInRange_MoveStateForward);
            }
            
            // NOTE(allen): finish updating the cursor
            if (edit_success){
                view_set_cursor_and_preferred_x(app, view, seek_pos(pos + insert.size));
            }
        }
    }
}

function void
fcm_draw_i_bar(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id) {
    i32 cursor_sub_id = default_cursor_sub_id();
    i64 cursor_pos = view_get_cursor_pos(app, view_id);
    draw_character_i_bar(app, text_layout_id, cursor_pos, fcolor_id(defcolor_cursor, cursor_sub_id));
}

function void
fcm_draw_i_bar_with_highlight(Application_Links *app, View_ID view_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, f32 roundness) {
    b32 has_highlight_range = draw_highlight_range(app, view_id, buffer, text_layout_id, roundness);
    if (!has_highlight_range) {
        i32 cursor_sub_id = default_cursor_sub_id();
        i64 cursor_pos = view_get_cursor_pos(app, view_id);
        i64 mark_pos = fcm_marks.pos[0];
        if (cursor_pos != mark_pos){
            i64 start_pos = Min(cursor_pos, mark_pos);
            i64 end_pos = Max(cursor_pos, mark_pos);
            
            if (cursor_pos < mark_pos)
                end_pos += 1;
            
            Range_i64 range = Ii64(start_pos, end_pos);
            draw_character_block(app, text_layout_id, range, roundness, fcolor_id(defcolor_highlight));
            paint_text_color_fcolor(app, text_layout_id, range, fcolor_id(defcolor_at_highlight));
        }
        draw_character_i_bar(app, text_layout_id, cursor_pos, fcolor_id(defcolor_cursor, cursor_sub_id));
    }
}

function b32
fcm_character_is_whitespace_or_underscore(char c) {
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v' || c == '_');
}

function b32
fcm_character_is_whitespace_or_underscore(u8 c) {
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v' || c == '_');
}

function b32
fcm_character_is_whitespace_or_underscore(u16 c) {
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v' || c == '_');
}

function b32
fcm_character_is_whitespace_or_underscore(u32 c) {
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v' || c == '_');
}

function i64
fcm_scan(Application_Links *app, Boundary_Function_List funcs, Buffer_ID buffer, Scan_Direction direction, i64 start_pos) {
    i64 result = 0;
    if (direction == Scan_Forward){
        i64 size = buffer_get_size(app, buffer);
        result = size + 1;
        for (Boundary_Function_Node *node = funcs.first;
             node != 0;
             node = node->next){
            i64 pos = fcm_scan(app, node->func, buffer, direction, start_pos);
            result = Min(result, pos);
        }
    }
    else{
        result = -1;
        for (Boundary_Function_Node *node = funcs.first;
             node != 0;
             node = node->next){
            i64 pos = fcm_scan(app, node->func, buffer, direction, start_pos);
            result = Max(result, pos);
        }
    }
    return(result);
}

function i64
fcm_scan(Application_Links *app, Boundary_Function *func, Buffer_ID buffer, Scan_Direction direction, i64 pos) {
    Side side = (direction == Scan_Forward)?(Side_Max):(Side_Min);
    return(func(app, buffer, side, direction, pos));
}

function i64
fcm_boundary_predicate(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos, Character_Predicate *predicate) {
    i64 result = 0;
    switch (side){
        case Side_Min:
        {
            result = fcm_buffer_seek_character_class_change_0_1(app, buffer, predicate, direction, pos);
        }break;
        case Side_Max:
        {
            result = fcm_buffer_seek_character_class_change_1_0(app, buffer, predicate, direction, pos);
        }break;
    }
    return(result);
}

function i64
fcm_buffer_seek_character_class_change_1_0(Application_Links *app, Buffer_ID buffer, Character_Predicate *predicate, Scan_Direction direction, i64 start_pos) {
    Character_Predicate negative = character_predicate_not(predicate);
    return(fcm_buffer_seek_character_class_change__inner(app, buffer, predicate, &negative, direction, start_pos));
}

function i64
fcm_buffer_seek_character_class_change_0_1(Application_Links *app, Buffer_ID buffer, Character_Predicate *predicate, Scan_Direction direction, i64 start_pos) {
    Character_Predicate negative = character_predicate_not(predicate);
    return(fcm_buffer_seek_character_class_change__inner(app, buffer, &negative, predicate, direction, start_pos));
}

function i64
fcm_buffer_seek_character_class_change__inner(Application_Links *app, Buffer_ID buffer, Character_Predicate *positive, Character_Predicate *negative, Scan_Direction direction, i64 start_pos) {
    i64 pos = start_pos;
    i64 line_num_startpos = get_line_number_from_pos(app, buffer, pos);
    
    switch (direction){
        case Scan_Backward:
        {
            pos = fcm_find_non_whitespace_pos(app, buffer, direction, pos - 1, 0);
            
            i64 line_num_current = get_line_number_from_pos(app, buffer, pos);
            if (line_num_startpos != line_num_current) {
                pos = get_line_side_pos(app, buffer, line_num_current, Side_Max);
                break;
            }
            
            String_Match m = buffer_seek_character_class(app, buffer, negative, direction, pos);
            pos = m.range.min;
            
            u32 c = buffer_get_char(app, buffer, m.range.min);
            if (c == '_' || c == ' ' || c == '\t')
                pos += 1;
            
            line_num_startpos = line_num_current;
            line_num_current = get_line_number_from_pos(app, buffer, pos);
            if (line_num_startpos != line_num_current) {
                i64 buffer_size = buffer_get_size(app, buffer);
                i64 line_min= get_line_side_pos(app, buffer, line_num_startpos, Side_Min);
                pos = fcm_find_non_whitespace_pos(app, buffer, Scan_Forward, line_min, buffer_size);
            }
            
        }break;
        case Scan_Forward:
        {
            // NOTES(tiny): Simply pushing
            i64 buffer_max = buffer_get_size(app, buffer);
            pos = fcm_find_non_whitespace_pos(app, buffer, direction, pos, buffer_max);
            
            i64 line_num_current = get_line_number_from_pos(app, buffer, pos);
            if (line_num_startpos != line_num_current) {
                i64 line_min = get_line_side_pos(app, buffer, line_num_current, Side_Min);
                pos = fcm_find_non_whitespace_pos(app, buffer, direction, line_min, buffer_max);
                break;
            }
            
            String_Match m = buffer_seek_character_class(app, buffer, positive, direction, pos);
            pos = m.range.min;
            
            u32 c = buffer_get_char(app, buffer, m.range.min);
            if (c == '_' || c == ' ' || c == '\t')
                pos += 1;
            
        }break;
    }
    return(pos);
}

function i64
fcm_boundary_for_word_scan(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos){
    return fcm_boundary_predicate(app, buffer, side, direction, pos, &character_predicate_for_word_scan);
}

function i64
fcm_boundary_for_name_scan(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos){
    return fcm_boundary_predicate(app, buffer, side, direction, pos, &character_predicate_for_name_scan);
}

function Range_i64
fcm_setup_range_left_boundary(Application_Links *app, fcm_vb vb, Boundary_Function_List func) {
    Range_i64 range = {};
    range.one_past_last = view_get_cursor_pos(app, vb.view);
    range.first = fcm_scan(app, func, vb.buffer, Scan_Backward, range.one_past_last);
    
    range = rectify(range);
    return range;
}

function Range_i64
fcm_setup_range_right_boundary(Application_Links *app, fcm_vb vb, Boundary_Function_List func) {
    Range_i64 range = {};
    range.first= view_get_cursor_pos(app, vb.view);
    range.one_past_last = fcm_scan(app, func, vb.buffer, Scan_Forward, range.first);
    
    rectify(range);
    return range;
}

internal i64
fcm_find_non_whitespace_pos(Application_Links *app, Buffer_ID buffer, Scan_Direction direction, i64 pos_start, i64 pos_end) {
    i64 result = pos_start;
    u32 c = buffer_get_char(app, buffer, result);
    
    if (direction == Scan_Backward) {
        while (result > pos_end && fcm_character_is_whitespace_or_underscore(c)) {
            result -= 1;
            c = buffer_get_char(app, buffer, result);
        }
    }
    else if (direction == Scan_Forward) {
        while (result < pos_end && fcm_character_is_whitespace_or_underscore(c)) {
            result += 1;
            c = buffer_get_char(app, buffer, result);
        }
    }
    
    return result;
}

function void
fcm_isearch(Application_Links *app, Scan_Direction start_scan, i64 first_pos,
            String_Const_u8 query_init){
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
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
            else{
                u64 size = bar.string.size;
                size = clamp_top(size, sizeof(previous_isearch_query) - 1);
                block_copy(previous_isearch_query, bar.string.str, size);
                previous_isearch_query[size] = 0;
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
        view_set_cursor_and_preferred_x(app, view, seek_pos(first_pos));
    }
    
    view_set_camera_bounds(app, view, old_margin, old_push_in);
}

function void
fcm_isearch(Application_Links *app, Scan_Direction start_scan, String_Const_u8 query_init){
    View_ID view = get_active_view(app, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);;
    isearch(app, start_scan, pos, query_init);
}

function void
fcm_isearch(Application_Links *app, Scan_Direction start_scan){
    View_ID view = get_active_view(app, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);;
    isearch(app, start_scan, pos, SCu8());
}

function void
fcm_isearch_identifier(Application_Links *app, Scan_Direction scan){
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer_id = view_get_buffer(app, view, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);
    Scratch_Block scratch(app);
    Range_i64 range = enclose_pos_alpha_numeric_underscore(app, buffer_id, pos);
    String_Const_u8 query = push_buffer_range(app, scratch, buffer_id, range);
    isearch(app, scan, range.first, query);
}

#endif // FCM_FCODER_MODIFICATION_HPP