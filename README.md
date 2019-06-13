# Spaceman Map File Parser
A temporary home for the reworked map loading system for the Spaceman Raycaster Engine.

## Intro
Essentially, this is an effort to rewrite the map loading system in the current raycasting
engine. The original loader set out to do two things, initally:

* Allow users to create and test levels without having to recompile the raycaster.
* Have these levels be in a relatively human readable format.

Reaching these goals culminated in a very simple file format called the "Squanto Map File",
or "sqm" for short. I won't go into too much detail, but it was great for levels with no
interactions or anything, other than to just walk around.

However, the scope of my raycasting engine as since grown, and the parser is no longer
sufficient. Thus, I've undertaken an endeavor to rewrite it. This project is and will be
the result of that effort.

## Background

### The Squanto Map File and Old Parser
The Squanto Map File (sqm) is the human readable format for maps in the raycasting engine.
The format is rougly inspired by the [Valve Map Format](https://developer.valvesoftware.com/wiki/Valve_Map_Format).
Basically, the file format is a collection of what I call "recipes" that take the form of:

```
recipe {
	attribute = "value";

	attribute_2 = "value";

	attribute_3 = "value";
	...
}
```

There are currently three recipe types:

* properties: specifies general information about the map. This includes:
	- Map name
	- Sky texture
	- Fog presence and fog color

* component: A rectangular block of geometry. These would be walls or floor/ceiling pairs.
For a floor/ceiling pair, you can omit either the floor or ceiling (or both) textures to
create parts of the level that are outdoorsy.

* thing: A prop or spawn point in the map.

So an example level may look like:

```
properties {
	name = "Francisco Leopold Art Gallery";
	sky_tex = "./src/assests/textures/skybox/sky01.bmp";

	use_fog = "1";
	fog_r = "255";
	fog_g = "0";
	fog_b = "0";
}

thing {
	type = "0";
	x = "2712";
	y = "1048";
	rot = "90";

	anim_class = "0";
	sprite_sheet = "0";
}

component {
	x = "3";
	y = "3";
	w = "18";
	h = "2";

	is_floor_ciel = "1";
	tex_0 = "./src/assests/textures/baroque/carpet1.bmp";
	tex_1 = "./src/assests/textures/baroque/ceiling1.bmp";
}
```

This format works great for maps with few things to do besides walk around. Currently,
one cannot specify relationships between recipes. For example, you might want an area
in the level where something happens when the user walks over that. Not only is this
kind of interaction not coded in the base engine, it cannot be represented in the file format.
Theoretically, you could represent a space that triggers something by having something like:

```
entity {
	type = "trigger";

	component {
		x = "3";
		y = "3";
		w = "18";
		h = "2";

		is_floor_ciel = "1";
		tex_0 = "./src/assests/textures/baroque/carpet1.bmp";
		tex_1 = "./src/assests/textures/baroque/ceiling1.bmp";
	}
}
```

In this case, we have a non-existant "entity" recipe. More importantly, we have a recipe *within* another
recipe. Without these relationships, maps can only do so much. Hence, my goal is to rewrite
the parser to handle such relationships.

### Level Loading as a Program Compiling Process
I decided to take a cue from programming languages, and treat the level loader as a compiler/interpreter.
In compiler theory, there are a few key steps. I'll only list the ones relevent to level loading:

* Input: a .sqm file.
* Tokenizing - Take the sqm file, strip away all comments and uneccessary white space, and
produce a list of "tokens".
* Parser - Given the list of tokens, turn these into a tree-like representation of the level.
* Intepreter - Take the tree-like representation, and turn it into a mapdef.
* Output: a mapdef struct for the raycasting engine.
