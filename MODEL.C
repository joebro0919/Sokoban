#include "model.h"
#include <stdio.h>
#include <osbind.h>
void load_grid_walls(struct coordinate walls[], struct block game_grid [GRID_SIZE][GRID_SIZE]){

	int index, x_coordinate, y_coordinate;
	
	for(index = 0; index < WALL_NUM; index++){
		
		x_coordinate = walls[index].x;
		y_coordinate = walls[index].y;
		game_grid[y_coordinate][x_coordinate].wall = True; 
		
	}

}

void load_boxes(struct box boxes[], struct block game_grid [GRID_SIZE][GRID_SIZE]){
	
	int index, x_coordinate, y_coordinate;
	struct box *temp_box_ptr = boxes;
	
	
	for(index = 0; index < BOX_NUM; index++){
		
		x_coordinate = boxes[index].defaultPos.x;
		y_coordinate = boxes[index].defaultPos.y;
		game_grid[y_coordinate][x_coordinate].box_ptr = temp_box_ptr;
		temp_box_ptr++;
	}
	
	
	return;
}

void load_storageLocations(struct storage_location storage_locations[], struct block game_grid [GRID_SIZE][GRID_SIZE]){
	
	int index, x_coordinate, y_coordinate;
	struct storage_location *temp_storage_ptr = storage_locations;
	
	for(index = 0; index < STORAGE_NUM; index++){
		
		x_coordinate = storage_locations[index].fixed.x;
		y_coordinate = storage_locations[index].fixed.y;
		
		game_grid[y_coordinate][x_coordinate].storage_location_ptr = temp_storage_ptr;
		temp_storage_ptr++;
		
	}
	
	return;
}
void load_player(struct worker *player, struct block game_grid [GRID_SIZE][GRID_SIZE]){
	
	int x_coordinate = player -> defaultPos.x;
	int y_coordinate = player -> defaultPos.y;
	
	game_grid[y_coordinate][x_coordinate].worker_ptr = player;
	
	return;
	
}



int collision_wall(struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[])
{
	int x_coordinate = target[1].x;
	int y_coordinate = target[1].y;
	
	return game_grid[y_coordinate][x_coordinate].wall;
}

int collision_box(struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]){

	int x_coordinate_1 = target[1].x;
	int y_coordinate_1 = target[1].y;
	
	int x_coordinate_2 = target[2].x;
	int y_coordinate_2 = target[2].y;
	
	
	if(game_grid[y_coordinate_1][x_coordinate_1].box_ptr != NULL){
	
		if (game_grid[y_coordinate_2][x_coordinate_2].box_ptr != NULL)
			{return True;}
		
		else if (game_grid[y_coordinate_2][x_coordinate_2].wall == True)
			{return True;}
	}
		
		
		return False;
	
}
int collision_check (struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]){
	
	
	if (collision_wall(game_grid, target) == True)
	{return True;}	
	
	else if (collision_box(game_grid, target) == True) 
	{return True;}	

	return False;

	


}
void update_grid(struct block game_grid[GRID_SIZE][GRID_SIZE],struct coordinate target[])
{
	
	int x_coordinate_1 = target[1].x;
	int y_coordinate_1 = target[1].y;
	
	int x_coordinate_2 = target[2].x;
	int y_coordinate_2 = target[2].y;

	update_player(game_grid, target);
	
	if (game_grid[y_coordinate_1][x_coordinate_1].box_ptr != NULL){
		
		update_box(game_grid,target);
		
	}
	
	update_storage_locations(game_grid, target);	
	
	return;
}

void update_player(struct block game_grid[GRID_SIZE][GRID_SIZE],struct coordinate target[]){
	
	int x_coordinate_0 = target[0].x;
	int y_coordinate_0 = target[0].y;
	
	int x_coordinate_1 = target[1].x;
	int y_coordinate_1 = target[1].y;
	
	struct worker *temp_worker_ptr = game_grid[y_coordinate_0][x_coordinate_0].worker_ptr;
	
	game_grid[y_coordinate_1][x_coordinate_1].worker_ptr = temp_worker_ptr;
	game_grid[y_coordinate_0][x_coordinate_0].worker_ptr = NULL;
	
	temp_worker_ptr -> current.x = x_coordinate_1;
	temp_worker_ptr -> current.y = y_coordinate_1;
	
	return;
}
void update_box(struct block game_grid[GRID_SIZE][GRID_SIZE],struct coordinate target[]){
	
	int x_coordinate_1 = target[1].x;
	int y_coordinate_1 = target[1].y;
	
	int x_coordinate_2 = target[2].x;
	int y_coordinate_2 = target[2].y;
	
	struct box *temp_box_ptr = game_grid[y_coordinate_1][x_coordinate_1].box_ptr;
	
	game_grid[y_coordinate_2][x_coordinate_2].box_ptr = temp_box_ptr;
	game_grid[y_coordinate_1][x_coordinate_1].box_ptr = NULL;
	
	temp_box_ptr -> current.x = x_coordinate_2;
	temp_box_ptr -> current.y = y_coordinate_2;
	
	
	return;
	
	
}

void update_storage_locations(struct block game_grid[GRID_SIZE][GRID_SIZE], struct coordinate target[]){
	
	int x_coordinate_0 = target[0].x;
	int y_coordinate_0 = target[0].y;

	int x_coordinate_1 = target[1].x;
	int y_coordinate_1 = target[1].y;
	
	int x_coordinate_2 = target[2].x;
	int y_coordinate_2 = target[2].y;
	
	struct storage_location *storage_ptr0 = game_grid[y_coordinate_0][x_coordinate_0].storage_location_ptr;
	struct storage_location *storage_ptr1 = game_grid[y_coordinate_1][x_coordinate_1].storage_location_ptr;
	struct storage_location *storage_ptr2 = game_grid[y_coordinate_2][x_coordinate_2].storage_location_ptr;
	
	struct box *temp_box_ptr = game_grid[y_coordinate_2][x_coordinate_2].box_ptr;
	
	
	if (storage_ptr0 != NULL){
		
		storage_ptr0 -> covered = False;
		
	}
	
	if (storage_ptr1 != NULL){
		
		storage_ptr1 -> covered = True;
		
	}
	
	if(storage_ptr2 != NULL && temp_box_ptr != NULL){
		
		storage_ptr2 -> covered = True;
		
	}
	
	
	return;
}

