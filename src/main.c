#include <stdio.h>
#include <stdlib.h>

#include "./parser/parser.h"
#include <string.h>

int main() {
	struct token_list* tokens = get_tokens("./bin/c01.sqm");
	print_token_list(tokens);
	clean_token_list(tokens);

	return 0;
}
