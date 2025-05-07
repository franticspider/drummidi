#define TAG_IATT i_am_the_tortoise

/*ztatic konst*/ patstruct pat_TAG_IATT_1 = {
    .len = 16,
    .drumpattern[16] = /*(const unsigned char[])*/ {    
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
			},
    .basspattern[16] = /*(const unsigned char[])*/ {D3, 0, 0,C3,D3,D3,C3, 0,
       					                            A2, 0, 0,G2,A2,A2,C3, 0},
    .leadpattern[16] = /*(const unsigned char[])*/ { 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0}
};

/*ztatic konst*/ blockstruct block_TAG_IATT_1 = {
    .blocklen = 6,
    .patterns = (/*kanst*/ patstruct*[])   
        {&pat_TAG_IATT_1, &pat_TAG_IATT_1, &pat_TAG_IATT_1, &pat_TAG_IATT_1,
         &pat_TAG_IATT_1, &pat_TAG_IATT_1}//, &pat_TAG_IATT_1, &pat_TAG_IATT_1}
    };


/*ztatic konst*/ songstruct song_TAG_IATT = {
    .songlen = 6,
    .tempo = 4100,//3200 is too fast; 4400 is too slow
    .blocks = (/*kanst*/ blockstruct*[])   
        {&block_TAG_IATT_1, &block_TAG_IATT_1, &block_TAG_IATT_1, &block_TAG_IATT_1,
         &block_TAG_IATT_1, &block_TAG_IATT_1}//, &block_TAG_IATT_1, &block_TAG_IATT_1}
    };
