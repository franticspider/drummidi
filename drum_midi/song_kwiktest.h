



#define TAG_KW  kwik_test



const unsigned char dp_pat_TAG_KW_1[] = {    
                          0b00101100,      //Hard rock16
                          0b00000000,
                          0b00000100,
                          0b00000000,
                          0b00101110,
                          0b00000000,
                          0b00100100,
                          0b00000000};
const unsigned char bp_pat_TAG_KW_1[] = {31, 32, 33, 34, 35, 36, 37, 38};
const unsigned char lp_pat_TAG_KW_1[] = {91, 92, 93, 94, 95, 96, 97, 98};
const patstruct pat_TAG_KW_1 = {
    .len = 8,
    .drumpattern = dp_pat_TAG_KW_1,
    .basspattern = bp_pat_TAG_KW_1,
    .leadpattern = lp_pat_TAG_KW_1 
};




const unsigned char bp_pat_TAG_KW_2[] = {39, 42, 43, 44, 55, 66, 87, 98};
const unsigned char lp_pat_TAG_KW_2[] = {91, 91, 91, 103, 103, 91, 103, 103};
const patstruct pat_TAG_KW_2 = {
    .len = 8,
    .drumpattern = dp_pat_TAG_KW_1,
    .basspattern = bp_pat_TAG_KW_2,
    .leadpattern = lp_pat_TAG_KW_2 
};




const unsigned char bp_pat_TAG_KW_3[] = {49, 52, 53, 54, 65, 76, 87, 108};
const unsigned char lp_pat_TAG_KW_3[] = {91, 91, 91, 103, 103, 91, 103, 103};
const patstruct pat_TAG_KW_3 = {
    .len = 8,
    .drumpattern = dp_pat_TAG_KW_1,
    .basspattern = bp_pat_TAG_KW_3,
    .leadpattern = lp_pat_TAG_KW_3 
};

////////////////////////////////////////////////////////////////////////////////

const patstruct *pa_block_TAG_KW_1[] = {&pat_TAG_KW_1, &pat_TAG_KW_2, &pat_TAG_KW_1, &pat_TAG_KW_2};
const blockstruct block_TAG_KW_1 = {
    .blocklen = 4,
    .patterns = pa_block_TAG_KW_1
    };

const patstruct *pa_block_TAG_KW_2[] = {&pat_TAG_KW_3, &pat_TAG_KW_3, &pat_TAG_KW_3, &pat_TAG_KW_1, &pat_TAG_KW_3, &pat_TAG_KW_3};
const blockstruct block_TAG_KW_2 = {
    .blocklen = 6,
    .patterns = pa_block_TAG_KW_2
    };

////////////////////////////////////////////////////////////////////////////////

const blockstruct *bl_song_TAG_KW[] = {&block_TAG_KW_1, &block_TAG_KW_2, &block_TAG_KW_1, &block_TAG_KW_2};
const songstruct song_TAG_KW = {
    .songlen = 4,
    .tempo = 4300,
    .blocks = bl_song_TAG_KW
    };


