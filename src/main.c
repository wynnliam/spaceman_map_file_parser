#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include <string.h>

int main() {
	const char* file_path = "./bin/map.sqm";
	struct token_list* tokens = get_tokens_from_file(file_path);
	/*struct token curr_token;

	open_file_for_tokenizing(file_path);

	do {
		if(read_next_token(&curr_token)) {
			if(curr_token.symbol) {
				printf("%d:\t%s\n", curr_token.type, curr_token.symbol);
				free(curr_token.symbol);
			}
		} else {
			break;
		}
	} while(1);

	close_token_file();*/

	return 0;
}
