#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include "./parser/texture_list.h"
#include "./parser/thing_list.h"

int main() {
	/*struct token_list* tokens = get_tokens("./bin/c02.sqm");
	struct recipe_list* map_tree = build_map_tree(tokens);
	//struct texture_list* texture_list = construct_texture_list();

	print_recipe_list(map_tree, 0);

	//build_texture_list_from_map_tree(map_tree, texture_list);
	//print_texture_list(texture_list);

	clean_token_list(tokens);
	clean_recipe_list(map_tree);
	//clear_texture_list(texture_list);
	//free(texture_list);*/

	/*struct thinglist_data* thing_data = construct_thinglist_data(NULL, 0, 1120, 640, 90);
	struct thinglist_data* thing_data_2 = construct_thinglist_data("www", 0, 1120, 640, 90);

	if(thinglist_data_equals(thing_data, thing_data_2))
		printf("True!\n");
	else
		printf("False!\n");*/

	/*struct recipe* recipe = construct_recipe(0, "thing");
	struct thinglist_data* thinglist_data;

	insert_attribute_into_recipe(construct_attribute("sprite_sheet", "./sprite_sheet.bmp"), recipe);
	insert_attribute_into_recipe(construct_attribute("anim_class", "0"), recipe);
	insert_attribute_into_recipe(construct_attribute("x", "1024"), recipe);
	insert_attribute_into_recipe(construct_attribute("y", "2048"), recipe);
	insert_attribute_into_recipe(construct_attribute("rot", "-93"), recipe);

	thinglist_data = thinglist_data_from_recipe(recipe);

	print_thinglist_data(thinglist_data);

	clean_recipe(recipe);
	clean_thinglist_data(thinglist_data);*/

	struct thing_list* list = construct_thing_list();

	insert_data_into_thing_list(list, construct_thinglist_data("./shee1.bmp", 0, 1024, 2048, -93));
	insert_data_into_thing_list(list, construct_thinglist_data("./shee2.bmp", 2, 1024, 2048, 0));
	insert_data_into_thing_list(list, construct_thinglist_data("./shee3.bmp", 1, 1024, 2048, 43));
	insert_data_into_thing_list(list, construct_thinglist_data("./shee4.bmp", 0, 1024, 2048, 22));

	print_thing_list(list);
	clean_thing_list(list);

	return 0;
}
