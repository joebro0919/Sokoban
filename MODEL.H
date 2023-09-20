#ifndef MODEL_H
#define MODEL_H

#define BLOCK_SIZE 32
#define GRID_SIZE 13
#define WALL_NUM 55
#define STORAGE_NUM 7
#define BOX_NUM 7
#define True 1
#define False 0

/*
MODEl.H

Contains all the objects struct and funtions which is used to modify or update all the objects.

*/
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

struct coordinate{
	int x;
	int y;
};

struct worker
{
	struct coordinate defaultPos;
	struct coordinate current;
	
};

struct box
{
   struct coordinate defaultPos;
   struct coordinate current;
};

/*
Struct : storage_location
int convered act like a bool type which 0 == false 1 == true.
*/
struct storage_location
{
	int covered;
	struct coordinate fixed;
};

struct redo_button
{
	struct coordinate fixed;
};

/*
Struct : block
int wall act like a bool type which 0 == false 1 == true.
*/
struct block
{
	int wall;
	struct storage_location *storage_location_ptr;
	struct box *box_ptr;
	struct worker *worker_ptr;
};

/*
Struct : models
which contains all the objects.
*/	
struct models
{
	struct coordinate walls[WALL_NUM];
	struct storage_location storage_locations[STORAGE_NUM];
	struct box boxes[BOX_NUM];
	struct worker player;
	struct coordinate reset_button;
};


/*
Fcuntion: load_grid_walls

Purpose:  Take each the wall corrdinate and input them in to 2d ary grid and set the block
		  wall to true.

Input:	
		walls[] - takes coordinate and load them to game_grid[][].
		
		game_grid[][] - set bool wall to true at the coordinate from wall[].
		
*/

void load_grid_walls(struct coordinate walls[], struct block gamegrid [GRID_SIZE][GRID_SIZE]);

/*
Fcuntion: load_boxes

Purpose:  Take each box corrdinate and input them in to 2d ary grid and set the box pointer in
		  the block point to the box specific element in the box ary

Input:	
		boxes[] - takes coordinate and load them to game_grid[][].
		
		game_grid[][] - set each box_ptr  points each element in the boxes[].
		
Details:
		Takes all the coordinate from boxes[] as the position on the 2d array game_grid then
		set box_ptr in that block points to specific element of the boxes[].

*/
void load_boxes(struct box boxes[], struct block gamegrid [GRID_SIZE][GRID_SIZE]);


/*
Fcuntion: load_storageLocations

Purpose:  Take each storage Locations corrdinate and input them in to 2d ary grid and set the storage Locations 
		  pointer in the block point to specific element in the storage_location ary

Input:	
		storage_locations[] - takes coordinate and load them to game_grid[][].
		
		game_grid[][] - set each storage_locations_ptr points each element storage_locations[].
		
Details:
		Takes all the coordinate from boxes[] as the position on the 2d array game_grid then
		set box_ptr in that block points to each of the boxes[].

*/
void load_storageLocations(struct storage_location storage_locations[], struct block gamegrid [GRID_SIZE][GRID_SIZE]);

/*
Fcuntion: load_player

Purpose:  Take each player corrdinate and input them in to 2d ary grid and set the player 
		  pointer in the block point to the player object

Input:	
		*player - takes coordinate and load them to game_grid[][].
		
		game_grid[][] - set the player_ptr points the player object
		
Details:
		Takes  the coordinate from player as the position on the 2d array game_grid then
		set player_ptr in that block points to the player object.

*/
void load_player(struct worker *player, struct block gamegrid [GRID_SIZE][GRID_SIZE]);
/*
Fcuntion: collision_check

Purpose:  A master function calls all the collision fcuntions

Input:	
		
		game_grid[][] - take target[1] coordinate and check for the collision
		
		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player will move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate
				   
		they all passes to other collision fcuntions
Output:
		
		if any collision return from other collision function then true
		else false.
				   

*/
int collision_check (struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]);

/*
Fcuntion: collision_wall

Purpose:  Check on the collision for wall after takes input from the player.

Input:	
		
		game_grid[][] - take target[1] coordinate and check for the collision
		
		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player will move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate
Output:
		
		if collision then true
		else false.
				   
Details:
		the game_grid takes the coordinate from target [1] and check if the block contains a wall, if so return collision is true
		else is false.
	
*/

int collision_wall(struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]);

/*
Fcuntion: collision_box

Purpose:  Check on the collision for boxes after takes input from the player.

Input:	
		
		game_grid[][] - take target[1] and target[2] coordinates from target and check for the collision
		
		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player willing to move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate
Outpur:
		
		if collision then true
		else false.
				   
Details:
		The game_grid takes the coordinate from target [1] and check if there is a box, if none no collision else
		it takes another coordinate from target [2] and check again. if there is a box in target [2] then collision 
		occured else no collision.
	
*/
int collision_box(struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]);
/*
Fcuntion: update_grid

Purpose:  A master function calls all the update obejcts functions below
		
*/
void update_grid(struct block game_grid[GRID_SIZE][GRID_SIZE],struct coordinate target[]);
/*
Fcuntion: update_storage_locations

Purpose:  if a storage location is cover by a player or a box. 
		  bool cover in obejct has to be updated.

		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player willing to move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate
		
		game_grid - take  [0] [1] [2] coordinate and use them check on the game grid.
		
Details: After the player move or a box is been pushed, check if the block of all objects ptr points to null 
		 no objects is convering storage location, else if there is on pointer is not null then it is convered
		 
		
*/
void update_storage_locations(struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]);

/*
Fcuntion: update_player

Purpose:  update player current coordinate to target[1] position

		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player willing to move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate
		
*/

void update_player(struct block game_grid[GRID_SIZE][GRID_SIZE],struct coordinate target[]);
/*
Fcuntion: update_box

Purpose:  if there is a box at target[1] update box current coordinate to target[2] coordinate

		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player willing to move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate
		
*/
void update_box(struct block game_grid[GRID_SIZE][GRID_SIZE],struct coordinate target[]);


#endif
