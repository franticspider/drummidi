

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


const unsigned char dp_TAG_KT_1[] = {
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
};
const unsigned char bp_TAG_KT_1[] = {0, 0, 0, 0,A2,G2,E2,E2,0, 0,E3, 0, 0,E2, 0, 0};
const unsigned char lp_TAG_KT_1[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};

const patstruct pat_TAG_KT_1 = {
    .len = 16,
    .drumpattern = dp_TAG_KT_1,
    .basspattern = bp_TAG_KT_1,
    .leadpattern = lp_TAG_KT_1
};


static const patstruct pat_TAG_KT_2 = {
    .len = 16,
    .drumpattern = dp_TAG_KT_1,
    .basspattern = lp_TAG_KT_1, //NOT AN ERROR! just an empty pattern..
    .leadpattern = lp_TAG_KT_1
};

///////////////////////////////////////////////////////////////////////////////

const patstruct *pa_block_TAG_KT_1[] = {&pat_TAG_KT_1, &pat_TAG_KT_2,
                                        &pat_TAG_KT_2, &pat_TAG_KT_2,
                                        //&pat_TAG_KT_1, &pat_TAG_KT_1,
                                        &pat_TAG_KT_1, &pat_TAG_KT_2};
static const blockstruct block_TAG_KT_1 = {
    .blocklen = 6,
    .patterns = pa_block_TAG_KT_1
    };

const blockstruct *bl_song_TAG_KT[] = {&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1,
         &block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1,&block_TAG_KT_1
         };
static const songstruct song_TAG_KT = {
    .songlen = 8,
    .tempo = 2700,
    .blocks = bl_song_TAG_KT
    };



