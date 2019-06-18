// Liam Wynn, 6/7/2019, Spaceman Engine Level Loading

#include "./parser.h"

#include <stdlib.h>
#include <stdio.h>

// Returns 1 if curr is the start of a recipe name
// (IE: a name followed by a open curly bracket)
static int is_recipe(struct token_list_node* curr);
static int is_recipe_end(struct token_list_node* curr);
static int is_attribute(struct token_list_node* curr);

struct recipe_list* build_map_tree(struct token_list* tokens) {
	if(!tokens || !tokens->tail)
		return NULL;

	// Begin by breaking the token list into a simple linear linked list.
	struct token_list_node* head = tokens->tail->next;
	// Use this to walk the list.
	struct token_list_node* curr = head;
	tokens->tail->next = NULL;

	while(curr) {
		if(is_recipe(curr)) {
			printf("%s %s\n", curr->token->symbol, curr->next->token->symbol);
			curr = curr->next->next;
		} else if(is_recipe_end(curr)) {
			printf("%s\n", curr->token->symbol);
			curr = curr->next;
		} else if(is_attribute(curr)) {
			printf("%s %s %s %s\n", curr->token->symbol,
									curr->next->token->symbol,
									curr->next->next->token->symbol,
									curr->next->next->next->token->symbol);
			curr = curr->next->next->next->next;
		} else {
			curr = curr->next;
		}
	}

	// Reconnect the list.
	tokens->tail->next = head;

	return NULL;
}

int is_recipe(struct token_list_node* curr) {
	if(!curr || !curr->next)
		return 0;

	return curr->token->type == TOKEN_NAME && curr->next->token->type == TOKEN_OPEN_CURL;
}

static int is_recipe_end(struct token_list_node* curr) {
	if(!curr)
		return 0;

	return curr->token->type == TOKEN_CLOSE_CURL;
}

static int is_attribute(struct token_list_node* curr) {
	if(!curr || !curr->next || !curr->next->next || !curr->next->next->next)
		return 0;

	return curr->token->type == TOKEN_NAME &&
		   curr->next->token->type == TOKEN_EQUAL &&
		   curr->next->next->token->type == TOKEN_ATTR &&
		   curr->next->next->next->token->type == TOKEN_SEMI;
}
