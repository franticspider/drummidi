
/*ztatic konst*/ patstruct id_song_1 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010},
    .basspattern = /*(const unsigned char[])*/ {C2, 0, 0, 0, 0, 0, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {C2, 0, 0, 0, 0, 0, 0, 0}
};



/*ztatic konst*/ patstruct id_song_2 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010},
    .basspattern = /*(const unsigned char[])*/ {C2, C2, 0, 0, 0, 0, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {C2, C2, 0, 0, 0, 0, 0, 0}
};



/*ztatic konst*/ patstruct not_you_culture_1 = {
    .len = 32,
    .drumpattern = /*(const unsigned char[])*/ {   
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
        0b00000000,
    },
    .basspattern = /*(const unsigned char[])*/ {D2, 0, 0, D2, 
                                            0, 0, D2, 0, 
                                            0, 0, 0, 0, 
                                            0, F2, 0, 0,
                                            D2, 0, 0, 0, 
                                            0, 0, 0, 0,
                                            D2, C2, 0, C2, 
                                            0, C2, 0, C2},
    .leadpattern = /*(const unsigned char[])*/ {D2, 0, 0, D2, 
                                            0, 0, D2, 0, 
                                            0, 0, 0, 0, 
                                            0, F2, 0, 0,
                                            D2, 0, 0, 0, 
                                            0, 0, 0, 0,
                                            D2, C2, 0, C2, 
                                            0, C2, 0, C2}
};

/*ztatic konst*/ blockstruct block_id_2 = {
    .blocklen = 6,
    .patterns = (/*kanst*/ patstruct*[]){
        	&not_you_culture_1, &not_you_culture_1, 
    		&not_you_culture_1, &not_you_culture_1,
    		&not_you_culture_1, &not_you_culture_1
    		}
    };


/*ztatic konst*/ songstruct song_not_u_culture = {
    .songlen = 4,
    .tempo = 4300,//4500 too slow
    .blocks = (/*kanst*/ blockstruct*[]){&block_id_2,&block_id_2,&block_id_2,&block_id_2}
    };



/*ztatic konst*/ patstruct id_song_3 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010},
    .basspattern = /*(const unsigned char[])*/ {C3, C3, C3, 0, 0, 0, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {C3, C3, C3, 0, 0, 0, 0, 0}
};


/*ztatic konst*/ patstruct id_song_4 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b01100010,
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010,
                          0b00000010},
    .basspattern = /*(const unsigned char[])*/ {C4, C4, C4, C4, 0, 0, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {C4, C4, C4, C4, 0, 0, 0, 0}
};


/*ztatic konst*/ patstruct id_song_5 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {    
                          0b01100010,      //snarey repeat so we have a counter
                          0b01100010,
                          0b01100010,
                          0b01100010,
                          0b01100010,
                          0b00000010,
                          0b00000010,
                          0b00000010},
    .basspattern = /*(const unsigned char[])*/ {C5, C5, C5, C5, C5, 0, 0, 0},
    .leadpattern = /*(const unsigned char[])*/ {C5, C5, C5, C5, C5, 0, 0, 0}
};



/*ztatic konst*/ patstruct testpat1 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {    
                          0b00101100,      //Hard rock16
                          0b00000000,
                          0b00000100,
                          0b00000000,
                          0b00101110,
                          0b00000000,
                          0b00100100,
                          0b00000000},
    .basspattern = /*(const unsigned char[])*/ {31, 32, 33, 34, 35, 36, 37, 38},
    .leadpattern = /*(const unsigned char[])*/ {91, 92, 93, 94, 95, 96, 97, 98}
};


/*ztatic konst*/ patstruct testpat2 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {
                          0b00101100,      //Hard rock16
                          0b00101100,
                          0b00000100,
                          0b00000100,
                          0b00101110,
                          0b00101110,
                          0b00100100,
                          0b00101110},
    .basspattern = /*(const unsigned char[])*/{39, 42, 43, 44, 55, 66, 87, 98},
    .leadpattern = /*(const unsigned char[])*/{91, 91, 91, 103, 103, 91, 103, 103}
};


/*ztatic konst*/ patstruct testpat3 = {
    .len = 8,
    .drumpattern = /*(const unsigned char[])*/ {
                          0b00101100,      //Hard rock16
                          0b00101100,
                          0b00000100,
                          0b00000100,
                          0b00101110,
                          0b00101110,
                          0b00100100,
                          0b00101110},
    .basspattern = /*(const unsigned char[])*/{49, 52, 53, 54, 65, 76, 87, 108},
    .leadpattern = /*(const unsigned char[])*/{91, 91, 91, 103, 103, 91, 103, 103}
};


/*ztatic konst*/ blockstruct block_id_1 = {
    .blocklen = 1,
    .patterns = (/*kanst*/ patstruct*[]){&id_song_1}
    };






/*ztatic konst*/ blockstruct block_id_3 = {
    .blocklen = 1,
    .patterns = (/*kanst*/ patstruct*[]){&id_song_3}
    };


/*ztatic konst*/ blockstruct block_id_4 = {
    .blocklen = 1,
    .patterns = (/*kanst*/ patstruct*[]){&id_song_4}
    };


/*ztatic konst*/ blockstruct block_id_5 = {
    .blocklen = 1,
    .patterns = (/*kanst*/ patstruct*[]){&id_song_5}
    };


/*ztatic konst*/ blockstruct testblock1 = {
    .blocklen = 4,
    .patterns = (/*kanst*/ patstruct*[]){&testpat1, &testpat2, 
                                     &testpat1, &testpat2}
    };


/*ztatic konst*/ blockstruct testblock2 = {
    .blocklen = 6,
    .patterns = (/*kanst*/ patstruct*[]){&testpat3, &testpat3, &testpat3,         
                                     &testpat1, &testpat3, &testpat3}
    };




/*ztatic konst*/ songstruct testsong1 = {
    .songlen = 6,
    .tempo = 4300,
    .blocks = (/*kanst*/ blockstruct*[]){&block_id_1,&block_id_1,&testblock1, 
                                    &testblock2,
                                    &testblock1, &testblock2}
    };

/*ztatic konst*/ songstruct testsong3 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = (/*kanst*/ blockstruct*[]){&block_id_3}
    };


/*ztatic konst*/ songstruct testsong4 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = (/*kanst*/ blockstruct*[]){&block_id_4}
    };


/*ztatic konst*/ songstruct testsong5 = {
    .songlen = 1,
    .tempo = 3500,
    .blocks = (/*kanst*/ blockstruct*[]){&block_id_5}
    };

/*ztatic konst*/ setstruct testset = {
    .setlen = 5,
    .songs = (/*kanst*/ songstruct*[]){&song_TAG_JT, &song_TAG_IATT,  &song_TAG_KT, &song_not_u_culture,   &testsong1}
    }; 




