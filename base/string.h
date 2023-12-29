#ifndef BASE_STRING_H
#define BASE_STRING_H

// str8 helpers

#include "types.h"
#include "memory.h"

// Str8 constructors
str8 str8_from_str(u8* str, usize size);
str8 str8_from_range(u8* first, u8* last);
str8 str8_from_cstr(u8* str);
#define str8_from_literal(s) ( str8_from_str((u8*)(s), sizeof(s) - 1) )

// Str8 helpers
i8 str8_eql(str8 a, str8 b);
i8 str8str8(str8 haystack, str8 needle);
i8 str8chr(str8 haystack, u8 needle);
str8 str8cpy(Arena* arena, str8 str);
usize str8_count(str8 haystack, str8 needle);
void str8list_push(str8list* list, str8 string, str8node* node);
str8 str8list_join(Arena* arena, str8list* list, str8 separator);
str8list str8_split_any(Arena* arena, str8 str, str8 delim);

// Format string helpers
str8 str8_fmtv(Arena* arena, char* fmt, va_list args);
str8 str8_fmt(Arena* arena, char* fmt, ...);

// Unicode functions
utfdecode str8_decode_utf8(str8 str);
usize str_encode_utf8(u8* dest, u32 codepoint);

#endif /* BASE_STRING_H */
