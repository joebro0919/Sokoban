#include "EFFECTS.H"

void move_effect(){
    set_noise(5);
    set_envelope(0,600);
    write_psg(13, 4);
}

void restart_effect(){
    set_noise(3);
    set_envelope(0,200);
    write_psg(13, 8);
    
}