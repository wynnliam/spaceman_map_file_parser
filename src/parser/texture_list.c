// Liam Wynn, 6/24/2019, Spaceman Engine Level Loading

#include "./texture_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct texlist_data* construct_texlist_data(const char* tex_0, const char* tex_1) {
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

	return result;
}

void print_texlist_data(struct texlist_data* data) {
	if(!data)
		return;

	printf("Texture Id: %u\n", data->mapdef_id);
	printf("tex_0: %s\n", data->tex_0 ? data->tex_0 : "0");
	printf("tex_1: %s\n", data->tex_1 ? data->tex_1 : "0");
}
