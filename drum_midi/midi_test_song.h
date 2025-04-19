


/* CHATGPT SUGGESTS:

#include <stdio.h>*/

// Define a simple const struct
typedef struct {
    const char *name;
    const int value;
} Config;

// Define a struct that holds pointers to const Configs
typedef struct {
    const Config *main_config;
    const Config *backup_config;
} System;

// Define the Config instances as const
const Config MAIN_CONFIG = {
    .name = "MainConfig",
    .value = 42
};

const Config BACKUP_CONFIG = {
    .name = "BackupConfig",
    .value = 24
};

// Initialize the System struct with pointers to the const Configs
const System SYSTEM = {
    .main_config = &MAIN_CONFIG,
    .backup_config = &BACKUP_CONFIG
};

/*
// Demo function to show usage
void printSystemConfig(const System *sys) {
    printf("Main Config: %s = %d\n", sys->main_config->name, sys->main_config->value);
    printf("Backup Config: %s = %d\n", sys->backup_config->name, sys->backup_config->value);
}

int main(void) {
    printSystemConfig(&SYSTEM);
    return 0;
}
*/




/*

First step is to make sure this works! We'll just use the O2 drum patterns as midi notes - make sure we can get a signal out...

*/
typedef struct
{
  unsigned char len;
  unsigned char drumpattern[];
  unsigned char basspattern[];
  unsigned char leadpattern[];
}patstruct;


typedef struct td_songstruct{
  unsigned char seqlen;
  patstruct patterns[];
  unsigned char sequence[];
}songstruct;


const patstruct song1patterns[2]  ={{
  8,
  {   0b00101100,      //Hard rock16
      0b00000000,
      0b00000100,
      0b00000000,
      0b00101110,
      0b00000000,
      0b00100100,
      0b00000000,},
  { 31, 32, 33, 34, 35, 36, 37, 38},
  { 91, 92, 93, 94, 95, 96, 97, 98},
},{
  8,
  {  1,  2,  3,  4,  5,  6,  7,  8},
  {  1,  2,  3,  4,  5,  6,  7,  8},
  {  1,  2,  3,  4,  5,  6,  7,  8},
}}; 


const songstruct song1 = {8,&song1patterns,{0,0,1,1,0,1,0,1}};

const unsigned char SONGCOUNT = 4;

void make_setlist(){

	

}



/*******************************************************************/
/* OLD METHODS: DELETE WHEN ABOVE IS WORKING! **********************/
/*******************************************************************/


const unsigned char midi_patlen[16] PROGMEM = {
    15,   //Hard Rock 16
    15,   //Disco 16
    15,   //Reggae 16
    15,   //Rock 16 - nearly "rock'n'roll" when this was 11
    15,   //Samba 16 - has BG2 
    15,   //Rumba 16 - has BG2
    15,   //ChaCha16
    15,   //Swing 16 - was 11
    15,   //Bossa Nova 16
    15,   //Bequine 16
    15,   //synthpop 16
    11,   //Boogie 12
    11,   //waltz 12
    11,   //jazz rock 12
    11,   //slow rock
    11    //Oxygene12
};




