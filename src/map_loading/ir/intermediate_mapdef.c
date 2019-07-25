// Liam Wynn, 7/24/2019, Spaceman Engine Level Loading

#include "intermediate_mapdef.h"

#include <stdlib.h>

struct intermediate_mapdef* construct_intermediate_mapdef(struct recipe_list* map_tree) {
	if(!map_tree)
		return NULL;

	struct intermediate_mapdef* result = (struct intermediate_mapdef*)malloc(sizeof(struct intermediate_mapdef));

	result->textures = construct_texture_list();
	build_texture_list_from_map_tree(map_tree, result->textures);

	result->things = build_thing_list_from_map_tree(map_tree);

	result->components = build_component_list_from_recipe_list_and_texture_list(map_tree, result->textures);

	return result;
}

