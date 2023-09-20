#include "events.h"
#include "renderer.h"
#include "MUSIC.H"
#include "EFFECTS.H"
#include <stdio.h>
#include <osbind.h>



void wait();
char read_char();
UINT32 get_time();
int valid_input(char input);
UINT32* find_256_location (UINT8 back_buffer_screen[]);
void set_ptrs_null (struct block game_grid [GRID_SIZE][GRID_SIZE]);
UINT32* switch_screen (UINT32 *base, UINT32 *back_buffer, int *bufferCounter);
void initiate_render_objects (UINT32 *base, struct models objects, int done_wall);
void initiate_render_clear_player_N_ALLboxes (UINT32 *base, struct models objects);
void load_objects (struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], int done_wall);
void initiate_render_player_box (UINT32 *base, struct block game_grid [GRID_SIZE][GRID_SIZE], struct coordinate target[]);
void initiate_render_clear_player_N_box (UINT32 *base, UINT32 *back_buffer, UINT32 *screen_ptr, struct coordinate target[]);
void do_reset(UINT32 *base, UINT32 *back_buffer, struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], UINT32 *screen_ptr);
void initiate_render_storage_locations(UINT32 *base, UINT32 *back_buffer, UINT32 *screen_ptr, struct coordinate target[],struct block game_grid [GRID_SIZE][GRID_SIZE]);
void do_move(UINT32 *base, UINT32 *back_buffer, struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], UINT32 *screen_ptr, struct coordinate target[]);
void first_load_N_render (UINT32 *base, UINT32 *back_buffer, struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], int done_wall);

UINT8 back_buffer_screen [32256];
int main(){
	
	struct block game_grid[GRID_SIZE][GRID_SIZE];
	
	struct models objects = { 
			/*assign all the object with coordinate  (x,y) */
		{	/*  struct coordinate walls[WALL_NUM]  */
			{3,3},  {3,4},  {3,7},  {3,10},  {4,7},  {4,10},
			{6,3},  {6,4},  {6,6},  {6,7},   {7,6},  {7,7},
			{7,9},  {7,10}, {8,6},  {9,3},   {9,6},  {10,3}, 
			{10,6}, {2,2},  {2,3},  {2,4},   {2,5},  {2,6},
			{2,7},  {2,8},  {2,9},  {2,10},  {2,11}, {3,2},
			{4,2},  {5,2},  {6,2},  {7,2},   {8,2},  {9,2}, 
			{10,2}, {11,2}, {3,11}, {4,11},  {5,11}, {6,11},
			{7,11}, {8,11}, {9,11}, {10,11}, {11,11},
			{11,3}, {11,4}, {11,5}, {11,6},  {11,7}, {11,8},
			{11,9}, {11,10}
		},

		{  /* struct storage_location storage_locations[STORAGE_NUM] */
			{False, {5,4}}, {False, {5,5}}, {False, {9,5}},
			{False, {4,8}}, {False, {5,8}}, {False, {8,8}}, {False, {8,9}}
		},

		{ 			/*struct box boxes[BOX_NUM];*/
			{{4,4}, {4,4}}, {{4,5}, {4,5}}, {{4,9}, {4,9}},
			{{5,9}, {5,9}}, {{9,4}, {9,4}}, {{9,8}, {9,8}},
			{{9,9}, {9,9}}
		},

		{ /*struct worker player;*/
			{10,7}, {10,7}
		},
		  /*struct coordinate reset_button*/
			{15,1}
		
	};

	struct note music[MUSIC_LENGTH] = {
		{c_note,70}, {b_note, 70},{g_note,70},{b_note,70},
		{c_note,70}, {b_note, 35},{g_note,70},{b_note,35},
		{c_note,70}, {b_note, 35},{g_note,70},{b_note,35},
		{c_note,70}, {b_note, 35},{g_note,70},{e_note,35},
		{c_note,35}, {b_note, 35},{g_note,35},{b_note,35},
		{c_note,35}, {b_note, 35},{g_note,35},{b_note,35},
		{c_note,35}, {b_note, 35},{g_note,35},{b_note,35},
		{c_note,35}, {b_note, 35},{g_note,35},{e_note,35},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,15}, {b_note, 15},{e_note,15},{a_note,15},
		{c_note,5}, {b_note, 5},{g_note,5},{e_note,5}

	};

	struct coordinate target[3];
	/*	target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player will move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate*/
  
	UINT32 timeNow, timeThen, timeElapsed,musicTimeThen, musicTimeNow, musicTimeElapsed;
    UINT32 *base = (UINT32*) ((UINT32)get_video_base() << 8);
	UINT32 *back_buffer = find_256_location(back_buffer_screen);
	UINT32 *screen_ptr; /*indiate which scrren buffer has to be pass in to function*/
	
    char input;
	
    int quit = False;
    int win = False;
	int done_wall = False;	/*wall only has to be printed on time this will passed in to fucntion indiate no need to print wall again*/
	int bufferCounter = 0;	/*odd back screen buffer even main screen buffer*/
	int current_music = 0;
	int next_music = 1;
		
	first_load_N_render (base, back_buffer, &objects, game_grid , done_wall);
	
	write_psg(7,0x3F);
	
	update_music(music, current_music);
	enable_channel(0,1,0);
	enable_channel(2,0,1);
	set_volume(0,10);
	set_volume(2,26);
	
	done_wall = True;

    timeThen = get_time();
	musicTimeThen = timeThen;

    while(quit == False && win == False){

		if(Cconis()){
			input = read_char();
		}
		timeNow = get_time();

		timeElapsed = timeNow - timeThen;

		if (timeElapsed > 0){

			musicTimeElapsed =  timeNow - musicTimeThen;
			
			if(musicTimeElapsed > music[current_music].duration && current_music <= (MUSIC_LENGTH-1)){
				
				if(next_music > (MUSIC_LENGTH-1)){
					current_music = 0;
					next_music = 1;
				}
				else{
					current_music = next_music;
					next_music++;
				}
				update_music(music, current_music);
				musicTimeThen = get_time();
			}
            
			if(valid_input(input) == True){

				screen_ptr = switch_screen(base, back_buffer, &bufferCounter);
		
				if (input == 'q'){
					quit = True;
					
				}
           		else if(input == 'r'){
					do_reset (base, back_buffer, &objects, game_grid, screen_ptr);
					
				}
				else{
                    /*take user input and assign them to target*/
		        	direction_coordinate(input, objects.player.current, target);
					if (collision_check(game_grid, target) == False) {
						do_move (base, back_buffer, &objects, game_grid, screen_ptr, target);
						
					}
				}			
			}
            timeThen = timeNow;
			input ='z'; /*change input so it doesn't repeatedly move character*/
        }
		
        win = check_win(objects.storage_locations);
    }
	bufferCounter = 0;
	stop_sound();
	enable_channel(0,0,0);
	switch_screen (base, back_buffer, &bufferCounter);
	
    return 0;
}

