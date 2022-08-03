#ifndef FCODER_MODAL_PROTOTYPES_H
#define FCODER_MODAL_PROTOTYPES_H

// TODO(tiny): Look at all the functions again and see what fits
// get_line_start_pos
// get_line_end_pos
// get_line_side_pos_from_pos
// get_line_side_pos
// get_line_number_from_pos

/////////////
// Defines //
/////////////
#define Bind2(func, key_hold, key_use) Bind(func, key_use, key_hold)
#define Bind3(func, key_hold1, key_hold2, key_use) Bind(func, key_use, key_hold1, key_hold2)

#define FCM_COLOR_RED     0xffff0000
#define FCM_COLOR_GREEN   0xff00ff00
#define FCM_COLOR_BLUE    0xff0000ff
#define FCM_COLOR_YELLOW  0xffffff00
#define FCM_COLOR_CYAN    0xff00ffff
#define FCM_COLOR_MAGENTA 0xffff00ff
#define FCM_COLOR_ORANGE  0xffffa500

#define FCM_LEFT  1
#define FCM_DOWN  2
#define FCM_UP    3
#define FCM_RIGHT 4

#define FCM_MAX_MARKS 1023

////////////////////
// Structs & Enum //
////////////////////
typedef struct {
    View_ID view;
    Buffer_ID buffer;
} fcm_vb;

typedef struct {
    i64 pos;
    i64 line;
} fcm_buffer_type;

typedef struct {
    i64 pos[FCM_MAX_MARKS];
    i64 count;
} fcm_marks_type;

enum FCM_MODE_FLAGS : u64 {
    FCM_MODE_NORMAL        = 0x1,
    
    FCM_MODE_TYPE          = 0x100,
    FCM_TYPE_INSERT        = 0x200,
    FCM_TYPE_REPLACE       = 0x400,
    FCM_TYPE_REPLACE_CHAR  = 0x800,
    FCM_TYPE_APPEND        = 0x1000,
    
    FCM_MODE_BUFFER        = 0x10000,
    FCM_BUFFER_COPY        = 0x20000,
    FCM_BUFFER_CUT         = 0x40000,
    FCM_BUFFER_DELETE      = 0x80000,
    
    FCM_MODE_VISUAL        = 0x1000000,
    FCM_VISUAL_HIGHLIGHT   = 0x2000000,
    FCM_VISUAL_LINE        = 0x4000000,
    FCM_VISUAL_MARKED      = 0x8000000,
    FCM_VISUAL_CAN_TYPE	= 0x10000000,
    
    FCM_FLAGS_MAX          = 0xFFFFFFFFFFFFFFFF
};
//////////////////////
// Global Variables //
//////////////////////
global String_ID fcm_mapid_shared;
global String_ID fcm_mapid_normal;
global String_ID fcm_mapid_type;
global String_ID fcm_mapid_buffer;
global String_ID fcm_mapid_visual;

global u64 fcm_flags;
global fcm_marks_type fcm_marks;

/* 
Predicate Reference:

global Character_Predicate character_predicate_for_word_scan = { {
  0,   8,  16,  24,  32,  40,  48,  56,
 64,  72,  80,  88,  96, 104, 112, 120,
128, 136, 144, 152, 160, 168, 176, 184, 
192, 200, 208, 216, 224, 232, 240, 248,
} };
*/
global Character_Predicate character_predicate_for_word_scan = { {
        0,  62,   0,   0, 133,  83,   0,   8, // TAB, FF, VT, LF, CR, SPACE, COMMA, ", ', ()
        254, 255, 255, 175,   0,   0,   0,  40, // A-Z, _, [], {}
        0,   0,   0,   0,   0,   0,   0,   0, 
        0,   0,   0,   0,   0,   0,   0,   0, 
    } };

