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
* Interpreter - Take the tree-like representation, and turn it into a mapdef.
* Output: a mapdef struct for the raycasting engine.

The next few sections will detail each of these steps. I think it's instructive to think of this program
as a translater between a human readable language and the language of a raycaster. By doing so, it solitifies
the overall theory of this system as a program compilation process.

### Program Steps:

#### 1. Input - An sqm File a human can read
We first begin by feeding the level loader with an sqm file. I've detailed this before, but I will go
into the format more so. Recall that a level is a set of recipes, and recipes have the format:

```
recipe {
	attribute = "value";
	attribute = "value";
	...
}
```

The main motivation of this system was to build levels with more expressive power. Rather than just a collection
of independent recipes, we could put recipes within recipes which connote a dependence on one recipe with another.
To achieve this, we'd have:

```
recipe {
	attribute = "value";
	attribute = "value";

	recipe {
		attribute = "value";
		attribute = "value";
	}

	...
}
```

To formally express this, we can construct a grammar, which is as follows:

```
Map -> RecipeList
RecipeList -> Recipe | Recipe RecipeList
Recipe -> Name { PropertyList }
PropertyList -> Property | Property PropertyList
Property -> Attribute | Recipe
Attribute -> Name = Value;
```

I won't cover this in too much detail here. If you want to know more, I'd suggest reading about
context free grammars.

#### 2. Tokenizing
As I stated in the previous section, our file format is described by a grammar. However, we don't
always have a perfect format. We get a text file with a series of characters. So before we can
do anything, we need a list of symbols. These symbols are going to be a strings of characters
that act as a single unit. The name for such a symbol is called a "token". So the first real step
to loading a level is to take a series of characters group them into a list of tokens. Take the
following recipe:

```
component {
	x = "3";
	y = "0";
	w = "1";
	h = "1";

	is_floor_ciel = "0";
	tex_0 = "./src/assests/textures/art/north_wing/art3b.bmp";
	tex_1 = "0";
}
```

We can think of this as:

```
N O
	N E A S
	N E A S
	N E A S
	N E A S


	N E A S
	N E A S
	N E A S
C
```

Where the letters mean as follows:

* N is a Name, which is a string of letters, underscores, and numbers
* O is an open curly bracket "{"
* E is an equal sign "="
* A is an "Attribute" which is just any string surrounded by quotation marks.
* S is a semicolon ";"
* C is a close curly bracket "}"

The point of tokenizing is to basically strip away comments and whitespace that
isn't relevent to getting the mapdef. Once we have the token list, we can
use the grammar to convert the list of symbols into a tree representation of our
map.

#### 3. Parsing
Once we've got a list of tokens, we can scan it to determine the tree-like representation
of the map. What do I mean by "tree-like representation"? Well first, a map is a list of
recipes, and these recipes may have sub recipes in them. So essentially, the map itself is
the root of this theoretical tree, and the highest level recipes (ie: recipes that are not
sub-recipes of other recipes) are the child nodes to this root node. The child nodes of these
recipes are their sub recipes, and so on. In this way, we create a tree-like structure of the
level that better represent the relationships between different parts of the level.

I will leave this fairly vague since, as of writing this (6-13-2019), this step and beyond have not
really been fleshed out. Once I do, I'll expound this section, and the subsequent ones.

#### 4. Interpreter
In the interpretation stage, we take our tree-like structure and generate a corresponding mapdef struct.

#### 5. Output - A mapdef struct the Raycaster can read.
Finally, we have a mapdef for use! I should mention that at this point, our final mapdef will depend highly
on the entities available in any particular game. For example, one game may have entities specific to it
(maybe say collectibles in an exploration game, or ammo in a shooter). Because of this, the way we handle
certain entities will be dependent on the game itself. If you want an entity to be an NPC of some kind, you
need to code that in for your game, and then tell the interpreter how to create that should it come up.

Again, as I start working on this part of the system, I will flesh it out more.
