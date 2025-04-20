#include <stdlib.h>
#include <stdio.h>

#include "catch.hpp"

//use a define to remove this specifier...
#define PROGMEM

#include "../drum_midi/midi_patterns.h"
#include "../drum_midi/midi_test_song.h"


TEST_CASE("pattern memory allocation is valid"){
/*
	make_setlist();
	
	
	for(unsigned char ss = 0; ss< SONGCOUNT; ss++){
	
	    printf("SONG %02d:\n",ss);
	    songstruct song = setlist[ss];
	    
	    for(unsigned char bb = 0; bb< song.BLOCKCOUNT; bb++){
	    
	        blockstruct block = song.block[bb];
	        printf("  BLOCK %02d:\n",bb);
	    
	        for(unsigned char pp = 0; pp< block.PATTERNCOUNT; pp++){
	        
	            blockstruct block = song.block[bb];
	            printf("    PATTERN %02d:\n",pp);
	        
	        
	        }	    
	    }
	}
*/	
}