global Character_Predicate character_predicate_for_name_scan = { {
        0,  62,   0,   0, 133,  83,   0,   8, // TAB, FF, VT, LF, CR, SPACE, COMMA, ", ', () 
        0,   0,   0,  40,   0,   0,   0,  40, // [], {}
        0,   0,   0,   0,   0,   0,   0,   0, 
        0,   0,   0,   0,   0,   0,   0,   0, 
    } };

/////////////////////////////////
// fcm_4coder_modification.hpp //
/////////////////////////////////
CUSTOM_COMMAND_SIG(fcm_list_substring_locations_other_panel);
CUSTOM_COMMAND_SIG(fcm_select_location_same_panel);
CUSTOM_COMMAND_SIG(fcm_interactive_new_or_open);
CUSTOM_COMMAND_SIG(fcm_command_lister);
CUSTOM_COMMAND_SIG(fcm_project_command_lister);
CUSTOM_COMMAND_SIG(fcm_change_active_panel);
CUSTOM_COMMAND_SIG(fcm_change_active_panel_backwards);
CUSTOM_COMMAND_SIG(fcm_write_text_and_auto_indent);

CUSTOM_COMMAND_SIG(fcm_startup);
BUFFER_HOOK_SIG(fcm_begin_buffer);

internal void
fcm_set_all_default_hooks(Application_Links *app);

internal void
fcm_4coder_initialize(Application_Links *app, String_Const_u8_Array file_names, i32 override_font_size, b32 override_hinting);

internal void
fcm_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id);

internal void
fcm_render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, Rect_f32 rect);

internal void
fcm_draw_original_4coder_style_cursor_mark_highlight(Application_Links *app, View_ID view_id, b32 is_active_view, Buffer_ID buffer, Text_Layout_ID text_layout_id, f32 roundness, f32 outline_thickness);

function void
fcm_draw_original_4coder_style_mark(Application_Links *app, View_ID view_id, b32 is_active_view,
                                    Buffer_ID buffer, Text_Layout_ID text_layout_id,
                                    f32 roundness, f32 outline_thickness);

internal void
fcm_draw_i_bar(Application_Links *app, View_ID view_id, Text_Layout_ID text_layout_id);

function void
fcm_draw_i_bar_with_highlight(Application_Links *app, View_ID view_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, f32 roundness);

internal void
fcm_write_text_input(Application_Links *app);

internal void
fcm_write_text(Application_Links *app, String_Const_u8 insert);

function b32
fcm_character_is_whitespace_or_underscore(char c);

function b32
fcm_character_is_whitespace_or_underscore(u8 c);

function b32
fcm_character_is_whitespace_or_underscore(u16 c);

function b32
fcm_character_is_whitespace_or_underscore(u32 c);

function i64
fcm_scan(Application_Links *app, Boundary_Function_List funcs, Buffer_ID buffer, Scan_Direction direction, i64 start_pos);

function i64
fcm_scan(Application_Links *app, Boundary_Function *func, Buffer_ID buffer, Scan_Direction direction, i64 pos);

function i64
fcm_boundary_predicate(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos, Character_Predicate *predicate);

function i64
fcm_buffer_seek_character_class_change_1_0(Application_Links *app, Buffer_ID buffer, Character_Predicate *predicate, Scan_Direction direction, i64 start_pos);

function i64
fcm_buffer_seek_character_class_change_0_1(Application_Links *app, Buffer_ID buffer, Character_Predicate *predicate, Scan_Direction direction, i64 start_pos);

function i64
fcm_buffer_seek_character_class_change__inner(Application_Links *app, Buffer_ID buffer, Character_Predicate *positive, Character_Predicate *negative, Scan_Direction direction, i64 start_pos);

function i64
fcm_boundary_for_word_scan(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos);

function i64
fcm_boundary_for_name_scan(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos);

function i64
fcm_boundary_for_name_scan_with_brackets(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos);

function i64
fcm_boundary_for_scope_scan(Application_Links *app, Buffer_ID buffer, Side side, Scan_Direction direction, i64 pos);

function Range_i64
fcm_setup_range_left_boundary(Application_Links *app, fcm_vb data, Boundary_Function_List func);

