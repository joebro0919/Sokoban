#ifndef PSG_H
#define PSG_H

#include "MODEL.H"
#include <osbind.h>

void write_psg(int reg, UINT8 val); 
void set_tone(int channel, int tuning); 
UINT8 read_psg(int reg); 
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void and_or_psg(int reg, UINT8 val, int and_or); 
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain); 

#endif