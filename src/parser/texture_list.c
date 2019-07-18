// Liam Wynn, 6/24/2019, Spaceman Engine Level Loading

#include "./texture_list.h"
#include "./recipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct texlist_data* construct_texlist_data(const char* tex_0, const char* tex_1, int is_floor_ceil_pair) {
	struct texlist_data* result = (struct texlist_data*)malloc(sizeof(struct texlist_data));

	if(!tex_0) {
		result->tex_0 = NULL;
	} else {
		result->tex_0 = (char*)malloc(strlen(tex_0) + 1);
		strcpy(result->tex_0, tex_0);
	}

	if(!tex_1) {
		result->tex_1 = NULL;
	} else {
		result->tex_1 = (char*)malloc(strlen(tex_1) + 1);
		strcpy(result->tex_1, tex_1);
	}

	result->is_floor_ceil_pair = is_floor_ceil_pair;

	return result;
}

int texlist_data_equals(struct texlist_data* a, struct texlist_data* b) {
	if(!a || !b)
		return a == b;

	int tex_0_cmp;
	int tex_1_cmp;

	if(!a->tex_0 || !b->tex_0)
		tex_0_cmp = a->tex_0 == b->tex_0;
	else
		tex_0_cmp = strcmp(a->tex_0, b->tex_0) == 0;

	if(!a->tex_1 || !b->tex_1)
		tex_1_cmp = a->tex_1 == b->tex_1;
	else
		tex_1_cmp = strcmp(a->tex_1, b->tex_1) == 0;

	return tex_0_cmp && tex_1_cmp && (a->is_floor_ceil_pair == b->is_floor_ceil_pair);
}

void clean_textlist_data(struct texlist_data* to_clean) {
	if(!to_clean)
		return;

	if(to_clean->tex_0) {
		free(to_clean->tex_0);
		to_clean->tex_0 = NULL;
	}

	if(to_clean->tex_1) {
		free(to_clean->tex_1);
		to_clean->tex_1 = NULL;
	}

	free(to_clean);
}

void print_texlist_data(struct texlist_data* data) {
	if(!data)
		return;

	printf("tex_0: %s\n", data->tex_0 ? data->tex_0 : "0");
	printf("tex_1: %s\n", data->tex_1 ? data->tex_1 : "0");
	printf("Is floor/ceiling pair: %s\n", data->is_floor_ceil_pair ? "True" : "False");
}

struct texlist_node* construct_texlist_node(struct texlist_data* data) {
	if(!data)
		return NULL;

	struct texlist_node* result = (struct texlist_node*)malloc(sizeof(struct texlist_node));

	result->data = data;
	result->next = NULL;

	return result;
}

struct texture_list* construct_texture_list() {
	struct texture_list* result = (struct texture_list*)malloc(sizeof(struct texture_list));

	result->head = NULL;

	return result;
}

int insert_texture_into_texture_list(struct texture_list* list, struct texlist_data* data) {
	if(!data)
		return 0;

	struct texlist_node* temp = construct_texlist_node(data);
	temp->next = list->head;
	list->head = temp;

	return 1;
}

void clear_texture_list(struct texture_list* list) {
	if(!list)
		return;

	struct texlist_node* curr;
	struct texlist_node* temp;

	curr = list->head;
	while(curr) {
		temp = curr->next;
		clean_textlist_data(curr->data);
		free(curr);
		curr = temp;
	}
}

void print_texture_list(struct texture_list* list) {
	if(!list)
		return;

	struct texlist_node* curr = list->head;
	while(curr) {
		print_texlist_data(curr->data);
		curr = curr->next;
	}
}

int texture_list_contains(struct texture_list* list, struct texlist_data* to_find) {
	if(!list || !to_find)
		return 0;

	int result = 0;
	struct texlist_node* curr = list->head;

	while(curr) {
		if(texlist_data_equals(curr->data, to_find)) {
			result = 1;
			break;
		}

		curr = curr->next;
	}

	return result;
}

int build_texture_list_from_map_tree(struct recipe_list* map_tree, struct texture_list* result) {
	if(!map_tree || !map_tree->head || !result)
		return 0;

	struct recipe* curr_recipe = map_tree->head->recipe;
	struct recipe_list* sub_recipes = curr_recipe->subrecipes;

	// If curr_recipe is a component recipe, then these values are 
	char* attr_tex_0;
	char* attr_tex_1;
	char* attr_is_floor_ceil_pair;
	struct texlist_data* texture_data;

	if(strcmp(curr_recipe->type, "component") == 0) {
		texture_data = (struct texlist_data*)malloc(sizeof(struct texlist_data));

		attr_tex_0 = get_attribute_value(curr_recipe->attributes, "tex_0");
		attr_tex_1 = get_attribute_value(curr_recipe->attributes, "tex_1");
		attr_is_floor_ceil_pair = get_attribute_value(curr_recipe->attributes, "is_floor_ciel");

		if(attr_tex_0)
			texture_data->tex_0 = attr_tex_0;
		else
			texture_data->tex_0 = "0";

		if(attr_tex_1)
			texture_data->tex_1 = attr_tex_1;
		else
			texture_data->tex_1 = "0";

		if(attr_is_floor_ceil_pair && strcmp(attr_is_floor_ceil_pair, "\"1\"") == 0)
			texture_data->is_floor_ceil_pair = 1;
		else
			texture_data->is_floor_ceil_pair = 0;

		if(!texture_list_contains(result, texture_data))
			insert_texture_into_texture_list(result, texture_data);
	}

	struct recipe_list dummy;
	dummy.head = map_tree->head->next;

	return build_texture_list_from_map_tree(sub_recipes, result) +
		   build_texture_list_from_map_tree(&dummy, result);
}