function Range_i64
fcm_setup_range_right_boundary(Application_Links *app, fcm_vb data, Boundary_Function_List func);

internal i64
fcm_find_non_whitespace_pos(Application_Links *app, Buffer_ID buffer, Scan_Direction direction, i64 pos_start, i64 pos_end);

function void
fcm_isearch(Application_Links *app, Scan_Direction start_scan, i64 first_pos, String_Const_u8 query_init);

function void
fcm_isearch(Application_Links *app, Scan_Direction start_scan, String_Const_u8 query_init);

function void
fcm_isearch(Application_Links *app, Scan_Direction start_scan);

function void
fcm_isearch_identifier(Application_Links *app, Scan_Direction scan);

//////////////////////
// fcm_bindings.hpp //
//////////////////////
internal void
fcm_setup_bindings_shared(Mapping *mapping);

internal void
fcm_setup_bindings_normal(Mapping *mapping);

internal void
fcm_setup_bindings_type(Mapping *mapping);

internal void
fcm_setup_bindings_buffer(Mapping *mapping);

internal void
fcm_setup_bindings_visual(Mapping *mapping, i64 mapid);

////////////////////
// fcm_buffer.hpp //
////////////////////
CUSTOM_COMMAND_SIG(fcm_mode_buffer_copy);
CUSTOM_COMMAND_SIG(fcm_mode_buffer_cut);
CUSTOM_COMMAND_SIG(fcm_mode_buffer_delete);
CUSTOM_COMMAND_SIG(fcm_mode_buffer_toggle);

CUSTOM_COMMAND_SIG(fcm_buffer_do_left_word);
CUSTOM_COMMAND_SIG(fcm_buffer_do_right_word);
CUSTOM_COMMAND_SIG(fcm_buffer_do_left_name);
CUSTOM_COMMAND_SIG(fcm_buffer_do_right_name);
CUSTOM_COMMAND_SIG(fcm_buffer_do_bol);
CUSTOM_COMMAND_SIG(fcm_buffer_do_eol);
CUSTOM_COMMAND_SIG(fcm_buffer_do_current_line_and_above);
CUSTOM_COMMAND_SIG(fcm_buffer_do_current_line_and_below);
CUSTOM_COMMAND_SIG(fcm_buffer_do_all_lines_on_and_above);
CUSTOM_COMMAND_SIG(fcm_buffer_do_all_lines_on_and_below);

CUSTOM_COMMAND_SIG(fcm_buffer_copy_current_line);
CUSTOM_COMMAND_SIG(fcm_buffer_delete_current_line);

CUSTOM_COMMAND_SIG(fcm_copy_line);
CUSTOM_COMMAND_SIG(fcm_cut_line);
CUSTOM_COMMAND_SIG(fcm_delete_line);

internal void
fcm_buffer_do_left_boundary(Application_Links *app, Boundary_Function_List func, fcm_vb data);

internal void
fcm_buffer_do_right_boundary(Application_Links *app, Boundary_Function_List func, fcm_vb data);

internal void
fcm_buffer_do_action(Application_Links *app, Buffer_ID buffer, Range_i64 range);

//////////////////////
// fcm_command.hpp  //
//////////////////////
CUSTOM_COMMAND_SIG(fcm_command);

internal b32
fcm_command_parse(Application_Links *app, String_Const_u8 s);

internal b32
fcm_command_line_goto(Application_Links *app, String_Const_u8 s);

internal b32
fcm_command_copy(Application_Links *app, String_Const_u8 s);

internal b32
fcm_command_cut(Application_Links *app, String_Const_u8 s);

internal b32
fcm_command_delete(Application_Links *app, String_Const_u8 s);

internal b32
fcm_command_save(Application_Links *app, String_Const_u8 s, b32 percent);

internal b32
fcm_command_quit(Application_Links *app, String_Const_u8 s);

