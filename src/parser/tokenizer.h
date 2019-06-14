// Liam Wynn, 6/11/2019, Spaceman Engine Level Loading

struct token {
	char* symbol;
	int type;
};

int open_file_for_tokenizing(const char* file_path);
int close_token_file();

int read_next_token(struct token* t);