/*
Fcuntion: do_move

Purpose:  a master function to process a player have a valid move.

steps:	
		first clear a block located in target[]
		update the gird 
		print player and box (if there is a box) 
		check print storage location if is no cover in the target coordinate
*/
void do_move(UINT32 *base, UINT32 *back_buffer, struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], UINT32 *screen_ptr, struct coordinate target[]){
	
	initiate_render_clear_player_N_box (base, back_buffer, screen_ptr, target);
				
	update_grid(game_grid, target);	
					
	initiate_render_player_box(screen_ptr, game_grid, target);
					
	initiate_render_storage_locations (base, back_buffer, screen_ptr, target, game_grid);
	
	return;
	
}/*
Fcuntion: initiate_render_clear_player_and_box

Purpose:  Clear the major 3 blocks in the grid. (rendering 0 in the coordinate)
		  
	input :
		*base - the main scrren buffer
		*back_buffer - back screen buffer
		*screen_ptr - indiate which screen buffer is being used
		 target[]  - the three major blocks 
		
Details: Since every valid move from the player only involving 3 blocks in the grid. 
		Therefore clear these 3 block after update the gird and using the coordinate in the target to check 
		which should be render in these 3 blocks.
		
		Also the previous player location in the screen buffer that is not being used need to be cleaned 
		if no the next time of the valid move there is another player appear in the grid
*/
void initiate_render_clear_player_N_box (UINT32 *base, UINT32 *back_buffer, UINT32 *screen_ptr, struct coordinate target[]){
	
	if (screen_ptr == base){
		
		render_clear_block(base, target[0]);
		render_clear_block(base, target[1]);
		render_clear_block(back_buffer, target[3]);
		
	}else{
		
		render_clear_block(back_buffer, target[0]);
		render_clear_block(back_buffer, target[1]);
		render_clear_block(base, target[3]);
		
	}
	
	return;
	
}
/*
Fcuntion: initiate_render_player_box

Purpose:  take the main 3 blocks coordinate and check if there is object on the grid if so pass the coordinate
		  to render function and print the object (only player and box in this function)
		  
	intput :
		*base - the screen buffer is being used
		 target[]  - the three major blocks 
		 game_grid - contains all the info about object
		
Details: This funtion is called after the grid being update. Since it is a valid move, player has to be at the target[1],
		 if there were a box in target [1] it has to be at [2], so check this two coordinates and render the objects.
*/
void initiate_render_player_box (UINT32 *base, struct block game_grid [GRID_SIZE][GRID_SIZE], struct coordinate target[]){
	
	int x_coordinate = target[2].x;
	int y_coordinate = target[2].y;
	
	struct box *temp_box_ptr = game_grid[y_coordinate][x_coordinate].box_ptr;
	struct storage_location *temp_storage_location_ptr = game_grid[y_coordinate][x_coordinate].storage_location_ptr;
	
	
	render_player(base, target[1]);
	
	if (temp_box_ptr != NULL){
		
		
		if (temp_storage_location_ptr == NULL)
		
			render_box_t1(base, target[2]);
		
		
		else 
			render_box_t2(base, target[2]);
		
	
	}
	
	return;
	
}
/*
Fcuntion: initiate_render_storage_locations

Purpose:  check if there is object coverd a storage_location. only target[0] and target[3] are needed.
	
input:	*base - the main scrren buffer
		*back_buffer - back screen buffer
		*screen_ptr - indiate which screen buffer is being used
		target[]  - the three major blocks 
		 game_grid - contains all the info about object
		
Details: Player is move toward to other the original position from player must contain no objects so this coordinate need to be check
	     if there is a storage location 
		 
		 also the pervious player is clear in the scrren buffer that is no being use that pervious player coordinate also need be checked.
		 
*/
void initiate_render_storage_locations(UINT32 *base, UINT32 *back_buffer, UINT32 *screen_ptr, struct coordinate target[],struct block game_grid [GRID_SIZE][GRID_SIZE]){
	
	
	int x_coordinate_0 = target[0].x;
	int y_coordinate_0 = target[0].y;
	
	int x_coordinate_3 = target[3].x;
	int y_coordinate_3 = target[3].y;
	
	struct storage_location *storage_location_ptr_0 = game_grid[y_coordinate_0][x_coordinate_0].storage_location_ptr;
	struct storage_location *storage_location_ptr_3 = game_grid[y_coordinate_3][x_coordinate_3].storage_location_ptr;
	
	if (screen_ptr == base){
		
		if (storage_location_ptr_0 != NULL){
			
			render_storage_location(base, target[0]);
		}
		
		if (storage_location_ptr_3 != NULL){
			
			render_storage_location(back_buffer, target[3]);
		}
		
	}else{
		
		if (storage_location_ptr_0 != NULL){
			
			render_storage_location(back_buffer, target[0]);
		}
		
		if (storage_location_ptr_3 != NULL){
			
			render_storage_location(base, target[3]);
		}
	}
	
	
	return;
	
}
/*
Fcuntion: first_load_Then_render

Purpose: master function for loading all the objects in to game_grid to both screen buffer. 
		then render object to both scrren buffer
	
input:	*base - the main scrren buffer
		*back_buffer - back screen buffer
		game_grid - contains all the info about object
		objects  - all the objects
		wall - indiate if wall has been printed
		
		 
*/
void first_load_N_render (UINT32 *base, UINT32 *back_buffer, struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], int done_wall){
	
	
	load_objects (objects, game_grid, done_wall);

	initiate_render_objects (base, *objects, done_wall);
	
	initiate_render_objects (back_buffer, *objects, done_wall);
	
}

