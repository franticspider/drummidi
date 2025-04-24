#include <stdlib.h>
#include <stdio.h>

#include "catch.hpp"

//use a define to remove this specifier...
#define PROGMEM

#include "../drum_midi/midi_patterns.h"
#include "../drum_midi/midi_test_song.h"

#define SONGCOUNT (16)

TEST_CASE("pattern memory allocation is valid"){
	

    for(unsigned char ss = 0; ss< SONGCOUNT; ss++){

        if(ss<testset.setlen){

	    if(testset.songs[ss] != NULL){
	        printf("SONG %02d:\n",ss);
	        songstruct const * song = testset.songs[ss];
	        
	        for(unsigned char bb = 0; bb< song->songlen; bb++){
	        
	            blockstruct const * block = song->blocks[bb];
	            printf("  BLOCK %02d:\n",bb);
	        
	            for(unsigned char pp = 0; pp< block->blocklen; pp++){
	            
	                patstruct const * patt = block->patterns[pp];
	                printf("    PATTERN %02d:\n",pp);
	                for(unsigned char cc = 0; cc<patt->len; cc++){
	                    printf("%03u, %03u, %03u\n",
	                        patt->drumpattern[cc],
	                        patt->basspattern[cc],
	                        patt->leadpattern[cc]);
	                }
	            }	    
	        }
	    }else{
	        printf("Slot %d is NULL\n",ss);
	    }
        }else{
	    printf("Slot %d not set\n",ss);
        }
    }

}


TEST_CASE("mechanism for playing song works in context"){


    //PLAYING OR NOT:
    bool playing = true;

    //SET UP SONG
    unsigned char ss = 7;
    unsigned char cc = 0;
    unsigned char pp = 0;
    unsigned char bb = 0;
	songstruct * song = (songstruct *) testset.songs[ss];
	blockstruct * block = (blockstruct *) song->blocks[bb];
    patstruct * patt = (patstruct *) block->patterns[pp];
    
    while(playing){
        
        //dummy for playing is printf, so: 
	    printf("SONG %02d; BLOCK %02d; PATTERN %02d; STEP %02d: %03u, %03u, %03u\n",ss,bb,pp,cc,
	                        patt->drumpattern[cc],
	                        patt->basspattern[cc],
	                        patt->leadpattern[cc]);
    
        if(++cc == patt->len){
            cc=0;
            if(++pp == block->blocklen){
                pp=0;
                if(++bb == song->songlen){
                    bb=0;
                    playing = false;
                }else{
                    block = (blockstruct *) song->blocks[bb];
                    patt = (patstruct *) block->patterns[pp];
                }
            }else{
                patt = (patstruct *) block->patterns[pp];
            }
        }          
    }
}




