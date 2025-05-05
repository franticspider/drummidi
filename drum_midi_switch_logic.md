

        playing = F  
        songfinished = F  
        latched = F

        while()

          if(playing = playswitch)  
            if(songfinished)
              playing = F
              
          if(songfinished)
            if !latched
              song++ (or 0)
              latched = T

          if(playing)
            ...eventually songfinished = T
            
          MUX (1/8 times)
            playswitch.read()
            if !playswitch
              songfinished = F
              latched = F
  
    
      
# Normal play mode
    
- nothing happens until playswitch reads ON
- Playing goes True - plays tune
- Eventually songfinished goes True
- playing goes F even if switch is ON
- song increments
- latched goes T
*everything stops until playswitch goes F*
- songfinished goes F
- latched goes F
*everything stays stopped until playswitch goes T*
- back to the top of this loop...

# If play is interrupted

- nothing happens until playswitch reads ON
- Playing goes True - plays tune




  
