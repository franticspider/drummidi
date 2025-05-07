//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <avr/pgmspace.h>
//#include "Arduino.h"
#include <SoftwareSerial.h>

#include "O2_data.h"
#include "rng.h"

#define POT0 A0
#define POT1 A1
#define POT2 A2
#define POT3 A3
#define POT4 A4
#define POT5 A5


#define MINIMUM(LEN, CUTOFF) ((LEN) < (CUTOFF) ? (LEN) : (CUTOFF))


/* HARDWARE FAULT!
  Somehow the PCB has CLOCk_PIN going to pin 13.
  Pin 13 is *also* wired to the built-in LED on arduino.

  This might not be a problem, but if it is we'll have to cut
  the track on the PCB and wire another digital pin to CLK_OUT

  It also means that if we try to use LED_BUILTIN for other signalling
  purposes, it will also affect the clock signal at the socket :(
*/
#define CLOCK_PIN (13)
#define RUNSTOP_PIN (4)
#define SW2_PIN (6)
#define SW3_PIN (8)
#define RX2_PIN (7)
#define TX2_PIN (9)
//#define VOLCA_MS (4)


// Uncomment the following if you want serial (needs ~4% prog storage!)
//#define DOSERIAL

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

////////////////////////////MIDI BLOCK/////////////////////
#define DOMIDI
#ifdef DOMIDI

#include <MIDI.h>
#include "midinotes.h"
#include "midi_patterns.h"
#include "song_kids_today.h"
#include "song_tortoise.h"
#include "song_jako_thing.h"
#include "midi_test_song.h"

byte BDtoggle = 0, LTtoggle = 0;


// Created and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

#endif

// Standard Arduino Pins
#define digitalPinToPortReg(P) \
  (((P) >= 0 && (P) <= 7) ? &PORTD : (((P) >= 8 && (P) <= 13) ? &PORTB : &PORTC))
#define digitalPinToDDRReg(P) \
  (((P) >= 0 && (P) <= 7) ? &DDRD : (((P) >= 8 && (P) <= 13) ? &DDRB : &DDRC))
#define digitalPinToPINReg(P) \
  (((P) >= 0 && (P) <= 7) ? &PIND : (((P) >= 8 && (P) <= 13) ? &PINB : &PINC))
#define digitalPinToBit(P) \
  (((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P)-8 : (P)-14))

#define digitalReadFast(P) bitRead(*digitalPinToPINReg(P), digitalPinToBit(P))

#define digitalWriteFast(P, V) bitWrite(*digitalPinToPortReg(P), digitalPinToBit(P), (V))

const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);



//--------- Ringbuf parameters ----------
uint8_t Ringbuffer[256];
uint8_t RingWrite = 0;
uint8_t RingRead = 0;
volatile uint8_t RingCount = 0;
volatile uint16_t SFREQ;
//-----------------------------------------

ISR(TIMER1_COMPA_vect) {
  //-------------------  Ringbuffer handler -------------------------
  if (RingCount) {                     //If entry in FIFO..
    OCR2A = Ringbuffer[(RingRead++)];  //Output LSB of 16-bit DAC
    RingCount--;
  }
  //-----------------------------------------------------------------
}


//uint16_t samplepntGU, samplepntBG2, samplepntBD, samplepntCL, samplepntCW, samplepntCY, samplepntMA, samplepntQU;
//uint16_t samplecntGU, samplecntBG2, samplecntBD, samplecntCL, samplecntCW, samplecntCY, samplecntMA, samplecntQU;
//uint16_t samplecutoff1 = 8192, samplecutoff2 = 8192;


SoftwareSerial drumRxTx(RX2_PIN, TX2_PIN);

//RIPPED FROM LOOP() - 
static const songstruct *song = &song_TAG_JT; //testset.songs[songidx];
uint8_t sw2 = 0, sw3 = 0;

