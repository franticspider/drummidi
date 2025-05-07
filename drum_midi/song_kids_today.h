

/*
0b0000110, //9: Kids Today A
0b0100000,
0b0100100,
0b0000010,
0b0100100,
0b0100000,
0b0000110,
0b0100000,
0b0000110,
0b0100000,
0b0100100,
0b0000010,
0b0100100,
0b0100000,
0b0000110,
0b0100001,
*/

#define TAG_KT   kids_today

static const patstruct pat_TAG_KT_1 = {
    .len = 16,
    .drumpattern = /*(const unsigned char[])*/ {    
                        0b00000110, //9: Kids Today A
                        0b00100000,
                        0b00100100,
                        0b00000010,
                        0b00100100,
                        0b00100000,
                        0b00000110,
                        0b00100000,
                        0b00000110,
                        0b00100000,
                        0b00100100,
                        0b00000010,
                        0b00100100,
                        0b00100000,
                        0b00000110,
                        0b00100001
			},
    .basspattern = /*(const unsigned char[])*/ {0, 0, 0, 0,A2,G2,E2,E2,0, 0,E3, 0, 0,E2, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0}
};


static const patstruct pat_TAG_KT_2 = {
    .len = 16,
    .drumpattern = /*(const unsigned char[])*/ {    
                        0b00000110, //9: Kids Today A
                        0b00100000,
                        0b00100100,
                        0b00000010,
                        0b00100100,
                        0b00100000,
                        0b00000110,
                        0b00100000,
                        0b00000110,
                        0b00100000,
                        0b00100100,
                        0b00000010,
                        0b00100100,
                        0b00100000,
                        0b00000110,
                        0b00100001
			},
    .basspattern = /*(const unsigned char[])*/ {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0}
};

static const blockstruct block_TAG_KT_1 = {
    .blocklen = 8,
    .patterns = (const patstruct*[])   
        {&pat_TAG_KT_1,&pat_TAG_KT_2,&pat_TAG_KT_1,&pat_TAG_KT_2,
         &pat_TAG_KT_1,&pat_TAG_KT_2,&pat_TAG_KT_1,&pat_TAG_KT_2
         }
    };

static const songstruct song_TAG_KT = {
    .songlen = 2,
    .tempo = 2700,
    .blocks = (const blockstruct*[])   
        {&block_TAG_KT_1,&block_TAG_KT_1//,&block_TAG_KT_1,&block_TAG_KT_1,
         //&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1
         }
    };



