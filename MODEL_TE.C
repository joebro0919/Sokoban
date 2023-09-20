#include "model.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

int main(){
int j,k;
char up,down,left,right;
char input;

UINT32 *base = Physbase();
UINT8 *base8 = Physbase();
char *basechar = Physbase();
up = 'w';
down = 's';
left = 'a';
right = 'd';

load_grid_walls(walls,game_grid, 10,10);
load_boxes_and_storage(boxes,storage_locations,game_grid);

/*testing load grid with walls
*/
for(j=0; j<13; j++){
		for(k=0; k<13; k++){
			printf("Column %d: %d \n",j, game_grid[k][j].wall);
			if(k == 12){
			Cconin();
		}
	}
}
/*
testing load grid with boxes
*/
for(j=0; j<13; j++){
	for(k=0; k<13; k++){
		if(game_grid[k][j].box_ptr != NULL){
			printf("Box X coord: %d    ", game_grid[k][j].box_ptr->defaultPos.x);
			printf("Box Y coord: %d \n", game_grid[k][j].box_ptr->defaultPos.y);
			Cconin();
		}
	}
}

/*
testing load grid with storage locations
*/
for(j=0; j<13; j++){
	for(k=0; k<13; k++){
		if(game_grid[k][j].storage_location_ptr != NULL){
		printf("Storage X coord: %d    ", game_grid[k][j].storage_location_ptr->fixed.x);
		printf("Storage Y coord: %d \n", game_grid[k][j].storage_location_ptr->fixed.y);
		Cconin();
		}
	}
}

/*
General model testing
*/
printf("Player X coord def: %d \n", player.current.x);
printf("Player Y coord def: %d \n", player.current.y);


direction_coordinate(down, player.current, target);
update_grid(game_grid, target, &player);

printf("Player X coord down: %d \n", player.current.x);
printf("Player Y coord down: %d \n", player.current.y);


direction_coordinate(left, player.current, target);
update_grid(game_grid, target, &player);

printf("Player X coord left: %d \n", player.current.x);
printf("Player Y coord left: %d \n", player.current.y);

update_storage_locations(game_grid, storage_locations);

direction_coordinate(down, player.current, target);
update_grid(game_grid, target, &player);
update_storage_locations(game_grid, storage_locations);

printf("Player X coord down: %d \n", player.current.x);
printf("Player Y coord down: %d \n", player.current.y);

direction_coordinate(left, player.current, target);
update_grid(game_grid, target, &player);
update_storage_locations(game_grid, storage_locations);

printf("Player X coord left: %d \n", player.current.x);
printf("Player Y coord left: %d \n", player.current.y);

for(j=0; j<13; j++){
	for(k=0; k<13; k++){
		if(game_grid[k][j].box_ptr != NULL){
			printf("Box X coord: %d    ", game_grid[k][j].box_ptr->current.x);
			printf("Box Y coord: %d \n", game_grid[k][j].box_ptr->current.y);
			Cconin();
		}
	}
}

for (j = 0; j<STORAGE_NUM;j++){
	printf("Storage Covered: %d \n", storage_locations[j].covered);
	printf("Storage X coord: %d \n", storage_locations[j].fixed.x);
	printf("Storage Y coord: %d \n", storage_locations[j].fixed.y);
	Cconin();

}

reset_game_grid(game_grid, storage_locations, boxes, &player);


Cconin();
render_walls(base, walls, wall_bitmap);
render_player(base, player, worker_bitmap);
plot_vline(base8, 416, 0, 399);
render_reset_button(base, reset_button, redo_button_RE, redo_button_SE, redo_button_T);
render_boxes(base, boxes, box_t1_bitmap);
render_storage_locations(base, storage_locations, storage_location_bitmap);


while(input != 'p'){
	input = Cconin();
	if(input == 'r'){
		reset_game_grid(game_grid, storage_locations, boxes, &player, target);
		fill_screen(basechar, 0);
		plot_vline(base8, 416, 0, 399);
		render_walls(base, walls, wall_bitmap);
		render_reset_button(base, reset_button, redo_button_RE, redo_button_SE, redo_button_T);
		render_storage_locations(base, storage_locations, storage_location_bitmap);
		render_player(base, player, worker_bitmap);
		render_boxes(base, boxes, box_t1_bitmap);
	}
	else{
		render_player(base, player, clear);
		render_boxes(base, boxes, clear);
		direction_coordinate(input, player.current, target);
		update_grid(game_grid, target, &player);
		update_storage_locations(game_grid, storage_locations);
		render_storage_locations(base, storage_locations, storage_location_bitmap);
		render_player(base, player, worker_bitmap);
		render_boxes(base, boxes, box_t1_bitmap);
		if(check_win(storage_locations) == 1){
			fill_screen(basechar, 0);
			printf("VICTORY");
		}
	}
}

Cconin();
/*
direction_coordinate(down, player.current, target);
update_grid(game_grid, target, &player);
direction_coordinate(left, player.current, target);
update_grid(game_grid, target, &player);
render_walls(base, walls, wall_bitmap,10,10);
plot_vline(base8, 416, 0, 399);
plot_vline(base8, 417, 0, 399);
plot_vline(base8, 418, 0, 399);
render_reset_button(base, reset_button, redo_button_RE, redo_button_SE, redo_button_T);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);

Cconin();
render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(left, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);

Cconin();
render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(down, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();

render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(down, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();

render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(right, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();

render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(up, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();


render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(up, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();


render_player(base, player, clear);
render_boxes(base, boxes, clear);
direction_coordinate(up, player.current, target);
update_grid(game_grid, target, &player);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();

fill_screen(basechar, 0);
reset_game_grid(game_grid, storage_locations, boxes, &player);
render_walls(base, walls, wall_bitmap,10,10);
plot_vline(base8, 416, 0, 399);
plot_vline(base8, 417, 0, 399);
plot_vline(base8, 418, 0, 399);
render_reset_button(base, reset_button, redo_button_RE, redo_button_SE, redo_button_T);
render_storage_locations(base, storage_locations, storage_location_bitmap);
render_player(base, player, worker_bitmap);
render_boxes(base, boxes, box_t1_bitmap);
Cconin();
*/


for(j=0; j<13; j++){
	for(k=0; k<13; k++){
		if(game_grid[k][j].box_ptr != NULL){
			printf("Box X coord: %d    ", game_grid[k][j].box_ptr->current.x);
			printf("Box Y coord: %d \n", game_grid[k][j].box_ptr->current.y);
			Cconin();
		}
	}
}

for (j = 0; j<STORAGE_NUM;j++){
	printf("Storage Covered: %d \n", storage_locations[j].covered);
	printf("Storage X coord: %d \n", storage_locations[j].fixed.x);
	printf("Storage Y coord: %d \n", storage_locations[j].fixed.y);
	Cconin();

}



return 0;
}