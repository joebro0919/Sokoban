#include "PSG.H"
#include <osbind.h>
/*
Writes the given byte value (0-255) to the given PSG register (0-15)
Channel 0 = A
        1 = B
        2 = C
*/
void write_psg(int reg, UINT8 val){
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

    *PSG_reg_select = reg;
    *PSG_reg_write = val;

    Super(old_ssp);
}

UINT8 read_psg(int reg){
    
    
    UINT8 value;
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
    *PSG_reg_select = reg;
    value = *PSG_reg_select;
    Super(old_ssp);

    return value;
}

/*
Used for enabling channels without changing other 
values 

and = 1
or = 0

*/
void and_or_psg(int reg, UINT8 val, int and_or){

    UINT8 reg_value = read_psg(reg);
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
    
    if (and_or == 1){ 
        *PSG_reg_select = reg;
        
        *PSG_reg_write = reg_value & val;
    }
    else{
        *PSG_reg_select = reg;
        
        *PSG_reg_write = reg_value | val;
        
    }
    Super(old_ssp);
   
}

void set_volume(int channel, int volume){
    if(channel == 0 || channel == 1 || channel == 2){
        if(channel == 0){
            write_psg(8, volume);
        }
        else if(channel == 1){
            write_psg(9, volume);
        }
         else if(channel == 2){
            write_psg(10, volume);
        }
    }
    else{
        return;
    }
}

void enable_channel(int channel, int tone_on, int noise_on){

    if(tone_on == 1){
        if(channel == 0){
            and_or_psg(7, 0x3E, 1);
        }
        else if(channel ==1){
            and_or_psg(7, 0x3D, 1);
        }
        else if(channel == 2){
            and_or_psg(7, 0x3B, 1);
        }
    }
    else if(noise_on == 1){
        if(channel == 0){
            and_or_psg(7, 0x37, 1);
        }
        else if(channel == 1){
            and_or_psg(7, 0x2F, 1);
        }
        else if(channel == 2){
            and_or_psg(7, 0x1F, 1);
        }
    }
    else if(tone_on == 0){
        if(channel == 0){
            and_or_psg(7, 0x01, 0);
        } 
        else if(channel == 1){
            and_or_psg(7, 0x02, 0);
        }
        else if(channel == 2){
            and_or_psg(7, 0x04, 0);
        }  
    }
    else if(noise_on == 0){
        if(channel == 0){
            and_or_psg(7, 0x08, 0);
        }
        else if(channel == 1){
            and_or_psg(7, 0x10, 0);
        }
        else if(channel == 2){
            and_or_psg(7, 0x20, 0);
        }
    }
}

void set_tone(int channel, int tuning){

    int roughtone = 0;
    int finetone = 0;

    finetone =  tuning << 4;
    finetone = finetone >> 4;

    roughtone = tuning >> 8;

    if(channel == 0){
        write_psg(0, finetone);
        write_psg(1, roughtone);
    }
    else if(channel == 1){
        write_psg(2, finetone);
        write_psg(3, roughtone);
    }
    else if(channel == 2){
         write_psg(4, finetone);
        write_psg(5, roughtone);
    }
    
    return;
}

void stop_sound(){
    set_volume(0,0);
    set_volume(1,0);
    set_volume(2,0);
}



void set_noise(int tuning){
    if(tuning > 31){
        return;
    }
    else{
    write_psg(6, tuning);
    }

}
/*
shape : 
0 = HOLD
1 = ALT
2 = ATT
3 = CONT
*/
void set_envelope(int shape, unsigned int sustain){
    int fine_adjustment, rough_adjustment;

    if (shape > 3 || sustain > 65535){
        return;
    }
    else{

        rough_adjustment = sustain >> 8;
        fine_adjustment = sustain << 8;
        fine_adjustment = fine_adjustment >> 8;

        write_psg(0xB, fine_adjustment);
        write_psg(0xC, rough_adjustment);

        if(shape == 0){
            and_or_psg(0xD, 14, 1);
        }
        else if(shape == 1){
            and_or_psg(0xD, 13, 1);
        }
        else if(shape == 2){
            and_or_psg(0xD, 11, 1);
        }
        else if(shape == 3){
            and_or_psg(0xD, 7, 1);
        }
    }
}