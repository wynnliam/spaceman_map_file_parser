// Liam Wynn, 7/24/2019, Spaceman Engine Level Loading

#include "./component_list.h"

#include <stdlib.h>
#include <stdio.h>

struct component* construct_component(unsigned int tex_id, unsigned int x, unsigned int y,
									  unsigned int w, unsigned int h) {
	struct component* result = (struct component*)malloc(sizeof(struct component));

	result->tex_id = tex_id;
	result->x = x;
	result->y = y;
	result->w = w;
	result->h = h;

	return result;
}

void print_component(struct component* to_print) {
	if(!to_print)
		return;

	printf("Texture ID: %u\n", to_print->tex_id);
	printf("Dimensions: { x: %u, y: %u, w: %u, h: %u }\n\n",
			to_print->x, to_print->y, to_print->w, to_print->h);
}