/*
Fcuntion: do_reset

Purpose: mater function to process the reseting the gird after player take a action of reset
	
steps:	clear the player and all the boxes (both scrren)
		reset object current postion = default postion
		load all the object to game_grid
		render objects
Details: 
		 
*/
void do_reset(UINT32 *base, UINT32 *back_buffer, struct models *objects, 
			  struct block game_grid [GRID_SIZE][GRID_SIZE], UINT32 *screen_ptr){

	int done_wall = True;

	initiate_render_clear_player_N_ALLboxes(base, *objects);
	initiate_render_clear_player_N_ALLboxes(back_buffer, *objects);
	reset_objects (objects);   
	load_objects (objects, game_grid, done_wall);
	initiate_render_objects (screen_ptr, *objects, done_wall);
		
	return;
	
}
/*
Fcuntion: initiate_render_clear_player_N_ALLboxes

Purpose: in order to reset the game_grid player and boxes need to be clear 

Details: take player and all boxes coordinate then print a blank 32 x 32 bitmap on their coordinate.
	
*/
void initiate_render_clear_player_N_ALLboxes (UINT32 *base, struct models objects){
	
	int index;
	render_clear_block(base, objects.player.current);
	
	for (index = 0; index < BOX_NUM; index++)
	render_clear_block(base, objects.boxes[index].current);
	
	return;
}
/*
Fcuntion: load_objects

Purpose: maste function to call every load objects function 

load all the object coordinate to game_grid.

if wall has been printed then no need to printed again.
	
*/
void load_objects(struct models *objects, struct block game_grid [GRID_SIZE][GRID_SIZE], int done_wall){

	
	if (done_wall == False){
		load_grid_walls(objects -> walls, game_grid);
	}
	
	set_ptrs_null(game_grid);
	
	load_boxes(objects -> boxes, game_grid);
	
    load_storageLocations(objects -> storage_locations, game_grid);
	
	load_player(&objects -> player, game_grid);
	
	return;
	
}
/*
Fcuntion: initiate_render_objects

Purpose: mater function which print all the objects

this will be called when the game launch or game reset
	
*/
void initiate_render_objects (UINT32 *base, struct models objects, int done_wall){
	
	UINT8 *base8 = (UINT8*)base;


	if (done_wall == False){
		
		render_walls(base, objects.walls);
		
		render_reset_button(base, objects.reset_button);
		
		plot_vline(base8, 416, 0, 399);
		
	}
	
	render_storage_locations(base, objects.storage_locations);
	
	render_player(base, objects.player.current);
	
    render_boxes(base, objects.boxes);
	
    
	
	
	return;
	
}
void wait(){
	
	UINT32 time = get_time();
	
	while(get_time() - time != 0);
	
	return;
}
/*
Fcuntion: switch_screen

Purpose: take the bufferCounter and set a screen to main screen
	
		 
*/
UINT32* switch_screen (UINT32 *base, UINT32 *back_buffer, int *bufferCounter){
	
	UINT32 *temp;
	
	*bufferCounter++;

	if (*bufferCounter % 2 == 0){
		
		temp = base;
	
	}else{
	
		temp = back_buffer;
	}
	
	
	wait();
	call_set_video_base(temp);
	
	return temp;
	
	
}
UINT32* find_256_location (UINT8 back_buffer_screen[]){
	
	UINT32 temp = 0xff;
	UINT32 address = (UINT32) &back_buffer_screen[0];

	for(; (address & temp) != 0; address++);
	
	return (UINT32*) address;
	
	
}


