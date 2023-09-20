#include "MUSIC.H"


void update_music(struct note music[], int array_num){
    int pitch = music[array_num].pitch;
    set_tone(0,pitch);
}
