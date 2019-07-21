// Liam Wynn, 7/18/2019, Spaceman Engine Level Loading

#include "./thing_list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int thinglist_data_equals(struct thinglist_data* a, struct thinglist_data* b) {
	int result;
	int sprite_sheet_cmp;

	if(!a || !b) {
		result = a == b;
	} else {
		if(a->sprite_sheet && b->sprite_sheet)
			sprite_sheet_cmp = strcmp(a->sprite_sheet, b->sprite_sheet) == 0;
		else
			sprite_sheet_cmp = a->sprite_sheet == b->sprite_sheet;

		result = sprite_sheet_cmp &&
				 a->x == b->x && a->y == b->y &&
				 a->rot == b->rot &&
				 a->anim_class == b->anim_class;
	}

	return result;
}

void clean_thinglist_data(struct thinglist_data* to_clean) {
	if(!to_clean)
		return;

	if(to_clean->sprite_sheet)
		free(to_clean->sprite_sheet);

	free(to_clean);
}

void print_thinglist_data(struct thinglist_data* to_print) {
	if(!to_print)
		return;

	if(to_print->sprite_sheet)
		printf("sprite sheed: %s\n", to_print->sprite_sheet);

	printf("anim class: %d\n", to_print->anim_class);
	printf("position: %d %d\n", to_print->x, to_print->y);
	printf("rotation: %d\n", to_print->rot);
}
