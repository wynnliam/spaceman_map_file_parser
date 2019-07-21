// Liam Wynn, 7/20/2019, Spaceman Engine Level Loading

#include "./utilities.h"

#include <string.h>
#include <stdlib.h>

char* remove_comment_from_string(char* str) {
	if(!str)
		return NULL;

	int len = strlen(str);
	char* result;

	// The length of the character must support two " characters,
	// And the first and last characters must be ".
	if(len >= 2 && str[0] == '"' && str[len - 1] == '"') {
		// Length of the resulting string is two less than the given string
		// plus 1, since we need a \0. So the length is len - 2 + 1 = len - 1.
		result = (char*)malloc(len - 1);

		int i;
		for(i = 1; i < len - 1; i++)
			result[i - 1] = str[i];

		result[i] = '\0';
	} else
		result = NULL;

	return result;
}
