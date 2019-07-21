#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include "./parser/texture_list.h"
#include "./parser/thing_list.h"
#include "./parser/utilities.h"

int main() {
	char* dummy = "\"a\"";
	char* dummy_no_quotes = remove_comment_from_string(dummy);

	if(dummy_no_quotes) {
		printf("Given: %s\nResult: %s\n", dummy, dummy_no_quotes);
	} else
		printf("Invalid quotes\n");

	/*struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);
	struct texture_list* texture_list = construct_texture_list();

	print_recipe_list(map_tree, 0);

	//build_texture_list_from_map_tree(map_tree, texture_list);
	//print_texture_list(texture_list);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);
	clear_texture_list(texture_list);
	free(texture_list);*/

	/*struct thinglist_data* thing_data = construct_thinglist_data(NULL, 0, 1120, 640, 90);
	struct thinglist_data* thing_data_2 = construct_thinglist_data("www", 0, 1120, 640, 90);

	if(thinglist_data_equals(thing_data, thing_data_2))
		printf("True!\n");
	else
		printf("False!\n");*/

	return 0;
}
