/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 03.01.2017
 *
 * File layer for 4coder
 *
 */

// TOP

//
// Edit Position Basics
//

enum Edit_Pos_Set_Type{
    EditPos_None,
    EditPos_CursorSet,
    EditPos_ScrollSet
};
struct File_Edit_Positions{
    GUI_Scroll_Vars scroll;
    Full_Cursor cursor;
    i32 mark;
    f32 preferred_x;
    i32 scroll_i;
    i32 last_set_type;
    b32 in_view;
};
static File_Edit_Positions null_edit_pos = {0};

internal void
edit_pos_set_cursor(File_Edit_Positions *edit_pos, Full_Cursor cursor, b32 set_preferred_x, b32 unwrapped_lines){
    edit_pos->cursor = cursor;
    if (set_preferred_x){
        edit_pos->preferred_x = cursor.wrapped_x;
        if (unwrapped_lines){
            edit_pos->preferred_x = cursor.unwrapped_x;
        }
    }
    edit_pos->last_set_type = EditPos_CursorSet;
}

internal void
edit_pos_set_scroll(File_Edit_Positions *edit_pos, GUI_Scroll_Vars scroll){
    edit_pos->scroll = scroll;
    edit_pos->last_set_type = EditPos_ScrollSet;
}


// TODO(NAME): Replace this with markers over time.
//
// Highlighting Information
//

struct Text_Effect{
    i32 start, end;
    u32 color;
    f32 seconds_down, seconds_max;
};

//
// Editing_File
//

union Buffer_Slot_ID{
    i32 id;
    i16 part[2];
};
inline Buffer_Slot_ID
to_file_id(i32 id){
    Buffer_Slot_ID result;
    result.id = id;
    return(result);
}

struct Marker_Array{
    Marker_Array *next, *prev;
    Buffer_Slot_ID buffer_id;
    u32 count, sim_max, max;
    Marker marker_0;
};
global_const u32 sizeof_marker_array = sizeof(Marker_Array) - sizeof(Marker);

struct Editing_File_Markers{
    Marker_Array sentinel;
    u32 array_count;
    u32 marker_count;
};

struct Editing_File_Settings{
    i32 base_map_id;
    i32 display_width;
    i32 minimum_base_display_width;
    i32 wrap_indicator;
    b32 dos_write_mode;
    b32 virtual_white;
    Font_ID font_id;
    b8 unwrapped_lines;
    b8 tokens_exist;
    b8 is_initialized;
    b8 unimportant;
    b8 read_only;
    b8 never_kill;
    u8 pad[2];
};
global_const Editing_File_Settings null_editing_file_settings = {0};

struct Editing_File_State{
    Gap_Buffer buffer;
    
    i32 *wrap_line_index;
    i32 wrap_max;
    
    i32 *character_starts;
    i32 character_start_max;
    
    f32 *line_indents;
    i32 line_indent_max;
    
    i32 wrap_line_count;
    
    i32 *wrap_positions;
    i32 wrap_position_count;
    i32 wrap_position_max;
    
    Undo_Data undo;
    
    Cpp_Token_Array token_array;
    Cpp_Token_Array swap_array;
    u32 lex_job;
    b32 tokens_complete;
    b32 still_lexing;
    
    Text_Effect paste_effect;
    
    Dirty_State dirty;
    u32 ignore_behind_os;
    
    File_Edit_Positions edit_pos_space[16];
    File_Edit_Positions *edit_poss[16];
    i32 edit_poss_count;
};
global_const Editing_File_State null_editing_file_state = {0};

struct Editing_File_Name{
    char live_name_[256];
    //char source_path_[256];
    char extension_[16];
    String live_name;
    //String source_path;
    String extension;
};

struct Editing_File_Canon_Name{
    char name_[256];
    String name;
};

struct File_Node{
    File_Node *next, *prev;
};

struct Editing_File{
    // NOTE(allen): node must be the first member of Editing_File!
    File_Node node;
    Editing_File_Settings settings;
    b32 is_loading;
    b32 is_dummy;
    Editing_File_State state;
    Editing_File_Markers markers;
    Editing_File_Name name;
    Editing_File_Canon_Name canon;
    Buffer_Slot_ID id;
    //u64 unique_buffer_id;
};
static Editing_File null_editing_file = {0};


//
// Handling a file's Marker Arrays
//

