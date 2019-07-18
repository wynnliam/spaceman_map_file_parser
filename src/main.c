#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include "./parser/tokenizer.h"
#include <string.h>

int main() {
	struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);
	struct texture_list* texture_list = construct_texture_list();

	//print_recipe_list(map_tree, 0);

	build_texture_list_from_map_tree(map_tree, texture_list);
	print_texture_list(texture_list);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);

	/*struct texlist_data* data1 = construct_texlist_data(NULL, "./floor_wood_1.bmp", 0);
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
	free(list);*/

	/*struct attribute_list* list = construct_attribute_list();
	insert_attribute_into_list(construct_attribute("n 1", "v 1"), list);
	insert_attribute_into_list(construct_attribute("n 2", "v 2"), list);
	insert_attribute_into_list(construct_attribute("n 3", "v 3"), list);
	insert_attribute_into_list(construct_attribute("n 4", "v 4"), list);
	insert_attribute_into_list(construct_attribute("n 5", "v 5"), list);

	char* val = get_attribute_value(list, "n 3");

	if(val) {
		printf("%s\n", val);
		free(val);
	}

	clean_attribute_list(list);*/

	return 0;
}
