#include "music.h"
#include <stdio.h>
#include <osbind.h>

UINT32 get_time();

int main(){

    UINT32 musicTimeElapsed, timeNow, musicTimeThen;
    int current_music = 0;
    int next_music = 1;

    struct note music[16] = {
	{c_note,70}, {b_note, 70},{g_note,70},{b_note,70},
	{c_note,70}, {b_note, 35},{g_note,70},{b_note,35},
	{c_note,70}, {b_note, 35},{g_note,70},{b_note,35},
	{c_note,70}, {b_note, 35},{g_note,70},{e_note,35},
    };
    write_psg(7,0x3F);
	update_music(music, current_music);
	enable_channel(0,1,0);
    set_volume(0,10);

    musicTimeThen = get_time();

    while(!Cconis()){
    
    timeNow = get_time();
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

    }
    return 0;
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