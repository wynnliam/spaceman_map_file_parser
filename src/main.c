#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include "./parser/texture_list.h"
#include "./parser/thing_list.h"

int main() {
	/*struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);
	struct texture_list* texture_list = construct_texture_list();

	//print_recipe_list(map_tree, 0);

	build_texture_list_from_map_tree(map_tree, texture_list);
	print_texture_list(texture_list);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);
	clear_texture_list(texture_list);
	free(texture_list);*/

	struct thinglist_data* thing_data = construct_thinglist_data("./src/assests/sprites/sculptures/king_rock.bmp",
																 0,
																 1120, 640,
																 90);

	print_thinglist_data(thing_data);
	clean_thinglist_data(thing_data);

	return 0;
}
