#include <stdio.h>
#include <stdlib.h>

#include "./map_loading/tokenizer/tokenizer.h"
#include "./map_loading/parser/parser.h"
#include "./map_loading/ir/texture_list.h"
#include "./map_loading/ir/thing_list.h"
#include "./map_loading/ir/component_list.h"

int main() {
	struct component_list* list = construct_component_list();

	insert_component_into_list(list, construct_component(0, 23, 72, 1, 1));
	insert_component_into_list(list, construct_component(1, 23, 74, 1, 1));
	insert_component_into_list(list, construct_component(2, 23, 76, 1, 1));
	insert_component_into_list(list, construct_component(3, 23, 78, 1, 1));

	print_component_list(list);

	clean_component_list(list);
	// TODO: Standardize texture list
	/*struct token_list* tokens = get_tokens("./bin/c02.sqm");
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

	clear_texture_list(texture_list);
	free(texture_list);*/
	return 0;
}
