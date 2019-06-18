#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include "./parser/tokenizer.h"
#include <string.h>

int main() {
	struct token_list* tokens = get_tokens("./bin/c01.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);

	print_recipe_list(map_tree, 0);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);

	return 0;
}
