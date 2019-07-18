// Liam Wynn, 7/18/2019, Spaceman Engine Level Loading

#include "./thing_list.h"

#include <stdlib.h>
#include <string.h>

struct thinglist_data* construct_thinglist_data(const char* sprite_sheet, int anim_class, int x, int y, int rot) {
	struct thinglist_data* result = (struct thinglist_data*)malloc(sizeof(struct thinglist_data));

	if(!sprite_sheet)
		result->sprite_sheet = NULL;
	else {
		result->sprite_sheet = (char*)malloc(strlen(sprite_sheet) + 1);
		strcpy(result->sprite_sheet, sprite_sheet);
	}

	result->anim_class = anim_class;
	result->x = x;
	result->y = y;
	result->rot = rot;

	return result;
}

