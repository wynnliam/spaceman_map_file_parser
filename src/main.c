#include <stdio.h>

#include "./parser/parser.h"
#include <string.h>

int main() {
	const char* file_path = "./bin/c01.sqm";
	char* next_token = NULL;

	open_file_for_tokenizing(file_path);

	do {
		next_token = read_next_token();
		if(next_token)
			printf("%s\n", next_token);
	} while(next_token != NULL);

	close_token_file();

	return 0;
}
