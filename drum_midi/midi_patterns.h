


/* CHATGPT SUGGESTS:

#include <stdio.h>*/

// Define the Config struct with three const pointers
typedef struct {
    const char *name;        // Pointer to constant character data
    const int *value;        // Pointer to constant int
    const char *description; // Pointer to constant character data
} Config;

// Define the System struct pointing to an array of Configs
typedef struct {
    const Config *configs;
    const size_t config_count;
} System;

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
  const unsigned char len;
  const unsigned char PROGMEM *drumpattern;
  const unsigned char PROGMEM *basspattern;
  const unsigned char PROGMEM *leadpattern;
}patstruct;


typedef struct {
  const unsigned char blocklen;
  const patstruct **patterns;
}blockstruct;


typedef struct {
  const unsigned char songlen;
  const blockstruct **blocks;
}songstruct;


typedef struct {
  const unsigned char setlen;
  const songstruct **songs;
}setstruct;


/*******************************************************************/
/* CLASS METHODS: MORE PORTABLE THAN STRUCTS! **********************/
/*******************************************************************/

	
class PattClass {
public:
	

    unsigned char len;
    unsigned char *drumpattern;
    unsigned char *basspattern;
    unsigned char *leadpattern;	

    void add_drum_pattern(unsigned char len, unsigned char * pattern){
    }
};

/*
class Song {
private:
    const uint8_t _numPatterns;
    const Pattern* const* _patterns;  // pointer to array of pointers to Pattern

public:
    Song(uint8_t numPatterns, const Pattern* const* patterns)
        : _numPatterns(numPatterns), _patterns(patterns) {}

    uint8_t length() const {
        return _numPatterns;
    }

    const Pattern* getPattern(uint8_t index) const {
        if (index >= _numPatterns) return nullptr;
        return _patterns[index];
    }
};
*/

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
