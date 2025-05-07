



#define TAG_JT   jako_thing

static const patstruct pat_TAG_JT_1 = {
    .len = 12,
    .drumpattern = /*(const unsigned char[])*/ {    
                        0b01100100,
                        0b00000000,
                        0b00000100, 
                        0b00100100,
                        0b00000110,
                        0b00010000, 
                        0b01100100,
                        0b00000100,
                        0b00000100, 
                        0b01100000,
                        0b01000000,
                        0b00000000
			},
    .basspattern = /*(const unsigned char[])*/ {0,A2,A3,   0, 0 ,0,   G2,E2,0,   0,E3, 0},
    .leadpattern = /*(const unsigned char[])*/ {0, 0, 0,   0, D5, D5,   0, 0,0,   C5,C5,0}
};


static const blockstruct block_TAG_JT_1 = {
    .blocklen = 4,
    .patterns = (const patstruct*[])   
        {//&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,
         //&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,
         &pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1
         }
    };

static const songstruct song_TAG_JT = {
    .songlen = 8,
    .tempo = 3000,
    .blocks = (const blockstruct*[])   
        {&block_TAG_JT_1, &block_TAG_JT_1, &block_TAG_JT_1, &block_TAG_JT_1,
         &block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1
         }
    };



