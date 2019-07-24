// Liam Wynn, 7/24/2019, Spaceman Engine Level Loading

#ifndef COMPONENT_LIST
#define COMPONENT_LIST

struct recipe_list;

// A rectangular group of tiles
struct component {
	// Used to denote the tile texture we have.
	// If no texture, we assume it is texture 0.
	unsigned int tex_id;

	unsigned int x, y, w, h;
};
#endif

