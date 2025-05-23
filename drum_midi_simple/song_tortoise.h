#define TAG_IATT i_am_the_tortoise




const unsigned char dp_TAG_IATT_1[] = {
          0b00110000, //1: Tortoise A
          0b10001000,
          0b00100010,
          0b00010000,
          0b00110000,
          0b00001000,
          0b00100010,
          0b10010000,
          0b00110000,
          0b10001000,
          0b00100010,
          0b10010000,
          0b00110000,
          0b00001000,
          0b00100010,
          0b00010010,
			};
const unsigned char bp_TAG_IATT_1[] = { D3, 0, 0,C3,
                                        D3,D3,C3, 0,
       					                        A2, 0, 0,G2,
                                        A2,A2,C3, 0};
const unsigned char lp_TAG_IATT_1[] = {  0, 0, 0, 0, 
                                         0, 0, 0, 0,
                                         0, 0, 0, 0, 
                                         0, 0, 0, 0};

const patstruct pat_TAG_IATT_1 = {
    .len = 16,
    .drumpattern = dp_TAG_IATT_1,
    .basspattern = bp_TAG_IATT_1,
    .leadpattern = lp_TAG_IATT_1
};

/////////////////////////////////////////////////////////////////////////////////

const patstruct *pa_block_TAG_IATT_1[] = {&pat_TAG_IATT_1, &pat_TAG_IATT_1, 
                                          &pat_TAG_IATT_1, &pat_TAG_IATT_1,
                                          &pat_TAG_IATT_1, &pat_TAG_IATT_1, 
                                          &pat_TAG_IATT_1, &pat_TAG_IATT_1};
const blockstruct block_TAG_IATT_1 = {
    .blocklen = 8,
    .patterns = pa_block_TAG_IATT_1
        
    };


const blockstruct *bl_song_TAG_IATT[] = {&block_TAG_IATT_1, &block_TAG_IATT_1, &block_TAG_IATT_1, &block_TAG_IATT_1,
         &block_TAG_IATT_1, &block_TAG_IATT_1};//, &block_TAG_IATT_1, &block_TAG_IATT_1}
const songstruct song_TAG_IATT = {
    .songlen = 6,
    .tempo = 4100,//3200 is too fast; 4400 is too slow
    .blocks = bl_song_TAG_IATT
    };
