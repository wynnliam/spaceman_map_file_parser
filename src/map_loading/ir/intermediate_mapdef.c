// Liam Wynn, 7/24/2019, Spaceman Engine Level Loading

#include "intermediate_mapdef.h"

#include <stdlib.h>

struct intermediate_mapdef* construct_intermediate_mapdef(struct recipe_list* map_tree) {
	if(!map_tree)
		return NULL;

	struct intermediate_mapdef* result = (struct intermediate_mapdef*)malloc(sizeof(struct intermediate_mapdef));

	// ...

	return result;
}