void setup() {

  OSCCAL = 0xFF;

  //Drum mute inputs
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(RUNSTOP_PIN, INPUT_PULLUP);  //My run/stop pin!

  //pinMode(5,INPUT_PULLUP);
  //pinMode(6,INPUT_PULLUP);
  //pinMode(7,INPUT_PULLUP);
  pinMode(CLOCK_PIN, OUTPUT);  //Clock output
  //pinMode(9,INPUT_PULLUP);

  //pinMode(10,INPUT_PULLUP); //RUN - Stop input
  //8-bit PWM DAC pin
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  //Reset output

  pinMode(A0, INPUT_PULLUP);  // pot read
  pinMode(A1, INPUT_PULLUP);  // tempo pot
  pinMode(A2, INPUT_PULLUP);  // pattern select pot
  pinMode(A3, INPUT_PULLUP);  // pattern select pot
  pinMode(A4, INPUT_PULLUP);  // pattern select pot
  pinMode(A5, INPUT_PULLUP);  // pattern select pot
  //WARNING: SETTING PINMODE ON A6 AND A7 CAUSES THIS SKETCH TO FAIL!!
  //pinMode(A6, INPUT); // pattern select pot
  //pinMode(A7, INPUT); // pattern select pot
  pinMode(LED_BUILTIN, OUTPUT);  //on board LED for

  // Set up Timer 1 to send a sample every interrupt.
  cli();
  // Set CTC mode
  // Have to set OCR1A *after*, otherwise it gets reset to 0!
  TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
  TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));
  // No prescaler
  TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
  // Set the compare register (OCR1A).
  // OCR1A is a 16-bit register, so we have to do this with
  // interrupts disabled to be safe.
  //OCR1A = F_CPU / SAMPLE_RATE;
  // Enable interrupt when TCNT1 == OCR1A
  TIMSK1 |= _BV(OCIE1A);
  sei();
  OCR1A = 800;  //800; //40KHz Samplefreq

  // Set up Timer 2 to do pulse width modulation on D11

  // Use internal clock (datasheet p.160)
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));

  // Set fast PWM mode  (p.157)
  TCCR2A |= _BV(WGM21) | _BV(WGM20);
  TCCR2B &= ~_BV(WGM22);

  // Do non-inverting PWM on pin OC2A (p.155)
  // On the Arduino this is pin 11.
  TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
  TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
  // No prescaler (p.158)
  TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

  // Set initial pulse width to the first sample.
  OCR2A = 128;

  //set timer0 interrupt at 61Hz
  TCCR0A = 0;  // set entire TCCR0A register to 0
  TCCR0B = 0;  // same for TCCR0B
  TCNT0 = 0;   //initialize counter value to 0
  // set compare match register for 62hz increments
  OCR0A = 255;  // = 61Hz
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for prescaler 1024
  TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);  //1024 prescaler

  TIMSK0 = 0;


  // set up the ADC
  SFREQ = analogRead(0);
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  // Choose prescaler PS_128.
  ADCSRA |= PS_128;
  ADMUX = 64;
  sbi(ADCSRA, ADSC);

#ifdef DOSERIAL
  Serial.begin(9600);

  Serial.println("Modified Jan Ostman O2 Minipops!");
  Serial.println("[j] for next pattern, [k] for previous");
  Serial.println("[f] to speed up, [d] to slow down.  [space] to pause.");
  Serial.println("[p] to get current pattern info");
#endif

#ifdef DOMIDI


  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  //MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  //MIDI.setHandleNoteOff(handleNoteOff);  // Put only the name of the function
  //MIDI.setHandleControlChange(handleControlChange);

  //MIDI.sendNoteOn(DataByte inNoteNumber, DataByte inVelocity, Channel inChannel)

  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to messages on channel 1

  //Serial.begin(115200); // This works with ttymid
  Serial.begin(31250);  //This is the Midi standard - use for sending via RX

  drumRxTx.begin(31250);

#endif

