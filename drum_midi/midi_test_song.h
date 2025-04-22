


/* CHATGPT SUGGESTS:

#include <stdio.h>*/


// Define actual values to be pointed to
const int VALUE_MAIN = 42;
const int VALUE_BACKUP = 24;
const int VALUE_EXTRA = 99;

// Define a const array of Configs with pointers to the above values
const Config CONFIG_ARRAY[] = {
    { .name = "MainConfig",   .value = &VALUE_MAIN,   .description = "Primary configuration settings" },
    { .name = "BackupConfig", .value = &VALUE_BACKUP, .description = "Fallback configuration" },
    { .name = "ExtraConfig",  .value = &VALUE_EXTRA,  .description = "Extra features or debugging" }
};

// Initialize the System
const System SYSTEM = {
    .configs = CONFIG_ARRAY,
    .config_count = sizeof(CONFIG_ARRAY) / sizeof(CONFIG_ARRAY[0])
};

/*
// Demo function to show usage
void printSystemConfig(const System *sys) {
    printf("Main Config: %s = %d\n", sys->main_config->name, sys->main_config->value);
    printf("Backup Config: %s = %d\n", sys->backup_config->name, sys->backup_config->value);
}

int main(void) {
    printSystemConfig(&SYSTEM);
    return 0;
}
*/

const patstruct testpat1 = {
    .len = 8,
    .drumpattern = (const unsigned char[]) {    0b00101100,      //Hard rock16
                          0b00000000,
                          0b00000100,
                          0b00000000,
                          0b00101110,
                          0b00000000,
                          0b00100100,
                          0b00000000},
    .basspattern = (const unsigned char[]) {31, 32, 33, 34, 35, 36, 37, 38},
    .leadpattern = (const unsigned char[]) {91, 92, 93, 94, 95, 96, 97, 98}
};


const patstruct testpat2 = {
    .len = 8,
    .drumpattern = (const unsigned char[]) {    0b00101100,      //Hard rock16
                          0b00101100,
                          0b00000100,
                          0b00000100,
                          0b00101110,
                          0b00101110,
                          0b00100100,
                          0b00101110},
    //.drumpattern = (const unsigned char[]){39, 42, 43, 44, 55, 66, 87, 98}, 
    .basspattern = (const unsigned char[]){39, 42, 43, 44, 55, 66, 87, 98},
    .leadpattern = (const unsigned char[]){91, 92, 93, 94, 95, 96, 97, 98}
};

/*
const blockstruct testblock1 = {
    .blocklen = 4,
    .patterns = (const patstruct**){&testpat1, &testpat1, &testpat1, &testpat2}
};*/






/*

First step is to make sure this works! We'll just use the O2 drum patterns as midi notes - make sure we can get a signal out...



const patstruct song1patterns[2]  ={{
  8,
  {   0b00101100,      //Hard rock16
      0b00000000,
      0b00000100,
      0b00000000,
      0b00101110,
      0b00000000,
      0b00100100,
      0b00000000,},
  { 31, 32, 33, 34, 35, 36, 37, 38},
  { 91, 92, 93, 94, 95, 96, 97, 98},
},{
  8,
  {  1,  2,  3,  4,  5,  6,  7,  8},
  {  1,  2,  3,  4,  5,  6,  7,  8},
  {  1,  2,  3,  4,  5,  6,  7,  8},
}}; 


const songstruct song1 = {8,&song1patterns,{0,0,1,1,0,1,0,1}};

const unsigned char SONGCOUNT = 4;

void make_setlist(){

	

}
*/