internal void
init_file_markers_state(Editing_File_Markers *markers){
    Marker_Array *sentinel = &markers->sentinel;
    dll_init_sentinel(sentinel);
    markers->array_count = 0;
    markers->marker_count = 0;
}

internal void
clear_file_markers_state(General_Memory *general, Editing_File_Markers *markers){
    Marker_Array *sentinel = &markers->sentinel;
    for (Marker_Array *marker_array = sentinel->next;
         marker_array != sentinel;
         marker_array = sentinel->next){
        dll_remove(marker_array);
        general_memory_free(general, marker_array);
    }
    Assert(sentinel->next == sentinel);
    Assert(sentinel->prev == sentinel);
    markers->array_count = 0;
    markers->marker_count = 0;
}

internal void*
allocate_markers_state(General_Memory *general, Editing_File *file, u32 new_array_max){
    u32 memory_size = sizeof_marker_array + sizeof(Marker)*new_array_max;
    memory_size = l_round_up_u32(memory_size, KB(4));
    u32 real_max = (memory_size - sizeof_marker_array)/sizeof(Marker);
    Marker_Array *array = (Marker_Array*)general_memory_allocate(general, memory_size);
    
    dll_back_insert(&file->markers.sentinel, array);
    array->buffer_id = file->id;
    array->count = 0;
    array->sim_max = new_array_max;
    array->max = real_max;
    
    ++file->markers.array_count;
    
    return(array);
}

internal b32
markers_set(Editing_File *file, void *handle, u32 first_index, u32 count, Marker *source){
    Assert(file != 0);
    b32 result = false;
    if (handle != 0){
        Marker_Array *markers = (Marker_Array*)handle;
        if (markers->buffer_id.id == file->id.id){
            if (first_index + count <= markers->sim_max){
                u32 new_count = first_index + count;
                if (new_count > markers->count){
                    file->markers.marker_count += new_count - markers->count;
                    markers->count = new_count;
                }
                Marker *dst = &markers->marker_0;
                memcpy(dst + first_index, source, sizeof(Marker)*count);
                result = true;
            }
        }
    }
    return(result);
}

internal b32
markers_get(Editing_File *file, void *handle, u32 first_index, u32 count, Marker *output){
    Assert(file != 0);
    b32 result = false;
    if (handle != 0){
        Marker_Array *markers = (Marker_Array*)handle;
        if (markers->buffer_id.id == file->id.id){
            if (first_index + count <= markers->count){
                Marker *src = &markers->marker_0;
                memcpy(output, src + first_index, sizeof(Marker)*count);
                result = true;
            }
        }
    }
    return(result);
}

internal b32
markers_free(General_Memory *general, Editing_File *file, void *handle){
    Assert(file != 0);
    b32 result = false;
    if (handle != 0){
        Marker_Array *markers = (Marker_Array*)handle;
        if (markers->buffer_id.id == file->id.id){
            dll_remove(markers);
            file->markers.marker_count -= markers->count;
            --file->markers.array_count;
            general_memory_free(general, markers);
        }
    }
    return(result);
}

//
// Manipulating a file's Edit_Pos array
//

internal i32
edit_pos_get_index(Editing_File *file, File_Edit_Positions *edit_pos){
    i32 edit_pos_index = -1;
    
    i32 count = file->state.edit_poss_count;
    File_Edit_Positions **edit_poss = file->state.edit_poss;
    for (i32 i = 0; i < count; ++i){
        if (edit_poss[i] == edit_pos){
            edit_pos_index = i;
            break;
        }
    }
    
    return(edit_pos_index);
}

internal b32
edit_pos_move_to_front(Editing_File *file, File_Edit_Positions *edit_pos){
    b32 result = false;
    
    if (file && edit_pos){
        i32 edit_pos_index = edit_pos_get_index(file, edit_pos);
        Assert(edit_pos_index != -1);
        
        File_Edit_Positions **edit_poss = file->state.edit_poss;
        
        memmove(edit_poss + 1, edit_poss, edit_pos_index*sizeof(*edit_poss));
        
        edit_poss[0] = edit_pos;
        result = true;
    }
    
    return(result);
}

