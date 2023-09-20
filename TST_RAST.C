#include <osbind.h>
#include "raster.h"
#include <stdio.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

UINT32 clear[32] ={
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};


int main()
{
	

	int x, y;
	UINT32 *base = Physbase();
	UINT8 *base2 = Physbase();
	
        char ch;
	for(x=0; x < SCREEN_WIDTH; x = x + 32){
		for(y = 0; y < SCREEN_HEIGHT; y = y+32){
			plot_32bitmap(base,x , y, wall_bitmap, 32);
		}
	}

	while(!Cconis()){

	}
	clear_screen(base);
	getchar();	
	return 0;
}
