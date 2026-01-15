#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
	Spec1:
		it must be able to set the floor and ceiling colors to two different ones.
	Spec2:
		it displays the images to the window following these rules:
			Rule1:The left/right keys must allow the player look left/right in the maze.
			Rule2:The W, A,
				S,D keys must allow the player to move the opint of view through the maze.
			Rule3:Pressing ESC key must close the window and quit the program cleanly.
			Rule4:Clicking on the red cross must close the window and quit the program cleanly.
			Rule5:The use of images of minilibx is strongly recommended.
	Spec3:
		The map must be composed of only 6 possible characters:
			0:empty space.
			1:a wall.
			N:Players start position and spawning orientation.
			S:same.
			E:same.
			W:same.
	Spec4:
		The map must be closed/sorrounded by walls,
			if not the program must return an error.
	Spec5:
		Except for the map content,
			each type of element can be separated by one or more empty lines.
	Spec6:
		Except for the map,
			each type of information from an element can be separated by one or more spaces.
	Spec7:
		The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle.
	Spec8:
		Except for the map,
			each element must begin with its type identifier(composed by one or two characters),
			followed by its specific information in a strict order:
			North: NO ./path_to_the_north_texture
			South: SO ./path_to_the_south_texture
			West : WE ./path_to_the_west_texture
			East : EA ./path_to_the_east_texture
			Floor: F 220,100,0 [R,G,B]
			Ceil : C 225,30,0 [R,G,B]
*/
