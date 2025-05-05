#define TAG_IATT i_am_the_tortoise

static const patstruct pat_TAG_IATT_1 = {
    .len = 16,
    .drumpattern = (const unsigned char[]) {    
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
    .basspattern = (const unsigned char[]) {D3, 0, 0,C3,D3,D3,C3, 0,
       					                            A2, 0, 0,G2,A2,A2,C3, 0},
    .leadpattern = (const unsigned char[]) { 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0}
};

static const blockstruct block_TAG_IATT_1 = {
    .blocklen = 6,
    .patterns = (const patstruct*[])   
        {&pat_TAG_IATT_1, &pat_TAG_IATT_1, &pat_TAG_IATT_1, &pat_TAG_IATT_1,
         &pat_TAG_IATT_1, &pat_TAG_IATT_1}//, &pat_TAG_IATT_1, &pat_TAG_IATT_1}
    };


static const songstruct song_TAG_IATT = {
    .songlen = 6,
    .tempo = 4100,//3200 is too fast; 4400 is too slow
    .blocks = (const blockstruct*[])   
        {&block_TAG_IATT_1, &block_TAG_IATT_1, &block_TAG_IATT_1, &block_TAG_IATT_1,
         &block_TAG_IATT_1, &block_TAG_IATT_1}//, &block_TAG_IATT_1, &block_TAG_IATT_1}
    };
