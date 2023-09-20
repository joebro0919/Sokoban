#include "events.h"
#include "model.h"
#include "effects.h"
/*
EVENTS.C

A action that the program will execute when specific event occurred.

*/


void reset_objects (struct models *objects)
{
	int index;
	
	for(index = 0; index < BOX_NUM; index++){
		
		objects -> boxes[index].current.x = objects -> boxes[index].defaultPos.x;
		objects -> boxes[index].current.y = objects -> boxes[index].defaultPos.y;
		
	}

	for(index = 0; index < STORAGE_NUM; index++){
		
		objects -> storage_locations[index].covered = False;
		
	}
	
	
	objects -> player.current.x = objects -> player.defaultPos.x;
	objects -> player.current.y = objects -> player.defaultPos.y;
	restart_effect();

	return;
}

int check_win(struct storage_location storage_locations[]){
	
	int index;

	for(index = 0; index < STORAGE_NUM; index++){
		
		if(storage_locations[index].covered == False)
		{return False;}
	
	}
	
	return True;
}

void direction_coordinate (char direction, struct coordinate player_pos, struct coordinate target[])
{
	target[0].x = target[3].x;
	target[0].y = target[3].y;
	
	target[0].x = player_pos.x;
	target[0].y = player_pos.y;
	
	if(direction == 'w' || direction == 's'){
		target[1].x = player_pos.x; 
		target[2].x = player_pos.x; 
		
	}
	else{
		target[1].y = player_pos.y; 
		target[2].y = player_pos.y; 
		
	}
	
	if (direction == 'w')
	{
		target[1].y = player_pos.y - 1;	
		target[2].y = player_pos.y - 2;	
		
	}
	else if (direction == 's'){
		target[1].y = player_pos.y + 1;	
		target[2].y = player_pos.y + 2;	
	
	}
	else if (direction == 'a'){
		target[1].x = player_pos.x - 1; 
		target[2].x = player_pos.x - 2; 

	}
	else if (direction == 'd'){
		target[1].x = player_pos.x + 1; 
		target[2].x = player_pos.x + 2; 
	}
	move_effect();

	return;	
}
