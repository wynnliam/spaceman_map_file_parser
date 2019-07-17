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
	struct texlist_data* data1 = construct_texlist_data(NULL, "./floor_wood_1.bmp", 0);
	struct texlist_data* data2 = construct_texlist_data(NULL, "./floor_wood_2.bmp", 1);
	struct texlist_data* data3 = construct_texlist_data(NULL, "./floor_wood_3.bmp", 0);
	struct texlist_data* data4 = construct_texlist_data(NULL, "./floor_wood_4.bmp", 1);
	struct texlist_data* data5 = construct_texlist_data(NULL, "./floor_wood_5.bmp", 0);

	struct texture_list* list = construct_texture_list();
	insert_texture_into_texture_list(list, data1);
	insert_texture_into_texture_list(list, data2);
	insert_texture_into_texture_list(list, data3);
	insert_texture_into_texture_list(list, data4);
	insert_texture_into_texture_list(list, data5);

	print_texture_list(list);
	clear_texture_list(list);
	free(list);

	return 0;
}
