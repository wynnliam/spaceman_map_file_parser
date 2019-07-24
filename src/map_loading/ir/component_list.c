// Liam Wynn, 7/24/2019, Spaceman Engine Level Loading

#include "./component_list.h"
#include "../parser/recipe.h"
#include "./texture_list.h"

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

struct component* construct_component_from_recipe_and_texture_list(struct recipe* recipe, struct texture_list* texture_list) {
	if(!recipe || !texture_list)
		return NULL;
	
	unsigned int tex_id;
	unsigned int x, y, w, h;

	char* x_attr = get_attribute_value(recipe->attributes, "x");
	char* y_attr = get_attribute_value(recipe->attributes, "y");
	char* w_attr = get_attribute_value(recipe->attributes, "w");
	char* h_attr = get_attribute_value(recipe->attributes, "h");

	struct texlist_data* component_texture_data = build_texlist_data_from_recipe(recipe);
	tex_id = find_mapdef_id(component_texture_data, texture_list);
	if(component_texture_data)
		clean_textlist_data(component_texture_data);

	if(x_attr) {
		x = (unsigned int)atoi(x_attr);
		free(x_attr);
	} else
		x = 0;

	if(y_attr) {
		y = (unsigned int)atoi(y_attr);
		free(y_attr);
	} else
		y = 0; 

	if(w_attr) {
		w = (unsigned int)atoi(w_attr);
		free(w_attr);
	} else
		w = 1;

	if(h_attr) {
		h = (unsigned int)atoi(h_attr);
		free(h_attr);
	} else
		h = 1;

	return construct_component(tex_id, x, y, w, h);
}

void clean_component(struct component* to_clean) {
	if(!to_clean)
		return;

	free(to_clean);
}

void print_component(struct component* to_print) {
	if(!to_print)
		return;

	printf("Texture ID: %u\n", to_print->tex_id);
	printf("Dimensions: { x: %u, y: %u, w: %u, h: %u }\n\n",
			to_print->x, to_print->y, to_print->w, to_print->h);
}