internal b32
fcm_command_substitute(Application_Links *app, String_Const_u8 s, b32 percent);

function b32
fcm_is_number(String_Const_u8 s);

function b32
fcm_command_buffer_get_range(Application_Links *app, fcm_vb vb, String_Const_u8 s, Range_i64 *range);

////////////////////
// fcm_normal.hpp //
////////////////////
CUSTOM_COMMAND_SIG(fcm_mode_normal);
CUSTOM_COMMAND_SIG(fcm_move_left_word);
CUSTOM_COMMAND_SIG(fcm_move_right_word);
CUSTOM_COMMAND_SIG(fcm_move_left_word_underscore);
CUSTOM_COMMAND_SIG(fcm_move_left_word_underscore);
CUSTOM_COMMAND_SIG(fcm_move_left_name);
CUSTOM_COMMAND_SIG(fcm_move_right_name);

internal void
fcm_move_left_boundary(Application_Links *app, Boundary_Function_List func);

internal void
fcm_move_right_boundary(Application_Links *app, Boundary_Function_List func);

////////////////////////////
// fcm_other_commands.hpp //
////////////////////////////
CUSTOM_COMMAND_SIG(FCM_RESERVED_FUNCTION);
CUSTOM_COMMAND_SIG(fcm_paste);
CUSTOM_COMMAND_SIG(fcm_paste_line_above);
CUSTOM_COMMAND_SIG(fcm_paste_line_current);
CUSTOM_COMMAND_SIG(fcm_paste_line_below);
CUSTOM_COMMAND_SIG(fcm_substitute_one_in_file);
CUSTOM_COMMAND_SIG(fcm_substitute_all_in_file);
CUSTOM_COMMAND_SIG(fcm_substitute_all_in_project_buffer);

internal void 
fcm_set_mapid_mode(Application_Links* app, Command_Map_ID mapid, i64 flags);

internal void
fcm_get_view_and_buffer(Application_Links *app, Access_Flag access, fcm_vb *data);

internal void
fcm_get_cursor_info(Application_Links *app, fcm_vb vb, fcm_buffer_type *cursor);

internal void
fcm_get_mark_info(Application_Links *app, fcm_vb vb, fcm_buffer_type *mark);

internal void
fcm_get_end_of_buffer(Application_Links *app, fcm_vb vb, fcm_buffer_type *buffer);

internal void
fcm_search_and_replace(Application_Links *app, Scan_Direction start_scan, i64 first_pos, 
                       String_Const_u8 query_init, String_Const_u8 replace_str);

function b32
fcm_if_view_has_highlighted_range_delete_range(Application_Links *app, View_ID view_id);

//////////////////
// fcm_type.hpp //
//////////////////
CUSTOM_COMMAND_SIG(fcm_mode_type_insert);
CUSTOM_COMMAND_SIG(fcm_mode_type_insert_append);
CUSTOM_COMMAND_SIG(fcm_mode_type_insert_bol);
CUSTOM_COMMAND_SIG(fcm_mode_type_insert_eol);
CUSTOM_COMMAND_SIG(fcm_mode_type_insert_new_line_current);
CUSTOM_COMMAND_SIG(fcm_mode_type_insert_new_line_above);
CUSTOM_COMMAND_SIG(fcm_mode_type_insert_new_line_below);
CUSTOM_COMMAND_SIG(fcm_mode_type_replace);
CUSTOM_COMMAND_SIG(fcm_mode_type_replace_char);
CUSTOM_COMMAND_SIG(fcm_mode_type_replace_append);
CUSTOM_COMMAND_SIG(fcm_mode_type_replace_bol);
CUSTOM_COMMAND_SIG(fcm_mode_type_replace_eol);
CUSTOM_COMMAND_SIG(fcm_write_text_and_auto_indent);
CUSTOM_COMMAND_SIG(fcm_type_delete_left_word);
CUSTOM_COMMAND_SIG(fcm_type_delete_right_word);
CUSTOM_COMMAND_SIG(fcm_type_delete_left_name);
CUSTOM_COMMAND_SIG(fcm_type_delete_right_name);
CUSTOM_COMMAND_SIG(fcm_type_delete_top_most_scope);
CUSTOM_COMMAND_SIG(fcm_type_delete_next_scope_after_current);