//IN DESPERATION: USING RESET TO PICK SONG DEPENDING ON SW2 AND SW3...


  sw2 = digitalReadFast(SW2_PIN);
  sw3 = digitalReadFast(SW3_PIN);

  if(!sw3){
    if(!sw2)
      song = &song_TAG_JT;
    else
      song = &song_TAG_IATT;
  }else{
    if(!sw2)
      song = &song_TAG_KT;
    else
      song = &song_not_u_culture;
  }

}


#ifdef DOSERIAL
void print_binary(int v, int num_places) {
  int mask = 0, n;

  for (n = 1; n <= num_places; n++) {
    mask = (mask << 1) | 0x0001;
  }
  v = v & mask;  // truncate v to specified number of places

  while (num_places) {

    if (v & (0x0001 << num_places - 1)) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    --num_places;
    if (((num_places % 4) == 0) && (num_places != 0)) {
      Serial.print("_");
    }
  }
}
#endif


void sendDrum(unsigned char note, unsigned char velocity) {

  // Send "Note On" for Middle C on Channel 10 with full velocity
  drumRxTx.write(0x99);      // Status byte: Note On, channel 10
  drumRxTx.write(note);      // Data byte 1: Middle C (note number 60)
  drumRxTx.write(velocity);  // Data byte 2: Velocity 127
}


void trig_to_midi(const uint8_t trig, const uint8_t bitval, const uint8_t rand_thresh, const uint8_t midival, const uint8_t channel) {
  if (trig & bitval) {
    sendDrum(midival, 127);
  } else {
    //MIDI.sendNoteOff(midival, 0, channel);
  }
}



