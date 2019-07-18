// Liam Wynn, 7/18/2019, Spaceman Engine Level Loading

#ifndef THING_LIST
#define THING_LIST

struct thinglist_data {
	char* sprite_sheet;

	int anim_class;
	int x, y;
	int rot;
};

struct thinglist_data* construct_thinglist_data(const char* sprite_sheet, int anim_class, int x, int y, int rot);
void print_thinglist_data(struct thinglist_data* to_print);

#endif

