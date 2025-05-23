



#define TAG_JT   jako_thing



const unsigned char dp_TAG_JT_1[] = {   
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
			};


const unsigned char bp_TAG_JT_1[] = {0,A2,A3,   0, 0 ,0,   G2,E2,0,   0,E3, 0};
const unsigned char lp_TAG_JT_1[] = {0, 0, 0,   0, D6, D6,   0, 0,0,   C6,C6,0};


static const patstruct pat_TAG_JT_1 = { 
    .len = 12,
    .drumpattern = dp_TAG_JT_1,
    .basspattern = bp_TAG_JT_1,
    .leadpattern = lp_TAG_JT_1
};




const patstruct *pa_block_TAG_JT_1[] = {
            &pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,
            &pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,
            &pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1,&pat_TAG_JT_1
         };
const blockstruct block_TAG_JT_1 = {
    .blocklen = 12,
    .patterns = pa_block_TAG_JT_1  
    };


const blockstruct *bl_song_TAG_JT[] = {
          &block_TAG_JT_1, &block_TAG_JT_1, &block_TAG_JT_1, &block_TAG_JT_1,
          &block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1
          };
static const songstruct song_TAG_JT = {
    .songlen = 8,
    .tempo = 3000,
    .blocks = bl_song_TAG_JT
    };



