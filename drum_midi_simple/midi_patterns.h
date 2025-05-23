
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
  const unsigned char len;
  const unsigned char *drumpattern;
  const unsigned char *basspattern;
  const unsigned char *leadpattern;
}patstruct;
#endif




typedef struct {
  const unsigned char blocklen;
  const patstruct **patterns;
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
