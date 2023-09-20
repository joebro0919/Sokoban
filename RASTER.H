#ifndef RASTER_H
#define RASTER_H
/*
RASTER.H

polting a single bitmap on the screen.
*/

#include "sub.h"
/*
Fcuntion: plot_32bitmap

Purpose: ploting a 32 bitmap on screen

Input: 
		base - a screen which need to be polt at
		
		x, y - a corrdinate which the bitmap is polted.
		
		*bitmap - the bitmap of the picture 
		
		height - height of the bitmap


Details:
		plot a bit map to certains x and y coordinate 
*/
void plot_32bitmap(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
/*
Fcuntion: clear_screen

Purpose: clear everthing on the screen

*/

void clear_screen(UINT32 *base);
/*
Fcuntion: plot_vline

Purpose: plot a vertical line on the screen

Input:	
		base - the scrren
		x    - horizontal point which want to plot a line
		y1	 - vertical point which start to plat a line
		y2   - vertical point which end the line

*/
void plot_vline (UINT8 *base, int x, int start_vertical, int end_vertical);

/*
Functions: print_splash

Purpose: prints a splash screen
*/
void plot_splash(UINT8 *base,const UINT8 *bitmap);

UINT16* get_video_base();
void call_set_video_base(UINT32 *base); 

#endif
