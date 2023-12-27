#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include "types.h"
#include "macros.h"

// Courtesy: https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/

typedef struct Arena {
	u8* buf;
	usize cap;
	usize prev_pos;
	usize curr_pos;
} Arena;

typedef struct Temp_Arena {
	Arena* arena;
	usize prev_pos;
	usize curr_pos;
} Temp_Arena;

#ifndef DEFAULT_ALIGN
#	define DEFAULT_ALIGN (2 * sizeof(void*))
#endif

void arena_init(Arena* arena, void* reserve, usize reserve_size); // Ask the user to reserve some mem for us
void* arena_alloc_align(Arena* arena, u64 size, usize align);
void* arena_alloc(Arena* arena, u64 size);
void* arena_resize_align(Arena* arena, void* old_memory, usize old_size, usize new_size, usize align);
void* arena_resize(Arena* arena, void* old_memory, usize old_size, usize new_size);
void arena_clear(Arena* arena);
// To deinit arena free your reserve or arena->buf
Temp_Arena temp_arena_begin(Arena* arena);
void temp_arena_end(Temp_Arena* temp_arena);

#define push_arr(arena, T, cnt) ( (T*) arena_alloc_align((arena), sizeof(T) * (cnt), sizeof(T)) )

#endif /* BASE_MEMORY_H */
