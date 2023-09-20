#include "raster.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

#include <stdio.h>
#include <osbind.h>


void clear_screen(UINT32 *base){
	
	int index = 0;
	UINT32 *ptr = base;

	while(index++ < 32000)
		
		*(ptr++) = 0x00000000;
		
	
}

void fill_screen(char *base, char pattern){

	 int index = 0;
	 char *loc = base;

	while (index++ < 32000)
		
		*(loc++) = pattern;

}

void plot_vline (UINT8 *base, int x, int start_vertical, int end_vertical){

	int temp;
	UINT8 pattern;
	UINT8 *screen_byte;

	if (x >= 0 && x < 640)
	{
		if (start_vertical > end_vertical)
		{
			temp = start_vertical;
			start_vertical = end_vertical;
			end_vertical = temp;
		}
	if (start_vertical < 0) start_vertical = 0;

	if (end_vertical > 399) end_vertical = 399;

	pattern = 1 << (7 - (x & 7));
	screen_byte = base + start_vertical * 80 + (x >> 3);

	for ( ; start_vertical <= end_vertical; start_vertical++){
	
		*screen_byte = pattern;
		screen_byte = screen_byte + 80;
		}
	}
 
	return;
} 

void plot_splash(UINT8 *base, const UINT8 *splash_screen){

	int i;
	int j;

	for(i = 0; i < 400; i++){
		for(j = i*80; j < (80*(i+1)); j++){

			*(base + j) = splash_screen[j];
		}

	}
}


void plot_32bitmap(UINT32 *base, int x, int y,  const UINT32 *bitmap, unsigned int height){

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT){
	
	int offset = (x >> 5) + (y * 20);
	
	int i = 0;
	int copy = 0;
	int rightShift = (x & 31);
	int leftShift = 32 - rightShift;
	
	if (rightShift == 0){
		
		for(i = 0; i < height; i++){
			
			*(base + offset + (20*i)) = bitmap[i];
		}	
		
	}else{	
	
		for(i = 0; i < height; i++){
			
			copy = bitmap[i];
			copy = (copy >> rightShift);
			*(base + offset + (20*i)) = copy;
				
			copy = bitmap[i];
			copy = (copy << leftShift);
			*(base + offset + (20*i) + 1) = copy;
			
			}
			
		}	
			
	}

	return;
}
UINT16* get_video_base(){
	
	long old_ssp = Super(0);
		
	UINT8 *Video_Base_HI = 0xffff8201;
	UINT8 *Video_Base_MI = 0xffff8203;	
	UINT32 result = 0;
	
	result = (UINT32)(*Video_Base_HI);
	
	result = result << 8;
	
	result = result + (UINT32) (*Video_Base_MI);
	
	Super(old_ssp);
	
	return (UINT16 *)(result);

}
void call_set_video_base(UINT32* base){
	
	long old_ssp = Super(0);
	set_video_base(base);
	Super(old_ssp);
	return;
}

