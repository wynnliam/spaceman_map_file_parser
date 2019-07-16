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
	// Tells us if we should interpret this texture data as
	// a floor/ceil pair or just a wall. While two-texture walls
	// have no meaning, a floor/ceil pair can have zero, one, or
	// two textures. 0 means floor/ceiling pair, and not 0 means wall.

	// Quick note: this flag tells us *how* to interpret the two textures.
	// if a floor/ceil pair, then tex_0 is the floor texture, and tex_1 is
	// the ceil. In a wall, tex_1 has no meaning, and tex_0 is the wall texture.
	int is_floor_ceil_pair;
};

struct texlist_data* construct_texlist_data(const char* tex_0, const char* tex_1, int is_floor_ceil_pair);
void clean_textlist_data(struct texlist_data* to_clean);

void print_texlist_data(struct texlist_data* data);
#endif

