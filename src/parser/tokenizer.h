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

struct token_list* get_tokens(const char* file_path);

int open_file_for_tokenizing(const char* file_path);
int close_token_file();

int read_next_token(struct token* t);

struct token_list* construct_token_list();
int insert_token_into_list(struct token* token, struct token_list* list);
void print_token_list(struct token_list* list);
int clean_token_list(struct token_list* list);
