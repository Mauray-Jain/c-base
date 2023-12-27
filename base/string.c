#include "string.h"

str8 str8_from_str(u8* str, usize len){
	str8 ret = {str, len};
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

i8 str8_eql(str8 a, str8 b){
	if (a.len != b.len) return 0;
	if (a.str == b.str) return 1;
	for (usize i = 0; i < a.len; i++) {
		if (a.str[i] != b.str[i]) {
			return 0;
		}
	}
	return 1;
}

i8 str8str8(str8 haystack, str8 needle){
	if (needle.len > haystack.len) {
		return 0;
	} else if (needle.len == haystack.len) {
		return str8_eql(haystack, needle);
	} else {
		for (usize i = 0; i <= haystack.len - needle.len; i++) {
			str8 slice = {0};
			slice.len = needle.len;
			slice.str = &haystack.str[i];
			if (str8_eql(slice, needle)) return 1;
		}
		return 0;
	}
}

i8 str8chr(str8 haystack, u8 needle){
	for (usize i = 0; i <= haystack.len; i++) {
		if (haystack.str[i] == needle) return 1;
	}
	return 0;
}

usize str8_count(str8 haystack, str8 needle){
	if (needle.len > haystack.len) {
		return 0;
	} else if (needle.len == haystack.len) {
		return str8_eql(haystack, needle);
	} else {
		usize cnt = 0;
		for (usize i = 0; i <= haystack.len - needle.len; i++) {
			str8 slice = {0};
			slice.len = needle.len;
			slice.str = &haystack.str[i];
			cnt += str8_eql(slice, needle);
		}
		return cnt;
	}
}

void str8list_push(str8list* list, str8 str, str8node* node){
	node->string = str;
	SLLStackPush(list->first, list->last, node);
	list->total_len += node->string.len;
	list->node_count++;
}

str8 str8list_join(Arena* arena, str8list* list, str8 separator){
	usize size = list->total_len + separator.len * (list->node_count - 1);
	u8* str = push_arr(arena, u8, size + 1);
	u8* ptr = str;
	i8 is_mid = 0;

	for (str8node* node = list->first; node != NULL; node = node->next) {
		if (is_mid) {
			MemoryCopy(ptr, separator.str, separator.len);
			ptr += separator.len;
		}
		MemoryCopy(ptr, node->string.str, node->string.len);
		ptr += node->string.len;
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
	list.total_len = 0;
	u8* ptr = str.str;
	u8* word_start = ptr;
	u8* last = str.str + str.len;
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
