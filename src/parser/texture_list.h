// Liam Wynn, 6/24/2019, Spaceman Engine Level Loading

#ifndef TEXTURE_LIST
#define TEXTURE_LIST

struct texlist_data {
	// These two values identify a texlist_data.
	// note that either of these (or both) can be NULL.
	char* tex_0;
	char* tex_1;

	// The id used in the mapdef to associate a
	// a number with a texture pair.
	unsigned int mapdef_id;
};

struct texlist_data* construct_texlist_data(const char* tex_0, const char* tex_1);

void print_texlist_data(struct texlist_data* data);
#endif