const unsigned char midi_pattern[256] PROGMEM = {
0b00101100,      //Hard rock16
0b00000000,
0b00000100,
0b00000000,
0b00101110,
0b00000000,
0b00100100,
0b00000000,
0b00101100,
0b00000000,
0b00000100,
0b00000000,
0b00101110,
0b00000000,
0b00000100,
0b00000000,


0b00100100,      //Disco16
0b00000000,
0b00000100,
0b00010100,
0b00100110,
0b00000000,
0b00000001,
0b00000100,
0b00100100,
0b00000000,
0b00000100,
0b00000100,
0b01100110,
0b00000100,
0b01000001,
0b00000000,

0b01000001,      //Reggae16
0b00000100,
0b10000000,
0b00000000,
0b00010110,
0b00000000,
0b10010000,
0b00000000,
0b00100000,
0b00000000,
0b10010000,
0b00000000,
0b00000110,
0b00000000,
0b10000100,
0b00000000,

0b00100100,      //Rock16
0b00000000,
0b00000100,
0b00000000,
0b00000110,
0b00000000,
0b00100100,
0b00000000,
0b00100100,
0b00000000,
0b00000100,
0b00000000,
0b00000110,
0b00000000,
0b00000110,
0b00000000,
  
0b10110101,      //Samba16
0b00010100,
0b10000100,
0b00010100,
0b10110100,
0b00000100,
0b01000100,
0b10010100,
0b00100100,
0b10010100,
0b01000100,
0b10010100,
0b10110101,
0b00000100,
0b10010100,
0b00000100,

0b00100110,      //Rumba16
0b00000100,
0b00000001,
0b00110100,
0b00100100,
0b00000001,
0b00010110,
0b00000100,
0b00100100,
0b00000100,
0b00010001,
0b00100100,
0b00110100,
0b00000100,
0b01000001,
0b00000100,

0b00100100,      //Cha-Cha16
0b00000000,
0b00000000,
0b00000000,
0b00000110,
0b00000000,
0b01000000,
0b00000000,
0b00100100,
0b00000000,
0b00000010,
0b00000000,
0b01000101,
0b00000000,
0b00000010,
0b00000000,

0b00100100,      //Swing16
0b00000000,
0b00000000,
0b00000000,
0b00000100,
0b00000000,
0b00000000,
0b00000100,
0b00000100,
0b00000000,
0b00000000,
0b00000000,
0b00000100,
0b00000000,
0b00000000,
0b00000100,

0b00100001,      //0bossa Nova16
0b00000100,
0b00000100,
0b00100100,
0b00100001,
0b00000100,
0b01000100,
0b00000100,
0b00100001,
0b00000100,
0b00000100,
0b00100000,
0b00100001,
0b01000101,
0b00000100,
0b00000100,

0b00100110,      //0beguine16
0b00000000,
0b00000001,
0b00000000,
0b00000100,
0b00000000,
0b01100110,
0b00000000,
0b00100100,
0b00000000,
0b01000100,
0b00000100,
0b00100110,
0b00000000,
0b00000100,
0b00000000,

0b10100000,      //Synthpop16
0b00000000,
0b10100010,
0b00000000,
0b00100000,
0b00000000,
0b00100110,
0b00000100,
0b01100000,
0b00000000,
0b01100110,
0b00000100,
0b00100000,
0b00000000,
0b00100010,
0b10001000,

/***********************************************/
// JAZZ ROCK 12 - 0bLANKED OUT...
        0b00000000,//0b00100110,      //Jazz rock12
        0b00000000,//0b00000000,
        0b00000000,//0b00000100,
        0b00000000,//0b00000000,
        0b00000000,//0b00000110,
        0b00000000,//0b00000000,
        0b00000000,//0b00000100,
        0b00000000,//0b00000000,
        0b00000000,//0b00000110,
        0b00000000,//0b00000000,
        0b00000000,//0b01100000,
        0b00000000,//0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,



//WALTZ 12 - DOUBLED THE TIME ON THIS SO IT MATCHES OXYGEN 12
0b00100100,      //Waltz12
0b00000000,
0b00010010,
0b00000000,
0b00010010,
0b00000000,
0b00100100,      //REPEAT
0b00000000,
0b00010010,
0b00000000,
0b00010010,
0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,


0b00100000,    //0boogie12
0b00000000,
0b00100100,
0b00000110,
0b00000000,
0b00100100,
0b00100100,
0b00000000,
0b00100100,
0b00000110,
0b00000000,
0b00100100,
    //////////unused bytes:
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,


//Slow rock12 - DOU0bLED THE TIME ON THIS SO IT MATCHES OXYGEN 12
0b00100100,    //Slow rock12 - 5/10, needed patlen fixing
0b00000100,
0b00100100,    //0b00000100,
0b00000110,
0b00000100,
0b00100100,
0b00100100,    //Slow rock12 - 5/10, needed patlen fixing
0b00000100,
0b00100100, //0b00000100,
0b00000110,
0b00000100,
0b00100100,
            //0b00100100,    //Slow rock12 - 5/10, needed patlen fixing
            //0b00000000,
            //0b00000100,
            //0b00000000,
            //0b00100100, //0b00000100,
            //0b00000000,
            //0b00000110,
            //0b00000000,
            //0b00000100,
            //0b00000000,
            //0b00100100,
            //0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

64,    //Test midi tune...
66,
68,
0,
90,
0,
0,
0,
36,
120,
40,
110,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000

};
