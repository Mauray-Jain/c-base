#include "string.h"
#include <stdarg.h>
#include <stdio.h>

// Str8 constructors

str8 str8_from_str(u8* str, usize size){
	str8 ret = {str, size};
	return ret;
}

str8 str8_from_range(u8* first, u8* last){
	str8 ret = {first, (usize) (last - first)};
	return ret;
}

str8 str8_from_cstr(u8* str){
	u8* ptr = str;
	for (; *ptr != '\0'; ptr++);
	str8 ret = str8_from_range(str, ptr);
	return ret;
}

// Str8 helpers

i8 str8_eql(str8 a, str8 b){
	if (a.size != b.size) return 0;
	if (a.str == b.str) return 1;
	for (usize i = 0; i < a.size; i++) {
		if (a.str[i] != b.str[i]) {
			return 0;
		}
	}
	return 1;
}

i8 str8str8(str8 haystack, str8 needle){
	if (needle.size > haystack.size) {
		return 0;
	} else if (needle.size == haystack.size) {
		return str8_eql(haystack, needle);
	} else {
		for (usize i = 0; i <= haystack.size - needle.size; i++) {
			str8 slice = {0};
			slice.size = needle.size;
			slice.str = &haystack.str[i];
			if (str8_eql(slice, needle)) return 1;
		}
		return 0;
	}
}

i8 str8chr(str8 haystack, u8 needle){
	for (usize i = 0; i <= haystack.size; i++) {
		if (haystack.str[i] == needle) return 1;
	}
	return 0;
}

str8 str8cpy(Arena* arena, str8 str){
	u8* strcopy = push_arr(arena, u8, str.size);
	MemoryCopy(strcopy, str.str, str.size);
	str8 ret = {0};
	ret.size = str.size;
	ret.str = strcopy;
	ret.str[ret.size] = '\0';
	return ret;
}

usize str8_count(str8 haystack, str8 needle){
	if (needle.size > haystack.size) {
		return 0;
	} else if (needle.size == haystack.size) {
		return str8_eql(haystack, needle);
	} else {
		usize cnt = 0;
		for (usize i = 0; i <= haystack.size - needle.size; i++) {
			str8 slice = {0};
			slice.size = needle.size;
			slice.str = &haystack.str[i];
			cnt += str8_eql(slice, needle);
		}
		return cnt;
	}
}

void str8list_push(str8list* list, str8 str, str8node* node){
	node->string = str;
	SLLStackPush(list->first, list->last, node);
	list->total_size += node->string.size;
	list->node_count++;
}

str8 str8list_join(Arena* arena, str8list* list, str8 separator){
	usize size = list->total_size + separator.size * (list->node_count - 1);
	u8* str = push_arr(arena, u8, size + 1);
	u8* ptr = str;
	i8 is_mid = 0;

	for (str8node* node = list->first; node != NULL; node = node->next) {
		if (is_mid) {
			MemoryCopy(ptr, separator.str, separator.size);
			ptr += separator.size;
		}
		MemoryCopy(ptr, node->string.str, node->string.size);
		ptr += node->string.size;
		is_mid = 1;
	}
	*ptr = '\0';

	str8 ret = str8_from_str(str, size);
	return ret;
}

str8list str8_split_any(Arena* arena, str8 str, str8 delim){
	str8list list = {0};
	list.first = 0;
	list.last = 0;
	list.node_count = 0;
	list.total_size = 0;
	u8* ptr = str.str;
	u8* word_start = ptr;
	u8* last = str.str + str.size;
	for (;ptr < last; ptr++) {
		if (str8chr(delim, *ptr)) {
			str8node* node = push_arr(arena, str8node, 1);
			str8list_push(&list, str8_from_range(word_start, ptr), node);
			word_start = ptr + 1;
		}
	}
	// Extract the last one
	if (word_start < ptr) {
		str8node* node = push_arr(arena, str8node, 1);
		str8list_push(&list, str8_from_range(word_start, ptr), node);
		word_start = ptr + 1;
	}
	return list;
}

// Format string helpers

str8 str8_fmtv(Arena* arena, char* fmt, va_list args){
	va_list args2;
	va_copy(args2, args);
	usize buf_size = 1 + vsnprintf(NULL, 0, fmt, args);
	u8* str = push_arr(arena, u8, buf_size);
	vsnprintf((char*) str, buf_size, fmt, args2);
	va_end(args2);
	str8 ret = str8_from_str(str, buf_size - 1);
	return ret;
}

str8 str8_fmt(Arena* arena, char* fmt, ...){
	va_list args;
	va_start(args, fmt);
	str8 ret = str8_fmtv(arena, fmt, args);
	va_end(args);
	return ret;
}

// Unicode functions

// doesn't validate the sequence
utfdecode str8_decode_utf8(str8 str){ // str will be str8 with utf8 bytes
	utfdecode ret = {0};
	const u8 lengths[] = {
		1, 1, 1, 1, // 00000 - 00011
		1, 1, 1, 1, // 00100 - 00111
		1, 1, 1, 1, // 01000 - 01100
		1, 1, 1, 1, // 01101 - 01111
		0, 0, 0, 0, // 10000 - 10011
		0, 0, 0, 0, // 10100 - 10111
		2, 2, 2, 2, // 11000 - 11011
		3, 3,       // 11100 - 11101
		4,          // 11110
		0           // 11111
	};
	const i8 masks[] = {0x0, 0x7f, 0x1f, 0x0f, 0x07};
	const i8 final_shifts[] = {0, 18, 12, 6, 0};
	u8 byte = str.str[0];
	const u8 len = lengths[byte >> 3];
	ret.codepoint = 0x0;
	ret.size = 1;

	if (0 < len && len <= str.size) {
		u32 cp = (byte & masks[len]) << 18; // 6 * 3
		switch (len) {
			case 4: cp |= ((str.str[3] & 0x3f) << 0);  // fallthrough
			case 3: cp |= ((str.str[2] & 0x3f) << 6);  // fallthrough
			case 2: cp |= ((str.str[1] & 0x3f) << 12); // fallthrough
			default: break;
		}
		cp >>= final_shifts[len];
		ret.codepoint = cp;
		ret.size = len;
	}

	return ret;
}

usize str_encode_utf8(u8* dest, u32 codepoint){
	usize size = 0;
	if (codepoint < (1 << 8)) {
		dest[0] = (u8) codepoint;
		size = 1;
	} else if (codepoint < (1 << 11)) {
		dest[0] = 0xc0 | (codepoint >> 6);
		dest[1] = 0x80 | (codepoint & 0x3f);
		size = 2;
	} else if (codepoint < (1 << 16)) {
		dest[0] = 0xe0 | (codepoint >> 12);
		dest[1] = 0x80 | ((codepoint >> 6) & 0x3f);
		dest[2] = 0x80 | (codepoint & 0x3f);
		size = 3;
	} else if (codepoint < (1 << 21)) {
		dest[0] = 0xf0 | (codepoint >> 18);
		dest[1] = 0x80 | ((codepoint >> 12) & 0x3f);
		dest[2] = 0x80 | ((codepoint >>  6) & 0x3f);
		dest[3] = 0x80 | (codepoint & 0x3f);
		size = 4;
	} else {
		dest[0] = 0x0;
		size = 1;
	}
	return size;
}
