#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include "./parser/tokenizer.h"
#include <string.h>

int main() {
	/*struct token_list* tokens = get_tokens("./bin/map.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);

	print_recipe_list(map_tree, 0);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);*/

	// TODO: Clean
	struct texlist_data* data = construct_texlist_data(NULL, "./floor_wood_2.bmp", 0);

	print_texlist_data(data);
	clean_textlist_data(data);

	return 0;
}
