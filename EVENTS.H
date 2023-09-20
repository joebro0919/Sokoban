#ifndef EVENTS_H
#define EVENTS_H
/*
EVENTS.H

A action that the program will execute when specific event occurred.

*/
#include "model.h"
/*
Fcuntion: reset_game_grid

Purpose: Assigning box and player current position to the dafault coordinate.
		 each bool covered in storage_locations[] set to false.
Input: 
		objects - only player box and storage_location need to be reset
*/
void reset_objects (struct models *objects);

/*
Fcuntion: check_win

Purpose: Check if all the location point is been convered by a box if so the player complete the game else the play continue the game.

Input:	
		storage_locations[] - checks if all the bool variables conver in the struct storage_locations[] is set to true 
							  (which means all the points are converd by boxes) the player wins the game.

Output:	
		Althought it is a int variable but it acts like a bool type which is 0 == false 1 == true.
		if all the loccation get convered it returns true otherwise false

Details:	
		When a box is moved to location point it would set that converdd variable to be true in the struct storage_location.
		Once all the point is convered which means the player complete the game.
	
*/
int check_win(struct storage_location storage_locations[]);

/*
Fcuntion: direction_coordinate

Purpose: Updated the corrdinate to the target[] after reading the input from the user.


Input:
		direction - The user input either 'w', 's', 'a' or 'd'.

		player_pos - the struct of player postion which needed to update target [].
		
		target[] - It contains 3 coordinate. 
				   [0] contains the current player coordinate.
				   [1] contains the coordinate that the player will move.
				   [2] contains the coordinate of the player one extea step futher after the move. 
				   [3] contains the previous player corrdinate

Details:
		Since only up, down, left and right are accepted, which also indicate as 'w' 's' 'a' 'd', either x coordinate 
		need to be updated if left or right is input, else y coordinate need to be updated if up or down is input. 
		After taking the input from the player, the function updates the the corrdinate to target[].
*/
void direction_coordinate (char direction, struct coordinate player_pos, struct coordinate target[]);

#endif