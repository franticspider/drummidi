
#ifdef USE_PROGMEM

/*
First step is to make sure this works! We'll just use the O2 drum patterns as midi notes - make sure we can get a signal out...
*/
typedef struct
{
  const unsigned char len;
  const unsigned char PROGMEM *drumpattern;
  const unsigned char PROGMEM *basspattern;
  const unsigned char PROGMEM *leadpattern;
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
  const unsigned char songlen;
  const unsigned short tempo;
  const blockstruct **blocks;
}songstruct;


typedef struct {
  const unsigned char setlen;
  const songstruct **songs;
}setstruct;
