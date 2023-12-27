#include "memory.h"

void arena_init(Arena* arena, void* reserve, usize reserve_size){
	arena->buf = reserve;
	arena->cap = reserve_size;
	arena->prev_pos = 0;
	arena->curr_pos = 0;
}

void* arena_alloc_align(Arena* arena, u64 size, usize align){
	uptr ptr = (uptr) (arena->buf + arena->curr_pos);
	usize offset = (usize) (AlignUpPow2(ptr, align) - (uptr) arena->buf); // - to change to relative offset
	if (offset + size <= arena->cap) {
		arena->prev_pos = offset;
		arena->curr_pos = offset + size;
		void* mem = &arena->buf[offset];
		memset(mem, 0, size);
		return mem;
	}
	return NULL;
}

void* arena_alloc(Arena* arena, u64 size){
	return arena_alloc_align(arena, size, DEFAULT_ALIGN);
}

void* arena_resize_align(Arena* arena, void* old_memory, usize old_size, usize new_size, usize align){
	u8* old_mem = (u8*) old_memory;
	if (old_mem == NULL || old_size == 0) {
		return arena_alloc_align(arena, new_size, align);
	} else if (arena->buf <= old_mem && old_mem <= arena->buf + arena->cap) {

		if (arena->buf + arena->prev_pos == old_mem) {
			if (arena->prev_pos + new_size <= arena->cap) {
				arena->curr_pos = arena->prev_pos + new_size;
				if (new_size > old_size) memset(&arena->buf[arena->curr_pos], 0, new_size - old_size);
				return old_mem;
			} else {
				return NULL;
			}
		} else {
			void* new_memory = arena_alloc_align(arena, new_size, align);
			memmove(new_memory, old_memory, Min(new_size, old_size));
			return new_memory;
		}

	}

	return NULL;
}

void* arena_resize(Arena* arena, void* old_memory, usize old_size, usize new_size){
	return arena_resize_align(arena, old_memory, old_size, new_size, DEFAULT_ALIGN);
}

void arena_clear(Arena* arena){
	arena->curr_pos = 0;
	arena->prev_pos = 0;
}

Temp_Arena temp_arena_begin(Arena* arena){
	Temp_Arena temp = {0};
	temp.arena = arena;
	temp.prev_pos = arena->prev_pos;
	temp.curr_pos = arena->curr_pos;
	return temp;
}

void temp_arena_end(Temp_Arena* temp_arena){
	temp_arena->arena->curr_pos = temp_arena->curr_pos;
	temp_arena->arena->prev_pos = temp_arena->prev_pos;
}
