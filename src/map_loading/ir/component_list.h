// Liam Wynn, 7/24/2019, Spaceman Engine Level Loading

#ifndef COMPONENT_LIST
#define COMPONENT_LIST

struct recipe;
struct texture_list;

// A rectangular group of tiles
struct component {
	// Used to denote the tile texture we have.
	// If no texture, we assume it is texture 0.
	unsigned int tex_id;

	unsigned int x, y, w, h;
};

struct component* construct_component(unsigned int tex_id, unsigned int x, unsigned int y,
									  unsigned int w, unsigned int h);
struct component* construct_component_from_recipe_and_texture_list(struct recipe* recipe, struct texture_list* texture_list);
void clean_component(struct component* to_clean);
void print_component(struct component* to_print);
#endif