internal void
fcm_delete_left_boundary(Application_Links *app, Boundary_Function_List func);

internal void
fcm_delete_right_boundary(Application_Links *app, Boundary_Function_List func);

internal void
fcm_type_delete_next_scope_after_pos(Application_Links *app, fcm_vb vb, i64 cursor_pos);

/////////////////////
// fcm_visual.hpp  //
/////////////////////
CUSTOM_COMMAND_SIG(fcm_mode_visual_highlight);
CUSTOM_COMMAND_SIG(fcm_mode_visual_line);
CUSTOM_COMMAND_SIG(fcm_mode_visual_marked);
CUSTOM_COMMAND_SIG(fcm_toggle_mode_visual);
CUSTOM_COMMAND_SIG(fcm_visual_back_to_normal_mode);
CUSTOM_COMMAND_SIG(fcm_visual_start_type);
CUSTOM_COMMAND_SIG(fcm_visual_copy);
CUSTOM_COMMAND_SIG(fcm_visual_cut);
CUSTOM_COMMAND_SIG(fcm_visual_delete);
CUSTOM_COMMAND_SIG(fcm_visual_paste);
CUSTOM_COMMAND_SIG(fcm_visual_type_or_copy);
CUSTOM_COMMAND_SIG(fcm_visual_type_or_cut);
CUSTOM_COMMAND_SIG(fcm_visual_type_or_delete);
CUSTOM_COMMAND_SIG(fcm_visual_type_or_paste);
CUSTOM_COMMAND_SIG(fcm_visual_type_backspace);
CUSTOM_COMMAND_SIG(fcm_visual_type_delete);
CUSTOM_COMMAND_SIG(fcm_visual_substitute);
CUSTOM_COMMAND_SIG(fcm_visual_move_up); // Note(tiny): Line/Mark Only
CUSTOM_COMMAND_SIG(fcm_visual_move_down); // Note(tiny): Line/Mark Only

internal void
fcm_visual_copy_highlight(Application_Links *app);

internal void
fcm_visual_cut_highlight(Application_Links *app);

internal void
fcm_visual_delete_highlight(Application_Links *app);

internal void
fcm_visual_paste_highlight(Application_Links *app);

internal void
fcm_visual_replace_highlight(Application_Links *app);

internal void
fcm_visual_copy_line(Application_Links *app);

internal void
fcm_visual_cut_line(Application_Links *app);

internal void
fcm_visual_delete_line(Application_Links *app);

internal void
fcm_visual_paste_line(Application_Links *app);

internal void
fcm_visual_replace_line(Application_Links *app);

internal void
fcm_visual_move_up_line(Application_Links *app);

internal void
fcm_visual_move_down_line(Application_Links *app);

internal void
fcm_visual_copy_line_marked(Application_Links *app);

internal void
fcm_visual_cut_line_marked(Application_Links *app);

internal void
fcm_visual_delete_line_marked(Application_Links *app);

internal void
fcm_visual_paste_line_marked(Application_Links *app);

internal void
fcm_visual_replace_line_marked(Application_Links *app);

internal void
fcm_visual_move_up_line_marked(Application_Links *app);

internal void
fcm_visual_mode_down_line_marked(Application_Links *app);

internal void
fcm_sync_mark_x_to_cursor_x(Application_Links *app);

internal void
fcm_visual_update_marks_up_line(Application_Links *app);

internal void
fcm_visual_update_marks_down_line(Application_Links *app);

function i64
fcm_marks_quicksort_partition(i64 index_low, i64 index_high);

function void
fcm_marks_quicksort(i64 index_low, i64 index_high);

#endif // FCODER_MODAL_PROTOTYPES_H