void loop() {

  uint16_t pitch;

  int16_t total;

  uint8_t stepcnt = 0;
  uint16_t tempo = 3500;  //, pot_tempo=tempo;
  uint16_t halftempo = tempo * 0.5;
  uint16_t tempocnt = 1;
  //uint8_t MUX=4;

  uint8_t playing = 0;
  uint8_t finishnote = 0;
  uint8_t songfinished = 0;
  uint8_t latched = 0;
  uint8_t playswitch = 0;
  uint8_t sw2latched = 0;

  //indexes for song structs:
  uint8_t stepidx = 0;
  uint8_t patidx = 0;
  uint8_t blockidx = 0;
  uint8_t songidx = 0;

  //TODO: we won't need these: 
  uint8_t patselect = 0;
  uint8_t patlength = 15;  //pgm_read_byte_near(patlen + patselect);

  uint8_t bitshift1 = 0,
          bitshift2 = 0;

  uint8_t bitmask1 = 0xff,
          bitmask2 = 0xff;

  //Pitch control:
  uint8_t divider, samplepitch1 = 129, samplepitch2 = 129;
  uint8_t phaccGU, phaccBG2, phaccBD, phaccCY,
    phaccCL, phaccCW, phaccMA, phaccQU;


  uint8_t MUX = 0;
  uint8_t pp;

  uint8_t togglestartstop = 1;  //change to zero if you don't want beat to start on boot

  uint8_t clockdiv = 4;  //number of
  uint16_t gatediv = 16;

  unsigned long now, then;
  uint8_t ledonoff = 0;

  uint8_t beatCount = 0;
  uint8_t rand_thresh;

  uint8_t notechan;

  uint8_t lasttrig;
  uint8_t trig;

  //set up the song structure pointers:
  //MADE GLOBAL: 
  //static const songstruct *song = &song_TAG_JT; //testset.songs[songidx];
  static const blockstruct *block = song->blocks[blockidx];
  static const patstruct *patt = block->patterns[patidx];

  tempo = song->tempo;

  while (1) {

    if (RingCount < 255) {

      //Emulate the ring buffer in drum_player to keep timing consistent (see ISR above too! )
      cli();
      RingCount++;
      sei();

      //------------------------------------------------------------------------
      //--------- control block ------------------------------------------------

      //Reset stuff here based on whether playing or not
      if (playing = playswitch) {
        if(songfinished){
          playing = 0;
        }
      }else{
        //if(sw2)
          //songidx++;
      }
      
      if(songfinished){
        stepcnt = 0;
        beatCount = 0;

        //todo(sjh): put this in a function! 
        if (!latched) {
          songidx++;
          if (songidx >= testset.setlen) {
            songidx = 0;
          }
          latched = 1;

          //song =  testset.songs[songidx];
          //songs = (/*kanst*/ songstruct*[]){&song_TAG_JT, &song_TAG_IATT,  &song_TAG_KT, &song_not_u_culture,   &testsong1}
          /*
          switch(songidx){
            case 0: 
              song = &song_TAG_JT;
              break;
            case 1:
              song = &song_TAG_IATT;
               break;
            case 2:  
              song = &song_TAG_KT;
              break;
            case 3: 
              song = &song_not_u_culture;
              break;
            case 4:   
              song = &testsong1;
              break;
            default:
              songidx=0;
              song = &testsong4;
              break;
          }
          */

      
          stepidx = 0;
          patidx = 0;
          blockidx = 0;

          block = song->blocks[blockidx];
          patt =  block->patterns[patidx];

          tempo = song->tempo;
        }

        digitalWriteFast(CLOCK_PIN, LOW);  //Clock out Lo
      } 

      //------------------------------------------------------------------------
      //--------- sequencer block ----------------------------------------------
      if (playing | finishnote) {
        if (!(tempocnt--)) {
          tempocnt = tempo;

          if ((beatCount & 0x02) == 0)
            digitalWriteFast(CLOCK_PIN, HIGH);  //Clock out Hi
          else
            digitalWriteFast(CLOCK_PIN, LOW);  //Clock out Lo
          beatCount++;

#ifdef USE_PROGMEM
          trig = pgm_read_byte_near(patt->drumpattern[stepidx]);
#else
          trig = patt->drumpattern[stepidx];
#endif
          PORTC = stepcnt;  //Not sure what this does!

          // Uncomment if you want to mask drums...
          //uint8_t mask=(PIND>>2)|((PINB&3)<<6);
          //trig&=mask;

          if (stepcnt > patlength) stepcnt = 0;
          if (stepcnt == 0) {
            digitalWriteFast(12, HIGH);  //Reset out Hi
          } else {
            digitalWriteFast(12, LOW);  //Reset out Lo
          }

          trig_to_midi(trig, 128, rand_thresh, GUMIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 64, rand_thresh, BG2MIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 32, rand_thresh, BDMIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 16, rand_thresh, SDMIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 8, rand_thresh, HHMIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 4, rand_thresh, LTMIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 2, rand_thresh, MAMIDI, MIDIDRUMCHANNEL);
          trig_to_midi(trig, 1, rand_thresh, QUMIDI, MIDIDRUMCHANNEL);

          //todo(sjh): make sure stepcnt is in sync with the above
#ifdef USE_PROGMEM
          trig = pgm_read_byte_near(patt->leadpattern[stepidx]);
#else
          trig = patt->leadpattern[stepidx];
#endif
          if (trig > 10)
            MIDI.sendNoteOn(trig, 127, 1);
#ifdef USE_PROGMEM
          trig = pgm_read_byte_near(patt->basspattern[stepidx]);
#else
          trig = patt->basspattern[stepidx];
#endif
          if (trig > 10)
            MIDI.sendNoteOn(trig, 127, 2);


          //update the pattern:
          if (++stepidx == patt->len) {
            stepidx = 0;
            if (++patidx == block->blocklen) {
              patidx = 0;
              if (++blockidx == song->songlen) {
                blockidx = 0;
                songfinished = true;
              }
              block = song->blocks[blockidx];
            }
            patt = block->patterns[patidx];
          }

          // tell the sequencer we have notes to finish!
          finishnote = 1;
        }

        if (tempocnt == halftempo) {
          //MIDI.sendNoteOn(trig, 0, 1);
          //OR all notes offL
          MIDI.sendControlChange(123, 0, 1);
          MIDI.sendControlChange(123, 0, 2);
          //MIDI.sendNoteOff(trig, 127, 1);
          //MIDI.sendNoteOff(trig, 127, 2);
          finishnote = 0;
        }
      }

    }
  


    //------------------------------------------------------------------------
    // Control pots & switches block -----------------------------------------
    if (!(divider++)) {

#define MAXMUX (8)

      if (!(ADCSRA & 64)) {

        //cbi(ADCSRA, ADSC); //start next conversation
        //uint16_t pitch=((ADCL+(ADCH<<8))>>3)+1;
        /* knob / switch layout:

              s1  s2  s3
            k0  k1  k2
              k3  k4  k5
            k6  k7
          */

        switch (MUX) {
          case 0:
            //samplecutoff1 = ((ADCL + (ADCH << 8)) << 3);
            break;
          case 1:
            //samplepitch1 = sw2 ? ((ADCL + (ADCH << 8)) >> 3) + 1 : 128;
            break;
          case 2:
            //bitshift1 = sw3 ? (ADCL + (ADCH << 8)) >> 7 : 0; //TODO: interesting effects if bitshift and samplecutoff are on the same mux!
            //bitmask1 = 0xff << (bitshift1 == 7 ? 6 : bitshift1);
            rand_thresh = B11111111;//sw3 ? (((ADCL + (ADCH << 8)) << 3) >> 2) : B11111111;  ////(((ADCL + (ADCH << 8)) << 3)>>2) < rng_next() ? 1 : 0;
            break;
          case 3:
            //samplecutoff2 = ((ADCL + (ADCH << 8)) << 3);
            break;
          case 4:
            //samplepitch2 = sw2 ? ((ADCL + (ADCH << 8)) >> 3) + 1 : 128;
            break;
          case 5:
            //bitshift2 = sw3 ? (ADCL + (ADCH << 8)) >> 7 : 0; //TODO: interesting effects if bitshift and samplecutoff are on the same mux!
            //bitmask2 = 0xff << (bitshift2 == 7 ? 6 : bitshift2);
            break;
          case 6:
            //songidx = 7; //TODO (sjh): tidy up the patselect variables...
            patselect = 15;  //(ADCL + (ADCH << 8)) >> 6;
            //patlength = pgm_read_byte_near(patlen + patselect);
            break;
          case 7:
            //tempo = 100 + 3500;//((ADCL + (ADCH << 8)) << 2);

            //This times when "NOTE OFF" is sent:
            //halftempo = 100 + ((ADCL + (ADCH << 8)) << 2);
            break;
        }

        MUX++;
        if (MUX == MAXMUX) MUX = 0;
        ADMUX = 64 | MUX;   //Select MUX
        sbi(ADCSRA, ADSC);  //start next conversation1
      }


      //TODO: if this works, put it in the MUX block to explicity disable reading from DAC - quicker that way and it means control can be opened up to MIDI!
      //Trying to use the other two switches to turn off the effects...
      //NB this seems to turn on/off some of the voices - need to check out why!
      sw2 = digitalReadFast(SW2_PIN);
      sw3 = digitalReadFast(SW3_PIN);

      if(!(playswitch = digitalReadFast(RUNSTOP_PIN))){
        
        songfinished = 0;
        latched = 0;
        /*
        //if(sw2){
        //  if(!sw2latched){
            songidx++;
            if (songidx == testset.setlen) {
              songidx = 0;
            }
            //sw2latched = 1;
        
            stepidx = 0;
            patidx = 0;
            blockidx = 0;

            song = (songstruct *)testset.songs[songidx];
            block = (blockstruct *)song->blocks[blockidx];
            patt = (patstruct *)block->patterns[patidx];

            tempo = song->tempo;
          
          }
          */
        //}else{
        //  sw2latched = 0;
        //}
      }


    }
  }
}
