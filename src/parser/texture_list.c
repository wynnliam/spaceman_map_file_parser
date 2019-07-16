// Liam Wynn, 6/24/2019, Spaceman Engine Level Loading

#include "./texture_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct texlist_data* construct_texlist_data(const char* tex_0, const char* tex_1, int is_floor_ceil_pair) {
	struct texlist_data* result = (struct texlist_data*)malloc(sizeof(struct texlist_data));

	if(!tex_0) {
		result->tex_0 = NULL;
	} else {
		result->tex_0 = (char*)malloc(strlen(tex_0) + 1);
		strcpy(result->tex_0, tex_0);
	}

	if(!tex_1) {
		result->tex_1 = NULL;
	} else {
		result->tex_1 = (char*)malloc(strlen(tex_1) + 1);
		strcpy(result->tex_1, tex_1);
	}

	result->mapdef_id = 0;
	result->is_floor_ceil_pair = is_floor_ceil_pair;

	return result;
}

void clean_textlist_data(struct texlist_data* to_clean) {
	if(!to_clean)
		return;

	if(to_clean->tex_0) {
		free(to_clean->tex_0);
		to_clean->tex_0 = NULL;
	}

	if(to_clean->tex_1) {
		free(to_clean->tex_1);
		to_clean->tex_1 = NULL;
	}

	free(to_clean);
}

void print_texlist_data(struct texlist_data* data) {
	if(!data)
		return;

	printf("Texture Id: %u\n", data->mapdef_id);
	printf("tex_0: %s\n", data->tex_0 ? data->tex_0 : "0");
	printf("tex_1: %s\n", data->tex_1 ? data->tex_1 : "0");
	printf("Is floor/ceiling pair: %s\n", data->is_floor_ceil_pair ? "True" : "False");
}
