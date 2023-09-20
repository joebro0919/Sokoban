#ifndef MUSIC_H
#define MUSIC_H
#include "PSG.H"

#define MUSIC_LENGTH    96
#define c_note          478       
#define d_note          426      
#define e_note          379
#define f_note          358      
#define g_note          319     
#define a_note          284
#define b_note          253

struct note{
    int pitch;
    int duration;
};

void update_music(struct note music[],int array_num); 



#endif