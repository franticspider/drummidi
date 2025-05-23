



#define TAG_NUC   its_not_you_culture



const unsigned char dp_TAG_NUC_1[] = {   
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
        0b00000000};
const unsigned char bp_TAG_NUC_1[] = {D2, 0, 0, D2, 
					0, 0, D2, 0, 
					0, 0, 0, 0, 
					0, F2, 0, 0,
					D2, 0, 0, 0, 
					0, 0, 0, 0,
					D2, C2, 0, C2, 
					0, C2, 0, C2};
const unsigned char lp_TAG_NUC_1[] = {D2, 0, 0, D2, 
                                    0, 0, D2, 0, 
                                    0, 0, 0, 0, 
                                    0, F2, 0, 0,
                                    D2, 0, 0, 0, 
                                    0, 0, 0, 0,
                                    D2, C2, 0, C2, 
                                    0, C2, 0, C2};


const patstruct pat_TAG_NUC_1 = {
    .len = 32,
    .drumpattern = dp_TAG_NUC_1, 
    .basspattern = bp_TAG_NUC_1,
    .leadpattern = lp_TAG_NUC_1 
};


const patstruct *pa_block_TAG_NUC_1[] = {
        &pat_TAG_NUC_1, &pat_TAG_NUC_1, 
    		&pat_TAG_NUC_1, &pat_TAG_NUC_1,
    		&pat_TAG_NUC_1, &pat_TAG_NUC_1
    		};
const blockstruct block_TAG_NUC_1 = {
    .blocklen = 6,
    .patterns = pa_block_TAG_NUC_1
    };


const blockstruct *bl_song_TAG_NUC[] = {&block_TAG_NUC_1,&block_TAG_NUC_1,&block_TAG_NUC_1,&block_TAG_NUC_1};
const songstruct song_TAG_NUC = {
    .songlen = 4,
    .tempo = 4300,//4500 too slow
    .blocks = bl_song_TAG_NUC
    };



