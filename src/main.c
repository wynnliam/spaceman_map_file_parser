#include <stdio.h>
#include <stdlib.h>

#include "./map_loading/tokenizer/tokenizer.h"
#include "./map_loading/parser/parser.h"
#include "./map_loading/ir/texture_list.h"
#include "./map_loading/ir/thing_list.h"
#include "./map_loading/ir/component_list.h"

int main() {
	// TODO: Standardize texture list
	struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);
	struct thing_list* thing_list = build_thing_list_from_map_tree(map_tree);
	struct texture_list* texture_list = construct_texture_list();
	struct component_list* components;
	
	build_texture_list_from_map_tree(map_tree, texture_list);

	components = build_component_list_from_recipe_list_and_texture_list(map_tree, texture_list);

	print_recipe_list(map_tree, 0);
	printf("\n");
	print_texture_list(texture_list);
	printf("\n");
	print_thing_list(thing_list);
	printf("\n");
	print_component_list(components);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);
	clean_thing_list(thing_list);
	clean_component_list(components);

	clear_texture_list(texture_list);
	free(texture_list);
	return 0;
}
