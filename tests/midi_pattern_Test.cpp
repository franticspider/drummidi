#include <stdlib.h>
#include <stdio.h>

#include "catch.hpp"

//use a define to remove this specifier...
#define PROGMEM

//handy sizeof calculator for arrays
#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

#include "../drum_midi/midinotes.h"
#include "../drum_midi/midi_patterns.h"
#include "../drum_midi/midi_test_song.h"

#define SONGCOUNT (16)

TEST_CASE("pattern memory allocation is valid"){
	
    printf("checking patterns are valid\n");


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
    
    printf("CHECKING PATTERNS WORK AS IF PLAYING\n");

    //SET UP SONG
    unsigned char ss = 0;
    unsigned char cc = 0;
    unsigned char pp = 0;
    unsigned char bb = 0;
	songstruct * song = (songstruct *) testset.songs[ss];
	blockstruct * block = (blockstruct *) song->blocks[bb];
    patstruct * patt = (patstruct *) block->patterns[pp];
    
    

    //CHECK(patt->len == NELEMS(patt->drumpattern));
    //CHECK(patt->len == NELEMS(patt->basspattern));
    //CHECK(patt->len == NELEMS(patt->leadpattern));

    
    while(playing){
        
        //dummy for playing is printf, so: 
	    printf("SONG %02d; BLOCK %02d; PATTERN %02d; STEP %02d: %03u, %03u, %03u\n",ss,bb,pp,cc,
	                        patt->drumpattern[cc],
	                        patt->basspattern[cc],
	                        patt->leadpattern[cc]);
    
        if(++cc == patt->len){
            cc=0;
            if(++pp == block->blocklen){
                //We will need a new block! 
                pp=0;
                if(++bb == song->songlen){
                    bb=0;
                    if(++ss == testset.setlen){
                        playing = false;
                        printf("Stopping playing at Song %d, block %d, pattern %d\n",ss,bb,pp);
                    }
                    if(playing){
                        printf("\n==========\nSONG %02d\n",ss);
                        song = (songstruct *) testset.songs[ss];                    
                    }
                }
                if(playing){
                    printf("BLOCK %02d\n",bb);
                    block = (blockstruct *) song->blocks[bb];
                }
            }
            if(playing){
                patt = (patstruct *) block->patterns[pp];
            }
        }          
    }
}


/* Song play protocol: 

turn on - with play off
    can turn knob to choose tune - how will we know which one??
    then turn on play switch - song will play until
        a: pattern finishes
        b: play switch -> off
    could use another switch to de    
*/        
        
        

TEST_CASE("mechanism for playing song works with start/stop"){


    //PLAYING OR NOT:
    bool playing = true;
    bool songfinished = false;
    
    printf("\n\n\n\n\nCHECKING PATTERNS WORK AS IF PLAYING\n");
    printf("Assumes playing is \"ON\" at boot \n");

    //SET UP SONG
    unsigned char songidx = 0;
    unsigned char blockidx = 0;
    unsigned char patidx = 0;
    unsigned char stepidx = 0;
	songstruct * song = (songstruct *) testset.songs[songidx];
	blockstruct * block = (blockstruct *) song->blocks[blockidx];
    patstruct * patt = (patstruct *) block->patterns[patidx];

    unsigned char swct = 0;
    const unsigned char swctlim = 2*testset.setlen;
    
    
    printf("\n==========*\nSONG %02d\n",songidx);
    
    while(swct<swctlim){
        
        //SEQEUNCER SIMULATION
        if(playing){
            //dummy for playing is printf, so: 
	        printf("SONG %02d; BLOCK %02d; PATTERN %02d; STEP %02d: %03u, %03u, %03u\n",songidx,blockidx,patidx,stepidx,
	                            patt->drumpattern[stepidx],
	                            patt->basspattern[stepidx],
	                            patt->leadpattern[stepidx]);
        
            if(++stepidx == patt->len){
                stepidx=0;
                if(++patidx == block->blocklen){
                    //We will need a new block! 
                    patidx=0;
                    if(++blockidx == song->songlen){
                        blockidx=0;
                        if(++songidx == testset.setlen){
                            playing = false;//Needed for this test - not in code!
                   
                            printf("FINISHED SET!\nStopping playing at Song");
                            printf("%d, block %d, pattern %d\n",songidx,blockidx,patidx);
                            return;
                        }
                        if(playing){
                            printf("\n==========\nSONG %02d\n",songidx);
                            song = (songstruct *) testset.songs[songidx];                    
                        }
                    }
                    if(playing){
                        printf("BLOCK %02d\n",blockidx);
                        block = (blockstruct *) song->blocks[blockidx];
                    }
                }
                if(playing){
                    patt = (patstruct *) block->patterns[patidx];
                }
            }
        }
        else{
            printf("Not playing!\n");
        }
    
        //SWITCHING SIMULATION          
        //Try run and stop in here - within the divider to keep things quick - no obvious latency...
        if (playing) {
            if(songfinished){
              swct++;
              playing = 0;
            }
        }
        else {

            songfinished = 0;
            stepidx = 0;
            patidx = 0;
            blockidx = 0;

            //song = (songstruct *) testset.songs[songidx];
            //block = (blockstruct *) song->blocks[blockidx];
            //patt = (patstruct *) block->patterns[patidx];
                 
            playing = 1;
        }
    }    
}








