

const unsigned char dp_id_song_1[] = {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010};
const unsigned char bp_id_song_1[] = {C2, 0, 0, 0, 0, 0, 0, 0};
const unsigned char lp_id_song_1[] = {C2, 0, 0, 0, 0, 0, 0, 0};
const patstruct id_song_1 = {
    .len = 8,
    .drumpattern = dp_id_song_1,
    .basspattern = bp_id_song_1 ,
    .leadpattern = lp_id_song_1 
};




const unsigned char dp_id_song_2[] = {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010};
const unsigned char bp_id_song_2[] = {C2,C2, 0, 0, 0, 0, 0, 0};
const unsigned char lp_id_song_2[] = {C2,C2, 0, 0, 0, 0, 0, 0};
const patstruct id_song_2 = {
    .len = 8,
    .drumpattern = dp_id_song_2,
    .basspattern = bp_id_song_2,
    .leadpattern = lp_id_song_2 
};




const unsigned char dp_id_song_3[] = {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010};
const unsigned char bp_id_song_3[] = {C3,C3,C3, 0, 0, 0, 0, 0};
const unsigned char lp_id_song_3[] = {C3,C3,C3, 0, 0, 0, 0, 0};
const patstruct id_song_3 = {
    .len = 8,
    .drumpattern = dp_id_song_3,
    .basspattern = bp_id_song_3,
    .leadpattern = lp_id_song_3 
};




const unsigned char dp_id_song_4[] = {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b01100010,
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010};
const unsigned char bp_id_song_4[] = {C4,C4,C4,C4, 0, 0, 0, 0};
const patstruct id_song_4 = {
    .len = 8,
    .drumpattern = dp_id_song_4,
    .basspattern = bp_id_song_4,
    .leadpattern = bp_id_song_4   //NOT AN ERROR!
};




const unsigned char dp_id_song_5[] = {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b01100010,
                          0b01100010,
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010};
const unsigned char bp_id_song_5[] = {C5,C5,C5,C5,C5, 0, 0, 0};
const patstruct id_song_5 = {
    .len = 8,
    .drumpattern = dp_id_song_5,
    .basspattern = bp_id_song_5,
    .leadpattern = bp_id_song_5   //NOT AN ERROR!
};





const patstruct *pa_block_id_1[] = {&id_song_1};
const blockstruct block_id_1 = {
    .blocklen = 1,
    .patterns = pa_block_id_1
    };



const patstruct *pa_block_id_3[] = {&id_song_3};
const blockstruct block_id_3 = {
    .blocklen = 1,
    .patterns = pa_block_id_3
    };



const patstruct *pa_block_id_4[] = {&id_song_4};
const blockstruct block_id_4 = {
    .blocklen = 1,
    .patterns = pa_block_id_4
    };



const patstruct *pa_block_id_5[] = {&id_song_5};
const blockstruct block_id_5 = {
    .blocklen = 1,
    .patterns = pa_block_id_5
    };
    
///////////////////////////////////////////////////////////////////////////////

const blockstruct *bl_testsong3[] =  {&block_id_3};
const songstruct testsong3 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = bl_testsong3
    };

const blockstruct *bl_testsong4[] =  {&block_id_4};
const songstruct testsong4 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = bl_testsong4
    };

const blockstruct *bl_testsong5[] =  {&block_id_5};
const songstruct testsong5 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = bl_testsong5
    };

/*
const songstruct testsong4 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = {&block_id_4}
    };


const songstruct testsong5 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = {&block_id_5}
    };
*/


const songstruct *so_testset[] = {&song_TAG_KW, &song_TAG_KT, &song_TAG_IATT, &song_TAG_JT, &song_TAG_NUC};
const setstruct testset = {
    .setlen = 5,
    .songs = so_testset
    }; 




