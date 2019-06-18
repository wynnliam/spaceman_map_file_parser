// Liam Wynn, 6/11/2019, Spaceman Engine Level Loading

#ifndef MAP_LOAD_TOKENIZER
#define MAP_LOAD_TOKENIZER

struct token {
	char* symbol;
	int type;
};

struct token_list_node {
	struct token* token;
	struct token_list_node* next;
};

struct token_list {
	struct token_list_node* tail;
};

struct token_list* get_tokens(const char* file_path);
int clean_token_list(struct token_list* list);
void print_token_list(struct token_list* list);

#endif
