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

int read_next_token(struct token* t) {
	if(!t)
		return 0;

	char curr;
	char buffer[10000];
	unsigned int buffer_index;

	// This loop is neccessary since it will throw out multiple
	// junk symbols at a time (ie: comments and whitespace).
	// When we read a proper token, we break this loop.
	do {
		curr = getc(map_file);

		if(curr == EOF) {
			t->symbol = NULL;
			t->type = TOKEN_NONE;
			return 0;
		}

		// In this case, we discard the character.
		if(is_whitespace(curr) || is_end_of_line(curr))
			continue;
		// In this case, we discard the entire line
		else if(is_start_of_comment(curr)) {
			while(curr != '\n')
				curr = getc(map_file);
		} else {
			t->type = get_token_type(curr);
			switch(t->type) {
				case TOKEN_NAME:
					buffer_index = 0;
					while(is_alphabetic(curr) || curr == '_' || is_numeric(curr)) {
						buffer[buffer_index] = curr;
						buffer_index++;
						curr = getc(map_file);
					}

					buffer[buffer_index] = '\0';
					t->symbol = (char*)malloc(strlen(buffer) + 1);
					strcpy(t->symbol, buffer);

					return 1;

				case TOKEN_ATTR:
					buffer[0] = '"';
					buffer_index = 1;

					do {
						curr = getc(map_file);
						buffer[buffer_index] = curr;
						buffer_index++;
					} while(curr != '"');

					buffer[buffer_index] = '\0';
					t->symbol = (char*)malloc(strlen(buffer) + 1);
					strcpy(t->symbol, buffer);

					return 1;

				case TOKEN_OPEN_CURL:
					t->symbol = (char*)malloc(strlen("{") + 1);
					strcpy(t->symbol, "{");
					return 1;

				case TOKEN_CLOSE_CURL:
					t->symbol = (char*)malloc(strlen("}") + 1);
					strcpy(t->symbol, "}");
					return 1;

				case TOKEN_EQUAL:
					t->symbol = (char*)malloc(strlen("=") + 1);
					strcpy(t->symbol, "=");
					return 1;

				case TOKEN_SEMI:
					t->symbol = (char*)malloc(strlen(";") + 1);
					strcpy(t->symbol, ";");
					return 1;

				default:
					t->type = TOKEN_NONE;
					t->symbol = NULL;
					return 0;
			}
		}

	} while(1);

	return 1;
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
