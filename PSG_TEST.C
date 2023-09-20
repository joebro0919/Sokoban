
#include "PSG.H"
#include <osbind.h>
#include <stdio.h>

int main(){

   
/*
TEST
void enable_channel(int channel, int tone_on, int noise_on)
*/
   
	write_psg(7, 0x3F);

    enable_channel(0,1,0);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(1,1,0);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(2,1,0);
    printf("the enable register contains : %u \n", read_psg(7));
    
    enable_channel(0,0,0);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(1,0,0);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(2,0,0);
    printf("the enable register contains : %u \n", read_psg(7));

    enable_channel(0,0,1);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(1,0,1);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(2,0,1);
    printf("the enable register contains : %u \n", read_psg(7));

    enable_channel(0,0,0);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(1,0,0);
    printf("the enable register contains : %u \n", read_psg(7));
    enable_channel(2,0,0);
    printf("the enable register contains : %u \n\n\n", read_psg(7));

/*
TEST
void set_volume(int channel, int volume);
*/
    set_volume(0,10);
    set_volume(1,10);
    set_volume(2,10);
    printf("the A volume register contains : %u \n", read_psg(8));
    printf("the B volume register contains : %u \n", read_psg(9));
    printf("the C volume register contains : %u \n\n\n", read_psg(10));

/*
TEST
void stop_sound();
*/
    stop_sound();
    printf("the A volume register contains : %u \n", read_psg(8));
    printf("the B volume register contains : %u \n", read_psg(9));
    printf("the C volume register contains : %u \n\n\n", read_psg(10));


    while (!Cconis());



    return 0;
}
