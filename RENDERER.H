#ifndef RENDERER_H
#define RENDERER_H
/*
RENDERER.H

Print bitmap by using raster funtions
Passing coordinate to a function and print a certain bitmap
Some objects like wall, render_reset_button and storage location has fixed coordinate,
They will be only printed once in the game.

*/

#include "raster.h"
#include "model.h"

void render_splash(UINT8 *base);

/*
Fcuntion: render_walls

Purpose: Print all walls at certain coordinate

Input: 
		base - the screen
		
		walls[] - take the coordinate in each element in the ary and print them
		
*/
void render_walls(UINT32 *base, struct coordinate walls[]);


/*
Fcuntion: render_player

Purpose: Print the player at certain coordinate

Input: 
		base - the screen
		
		player - take the current coordinate and print the player on that coordinate
	
*/


void render_player(UINT32 *base, struct coordinate current);


/*
Fcuntion: render_reset_button

Purpose: Print the reset button at fixed coordinate

Input: 
		base - the screen
		
	coordinate current - a coordinate that reset button will be printed on the grid
	
*/
void render_reset_button(UINT32 *base, struct coordinate reset_button);


/*
Fcuntion: render_boxes

Purpose: Print all the boxes on the screen

Input: 
		base - the screen
		
		boxes[] - ary that contatins all the box coordinate 
				  this function will read each element and print
				  them to the corrdinate.
		
	
	
*/
void render_boxes(UINT32 *base, struct box boxes[]);

/*
Fcuntion: render_storage_locations

Purpose: Print all the storage locations on the screen

Input: 
		base - the screen
		
		storage_locations[] - take the coordinate in each and print a storage_locations on that coordinate
	
*/
void render_storage_locations(UINT32 *base, struct storage_location storage_locations[]);
/*
Fcuntion: render_clear_block

Purpose: Print a blank 32 x 32 gird to the given coordinate

Input: 
		base - the screen
		
		coordinate target - the coordinate block which will be clear.
	
*/
void render_clear_block(UINT32 *base, struct coordinate target);

/*
Fcuntion: render_box_t1

Purpose: Print a box to the given coordinate in the grid

Input: 
		base - the screen
		
		coordinate target - the coordinate block which will be print a box.
		
Detail: box_t1 indicate there is no storage_location.
	
*/
void render_box_t1(UINT32 *base, struct coordinate target);
/*
Fcuntion: render_box_t2

Purpose: Print a box to the given coordinate in the grid

Input: 
		base - the screen
		
		coordinate target - the coordinate block which will be print a box.
		
Detail: box_t2 indicate the box is convering a storage_location.
		using different bitmap to showes in the grid
*/
void render_box_t2(UINT32 *base, struct coordinate target);
/*
Fcuntion: render_storage_location

Purpose: Print a storage location to the given coordinate in the grid

Input: 
		base - the screen
		
		coordinate target - the coordinate block which will be print a box.
		
Detail: When a box is covering the storage location but is pushed out, the storage_location has to be print.
	
*/
void render_storage_location(UINT32 *base, struct coordinate target);

#endif
