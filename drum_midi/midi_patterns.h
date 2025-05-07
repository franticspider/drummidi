
#ifdef USE_PROGMEM

/*
First step is to make sure this works! We'll just use the O2 drum patterns as midi notes - make sure we can get a signal out...
*/
typedef struct
{
  /*konst*/ unsigned char len;
  /*konst*/ unsigned char PROGMEM *drumpattern;
  /*konst*/ unsigned char PROGMEM *basspattern;
  /*konst*/ unsigned char PROGMEM *leadpattern;
}patstruct;
#else
typedef struct
{
  /*konst*/ unsigned char len;
  const unsigned char drumpattern[];
  /*konst*/ unsigned char basspattern[];
  /*konst*/ unsigned char leadpattern[];
}patstruct;
#endif




typedef struct {
  /*konst*/ unsigned char blocklen;
  /*konst*/ patstruct **patterns;
}blockstruct;


typedef struct {
  /*konst*/ unsigned char songlen;
  /*konst*/ unsigned short tempo;
  /*konst*/ blockstruct **blocks;
}songstruct;


typedef struct {
  /*konst*/ unsigned char setlen;
  /*konst*/ songstruct **songs;
}setstruct;
