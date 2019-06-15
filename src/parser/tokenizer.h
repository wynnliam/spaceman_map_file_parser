// Liam Wynn, 6/11/2019, Spaceman Engine Level Loading

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

struct token_list* get_tokens_from_file(const char* file_path);
