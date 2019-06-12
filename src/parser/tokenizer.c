// Liam Wynn, 6/11/2019, Spaceman Engine Level Loading

#include "./tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_NONE			0
#define TOKEN_NAME			1
#define TOKEN_ATTR			2
#define TOKEN_OPEN_CURL		3
#define TOKEN_CLOSE_CURL	4
#define TOKEN_EQUAL			5
#define TOKEN_SEMI			6

static FILE* map_file = NULL;

static int get_token_type(int c);

static int is_whitespace(int c);
static int is_end_of_line(int c);
static int is_start_of_comment(int c);

static int is_alphabetic(int c);
static int is_numeric(int c);

int open_file_for_tokenizing(const char* file_path) {
	if(!file_path || map_file)
		return 0;

	map_file = fopen(file_path, "r");

	if(!map_file)
		return 0;

	return 1;
}

int close_token_file() {
	if(!map_file)
		return 0;

	fclose(map_file);
	map_file = NULL;

	return 1;
}

char* read_next_token() {
	char curr;
	char* result = NULL;
	char buffer[10000];
	unsigned int buffer_index;

	do {
		curr = getc(map_file);

		if(curr == EOF)
			break;

		// In this case, we discard the character.
		if(is_whitespace(curr) || is_end_of_line(curr))
			continue;
		// In this case, we discard the entire line
		else if(is_start_of_comment(curr)) {
			while(curr != '\n')
				curr = getc(map_file);
		} else {
			switch(get_token_type(curr)) {
				// TODO: copy and return
				case TOKEN_NAME:
					buffer_index = 0;
					while(is_alphabetic(curr) || curr == '_' || is_numeric(curr)) {
						buffer[buffer_index] = curr;
						buffer_index++;
						curr = getc(map_file);
					}

					buffer[buffer_index] = '\0';
					result = (char*)malloc(strlen(buffer) + 1);
					strcpy(result, buffer);

					return result;

				case TOKEN_ATTR:
					buffer[0] = '"';
					buffer_index = 1;

					do {
						curr = getc(map_file);
						buffer[buffer_index] = curr;
						buffer_index++;
					} while(curr != '"');

					buffer[buffer_index] = '\0';
					result = (char*)malloc(strlen(buffer) + 1);
					strcpy(result, buffer);

					return result;

				case TOKEN_OPEN_CURL:
					result = (char*)malloc(strlen("{") + 1);
					strcpy(result, "{");
					return result;

				case TOKEN_CLOSE_CURL:
					result = (char*)malloc(strlen("}") + 1);
					strcpy(result, "}");
					return result;

				case TOKEN_EQUAL:
					result = (char*)malloc(strlen("=") + 1);
					strcpy(result, "=");
					return result;

				case TOKEN_SEMI:
					result = (char*)malloc(strlen(";") + 1);
					strcpy(result, ";");
					return result;

				default:
					printf("%c\n", curr);
					return "";
			}
		}

	} while(1);

	return result;
}

static int get_token_type(int c) {
	if(is_alphabetic(c) || c == '_' || is_numeric(c))
		return TOKEN_NAME;
	else if(c == '"')
		return TOKEN_ATTR;
	else if(c == '{')
		return TOKEN_OPEN_CURL;
	else if(c == '}')
		return TOKEN_CLOSE_CURL;
	else if(c == '=')
		return TOKEN_EQUAL;
	else if(c == ';')
		return TOKEN_SEMI;
	else
		return TOKEN_NONE;
}

int is_whitespace(int c) {
	return (c != 0 && c != 10 && (c < 33 || c > 127));
}

int is_end_of_line(int c) {
	return c == '\n';
}

int is_start_of_comment(int c) {
	return c == '#';
}

int is_alphabetic(int c) {
	return (c >= 97 && c <= 122) || (c >= 65 && c <= 90);
}

int is_numeric(int c) {
	return (c >= 48 && c <= 57);
}
