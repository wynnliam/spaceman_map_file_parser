#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include <string.h>

int main() {
	const char* file_path = "./bin/map.sqm";

	struct token* curr_token;
	struct token_list* token_list = construct_token_list();

	open_file_for_tokenizing(file_path);

	do {
		curr_token = (struct token*)malloc(sizeof(struct token));

		if(read_next_token(curr_token)) {
			if(curr_token->symbol) {
				insert_token_into_list(curr_token, token_list);
			}
		} else {
			break;
		}
	} while(1);

	print_token_list(token_list);

	close_token_file();

	return 0;
}
