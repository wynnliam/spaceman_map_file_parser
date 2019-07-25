#include <stdio.h>
#include <stdlib.h>

#include "./map_loading/tokenizer/tokenizer.h"
#include "./map_loading/parser/parser.h"
#include "./map_loading/ir/intermediate_mapdef.h"

int main() {
	// TODO: Standardize texture list
	struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);

	struct intermediate_mapdef* intermediate_mapdef = construct_intermediate_mapdef(map_tree);

	print_token_list(tokens);
	printf("\n");
	print_recipe_list(map_tree, 0);
	/*printf("\n");
	print_texture_list(texture_list);
	printf("\n");
	print_thing_list(thing_list);
	printf("\n");
	print_component_list(components);*/

	clean_token_list(tokens);
	clean_recipe_list(map_tree);
	clean_intermediate_mapdef(intermediate_mapdef);

	return 0;
}