internal b32
edit_pos_unset(Editing_File *file, File_Edit_Positions *edit_pos){
    b32 result = false;
    
    if (file && edit_pos){
        i32 edit_pos_index = edit_pos_get_index(file, edit_pos);
        Assert(edit_pos_index != -1);
        
        i32 count = file->state.edit_poss_count;
        File_Edit_Positions **edit_poss = file->state.edit_poss;
        
        memmove(edit_poss + edit_pos_index,
                edit_poss + edit_pos_index + 1,
                (count - edit_pos_index - 1)*sizeof(*edit_poss));
        
        edit_pos->in_view = false;
        
        if (file->state.edit_poss_count > 1){
            file->state.edit_poss_count -= 1;
        }
        result = true;
    }
    
    return(result);
}

internal File_Edit_Positions*
edit_pos_get_new(Editing_File *file, i32 index){
    File_Edit_Positions *result = 0;
    
    if (file && 0 <= index && index < 16){
        result = file->state.edit_pos_space + index;
        i32 edit_pos_index = edit_pos_get_index(file, result);
        
        if (edit_pos_index == -1){
            File_Edit_Positions **edit_poss = file->state.edit_poss;
            i32 count = file->state.edit_poss_count;
            
            if (count > 0){
                if (edit_poss[0]->in_view){
                    memcpy(result, edit_poss[0], sizeof(*result));
                    memmove(edit_poss+1, edit_poss, sizeof(*edit_poss)*count);
                    file->state.edit_poss_count = count + 1;
                }
                else{
                    Assert(count == 1);
                    memcpy(result, edit_poss[0], sizeof(*result));
                }
            }
            else{
                memset(result, 0, sizeof(*result));
                file->state.edit_poss_count = 1;
            }
            
            edit_poss[0] = result;
        }
        
        result->in_view = true;
    }
    
    return(result);
}


//
// Cursor Seeking
//

inline Partial_Cursor
file_compute_cursor_from_pos(Editing_File *file, i32 pos){
    Partial_Cursor result = buffer_partial_from_pos(&file->state.buffer, pos);
    return(result);
}

inline Partial_Cursor
file_compute_cursor_from_line_character(Editing_File *file, i32 line, i32 character){
    Partial_Cursor result = buffer_partial_from_line_character(&file->state.buffer, line, character);
    return(result);
}

inline b32
file_compute_partial_cursor(Editing_File *file, Buffer_Seek seek, Partial_Cursor *cursor){
    b32 result = true;
    switch (seek.type){
        case buffer_seek_pos:
        {
            *cursor = file_compute_cursor_from_pos(file, seek.pos);
        }break;
        
        case buffer_seek_line_char:
        {
            *cursor = file_compute_cursor_from_line_character(file, seek.line, seek.character);
        }break;
        
        default:
        {
            result = false;
        }break;
    }
    return(result);
}


//
// Dirty Flags
//

inline b32
buffer_needs_save(Editing_File *file){
    b32 result = 0;
    if (!file->settings.unimportant){
        if (file->state.dirty == DirtyState_UnsavedChanges){
            result = 1;
        }
    }
    return(result);
}

inline b32
buffer_can_save(Editing_File *file){
    b32 result = 0;
    if (!file->settings.unimportant){
        if (file->state.dirty == DirtyState_UnsavedChanges ||
            file->state.dirty == DirtyState_UnloadedChanges){
            result = 1;
        }
    }
    return(result);
}

inline b32
file_is_ready(Editing_File *file){
    b32 result = 0;
    if (file && file->is_loading == 0){
        result = 1;
    }
    return(result);
}

inline void
file_set_to_loading(Editing_File *file){
    file->state = null_editing_file_state;
    file->settings = null_editing_file_settings;
    file->is_loading = 1;
}

inline void
file_mark_clean(Editing_File *file){
    if (file->settings.unimportant){
        file->state.dirty = DirtyState_UpToDate;
    }
    else{
        if (file->state.dirty != DirtyState_UnloadedChanges){
            file->state.dirty = DirtyState_UpToDate;
        }
    }
}

inline void
file_mark_dirty(Editing_File *file){
    if (file->settings.unimportant){
        file->state.dirty = DirtyState_UpToDate;
    }
    else{
        if (file->state.dirty != DirtyState_UnloadedChanges){
            file->state.dirty = DirtyState_UnsavedChanges;
        }
    }
}

inline void
file_mark_behind_os(Editing_File *file){
    if (file->settings.unimportant){
        file->state.dirty = DirtyState_UpToDate;
    }
    else{
        file->state.dirty = DirtyState_UnloadedChanges;
    }
}

inline Dirty_State
file_get_sync(Editing_File *file){
    return (file->state.dirty);
}


// BOTTOM