char read_char(){
	
    char output;
    output = Cnecin();
    return output;
	
}
/*
Fcuntion: valid_input

Purpose: check only player valid input 

only w a s d r q are accpted
	
		 
*/
int valid_input(char input){

	
	if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'r'|| input == 'q')
		
	{return True;}


	return False;
	
}

UINT32 get_time(){

    long *timer = (long *)0x462; 
    long timeNow;
    long old_ssp;

    old_ssp = Super(0); 
    timeNow = *timer;
    Super(old_ssp);

    return timeNow;
}
/*
Fcuntion: set_ptrs_null

Purpose: set all the ptr to null in the game_grid
			 
*/
void set_ptrs_null(struct block game_grid [GRID_SIZE][GRID_SIZE]){
	
	int x_coordinate, y_coordinate;
	
	for(x_coordinate = 0; x_coordinate < GRID_SIZE; x_coordinate++){
		
		for(y_coordinate = 0; y_coordinate < GRID_SIZE; y_coordinate++){
			
			game_grid[y_coordinate][x_coordinate].box_ptr = NULL;
			game_grid[y_coordinate][x_coordinate].storage_location_ptr = NULL;
			game_grid[y_coordinate][x_coordinate].worker_ptr = NULL;
			
		}
		
	}

	return;
}