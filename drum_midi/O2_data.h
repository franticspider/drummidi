
// HASHDEFINES FOR SAMPLE LENGTH:

//NB! in first working version (that made nice patterns), clipping was applied to BD,BG2,QU

/* Patterns GU BG2 BD CL CW MA CY QU

15 sounds: Bass, Snare 1, Snare 2, Rimshot, High-Hat, Cymbal 1, Cymbal 2, Cowbell, Conga, Large Bongo, Small Bongo, Claves, Quijada, Guiro, Tambourine.

GU  = Guiro
BG2 = Small bongo?
BD  = Bass Drum
CL  = Claves
CW  = Cowbell
MA  = ?maraca? - not listed as a voice above.. 
CY  = cymbal
QU  = Quijada



16 steps
------------
Hard rock
Disco
Reggae
Rock
Samba
Rumba
Cha-Cha
Swing
Bossa Nova
Beguine
Synthpop

12-steps
---------
Boogie
Waltz
Jazz rock
Slow rock
Oxygen

 */

const unsigned char patlen[16] PROGMEM = {
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

/* PATTERN NOTES - nb these are not linear pots!!

#   dial
    0700-0930 - test pattern - fix to make a better beat
    0930-1130 - good! use for emom 2407
    1200-1230 -reggae16
    1230-1200 - rock16
    1300 - samba16  
    1330 - rumba 16
    1400 - chacha16 - not so good 


*/


const unsigned char pattern[256] PROGMEM = {
/*B00101100,      //Hard rock16
B00000000,
B00000100,
B00000000,
B00101110,
B00000000,
B00100100,
B00000000,
B00101100,
B00000000,
B00000100,
B00000000,
B00101110,
B00000000,
B00000100,
B00000000,


*/
//Test Pattern:    Effects table:                                 HDRRSRCSBBSBWJSO                
B00000000, //      pitch   trim   bitcrush   pitch2   Len   Type  0123456789abcdef Name
B10000000, // GU    X       *                 X       2816  bzzt     48            Guiro        not really suited to pitch changes
B01000000, // BG2   *       *      *                  1136  tom                    Small Bongo  great effects with low pitch
B00100000, // BD                              *       1076  tom   44               Bass Drum
B00010000, // CL            *      *                   752  tom   4                Claves
B00001000, // CW            *      *                   830  tom   8                Cowbell
B00000100, // MA            *                          568  noiz                   Maraca?      like a closed hihat
B00000010, // CY            *      *          *       9434  noiz  2                Cymbal       more like a snare, esp when trimmed
B00000001, // QU            *      *                  7712  bzzt                   Quijada
B00000000,
B00000000,
B11111111,
B00000000,
B11111111,
B00000000,
B00000000,
/*NOTES on the TEST Pattern:
- which is the best "snare" sound of these?
- strategy: test *all* effects on *all* sounds - record it! and see 

- Do we leave the bass drum un modified for *all* effects? 

- samplepitch2 should be for the more 'extreme' 
*/

/*
B00100100,      //Disco16
B00000000,
B00000100,
B00010100,
B00100110,
B00000000,
B00000001,
B00000100,
B00100100,
B00000000,
B00000100,
B00000100,
B01100110,
B00000100,
B01000001,
B00000000,*/


B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,

B01000001,      //Reggae16
B00000100,
B10000000,
B00000000,
B00010110,
B00000000,
B10010000,
B00000000,
B00100000,
B00000000,
B10010000,
B00000000,
B00000110,
B00000000,
B10000100,
B00000000,

B00100100,      //Rock16
B00000000,
B00000100,
B00000000,
B00000110,
B00000000,
B00100100,
B00000000,
B00100100,
B00000000,
B00000100,
B00000000,
B00000110,
B00000000,
B00000110,
B00000000,
  
B10110101,      //Samba16
B00010100,
B10000100,
B00010100,
B10110100,
B00000100,
B01000100,
B10010100,
B00100100,
B10010100,
B01000100,
B10010100,
B10110101,
B00000100,
B10010100,
B00000100,

B00100110,      //Rumba16
B00000100,
B00000001,
B00110100,
B00100100,
B00000001,
B00010110,
B00000100,
B00100100,
B00000100,
B00010001,
B00100100,
B00110100,
B00000100,
B01000001,
B00000100,

B00100100,      //Cha-Cha16
B00000000,
B00000000,
B00000000,
B00000110,
B00000000,
B01000000,
B00000000,
B00100100,
B00000000,
B00000010,
B00000000,
B01000101,
B00000000,
B00000010,
B00000000,

B00100100,      //Swing16
B00000000,
B00000000,
B00000000,
B00000100,
B00000000,
B00000000,
B00000100,
B00000100,
B00000000,
B00000000,
B00000000,
B00000100,
B00000000,
B00000000,
B00000100,

B00100001,      //Bossa Nova16
B00000100,
B00000100,
B00100100,
B00100001,
B00000100,
B01000100,
B00000100,
B00100001,
B00000100,
B00000100,
B00100000,
B00100001,
B01000101,
B00000100,
B00000100,

B00100110,      //Beguine16
B00000000,
B00000001,
B00000000,
B00000100,
B00000000,
B01100110,
B00000000,
B00100100,
B00000000,
B01000100,
B00000100,
B00100110,
B00000000,
B00000100,
B00000000,

B10100000,      //Synthpop16
B00000000,
B10100010,
B00000000,
B00100000,
B00000000,
B00100110,
B00000100,
B01100000,
B00000000,
B01100110,
B00000100,
B00100000,
B00000000,
B00100010,
B10001000,

/***********************************************/
// JAZZ ROCK 12 - BLANKED OUT...
        B00000000,//B00100110,      //Jazz rock12
        B00000000,//B00000000,
        B00000000,//B00000100,
        B00000000,//B00000000,
        B00000000,//B00000110,
        B00000000,//B00000000,
        B00000000,//B00000100,
        B00000000,//B00000000,
        B00000000,//B00000110,
        B00000000,//B00000000,
        B00000000,//B01100000,
        B00000000,//B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,



//WALTZ 12 - DOUBLED THE TIME ON THIS SO IT MATCHES OXYGEN 12
B00100100,      //Waltz12
B00000000,
B00010010,
B00000000,
B00010010,
B00000000,
B00100100,      //REPEAT
B00000000,
B00010010,
B00000000,
B00010010,
B00000000,
        //B00100100,      //Waltz12
        //B00000000,
        //B00000000,
        //B00000000,
        //B00010010,
        //B00000000,
        //B00000000,
        //B00000000,
        //B00010010,
        //B00000000,
        //B00000000,
        //B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,


B00100000,    //Boogie12
B00000000,
B00100100,
B00000110,
B00000000,
B00100100,
B00100100,
B00000000,
B00100100,
B00000110,
B00000000,
B00100100,
    //////////unused bytes:
    B00000000,
    B00000000,
    B00000000,
    B00000000,


//Slow rock12 - DOUBLED THE TIME ON THIS SO IT MATCHES OXYGEN 12
B00100100,    //Slow rock12 - 5/10, needed patlen fixing
B00000100,
B00100100,    //B00000100,
B00000110,
B00000100,
B00100100,
B00100100,    //Slow rock12 - 5/10, needed patlen fixing
B00000100,
B00100100, //B00000100,
B00000110,
B00000100,
B00100100,
            //B00100100,    //Slow rock12 - 5/10, needed patlen fixing
            //B00000000,
            //B00000100,
            //B00000000,
            //B00100100, //B00000100,
            //B00000000,
            //B00000110,
            //B00000000,
            //B00000100,
            //B00000000,
            //B00100100,
            //B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,

B00100101,    //Oxygen12: Love this- would be great to figure out which 2 patterns are joined together...!
B00001100,
B00000100,
B00101110,
B00000100,
B00010100,
B00100101,
B00000100,
B00000100,
B00101100,
B00000100,
B11100100,
    B00000000,
    B00000000,
    B00000000,
    B00000000

};




