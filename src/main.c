#include <stdio.h>
#include <stdlib.h>

#include "./map_loading/tokenizer/tokenizer.h"
#include "./map_loading/parser/parser.h"
#include "./map_loading/ir/texture_list.h"
#include "./map_loading/ir/thing_list.h"
#include "./map_loading/ir/component_list.h"

int main() {
	/*struct component* component = construct_component(103, 11, 2, 1, 1);
	print_component(component);
	clean_component(component);*/

	// TODO: Standardize texture list
	struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);
	struct thing_list* thing_list = build_thing_list_from_map_tree(map_tree);
	struct texture_list* texture_list = construct_texture_list();
	struct texlist_data data;
	
	build_texture_list_from_map_tree(map_tree, texture_list);

	print_recipe_list(map_tree, 0);
	print_texture_list(texture_list);
	print_thing_list(thing_list);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);
	clean_thing_list(thing_list);

	/*struct recipe* recipe = construct_recipe(0, "component");
	insert_attribute_into_recipe(construct_attribute("tex_0", "./src/assests/textures/wall/temple_wall.bmp"), recipe);
	insert_attribute_into_recipe(construct_attribute("tex_1", "0"), recipe);
	insert_attribute_into_recipe(construct_attribute("is_floor_ciel", 0), recipe);
	insert_attribute_into_recipe(construct_attribute("x", "7"), recipe);
	insert_attribute_into_recipe(construct_attribute("y", "13"), recipe);
	insert_attribute_into_recipe(construct_attribute("w", "14"), recipe);
	insert_attribute_into_recipe(construct_attribute("h", "1"), recipe);

	struct component* component = construct_component_from_recipe_and_texture_list(recipe, texture_list);
	print_component(component);

	clean_recipe(recipe);
	clean_component(component);*/

	clear_texture_list(texture_list);
	free(texture_list);

	return 0;
}
