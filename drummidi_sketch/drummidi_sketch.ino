// O2 Minipops rhythm box (c) DSP Synthesizers 2016
// Free for non commercial use
// http://janostman.wordpress.com


//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <avr/pgmspace.h>
//#include "Arduino.h"

#include "O2_data.h"
#include "rng.h"

#define POT0 A0
#define POT1 A1
#define POT2 A2
#define POT3 A3
#define POT4 A4
#define POT5 A5

#define  MINIMUM(LEN,CUTOFF)  ((LEN) < (CUTOFF) ? (LEN) : (CUTOFF))


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

#define VOLCA_MS (4)

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

#define BDMIDI 36
#define SDMIDI 39
#define HHMIDI 42
#define LTMIDI 45

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
  (((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P) - 8 : (P) - 14))

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
  if (RingCount) {                         //If entry in FIFO..
    OCR2A = Ringbuffer[(RingRead++)];      //Output LSB of 16-bit DAC
    RingCount--;
  }
  //-----------------------------------------------------------------
}


uint16_t samplepntGU, samplepntBG2, samplepntBD, samplepntCL, samplepntCW, samplepntCY, samplepntMA, samplepntQU;
uint16_t samplecntGU, samplecntBG2, samplecntBD, samplecntCL, samplecntCW, samplecntCY, samplecntMA, samplecntQU;
uint16_t samplecutoff1 = 8192, samplecutoff2 = 8192;

#ifdef DOMIDI

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Do whatever you want when a note is pressed.

  // Try to keep your callbacks short (no delays ect)
  // otherwise it would slow down the loop() and have a bad impact
  // on real-time performance.
  if (velocity > 5) {
    switch (pitch) {
      //This arrangement uses all the keys on the Korg nanokeys
      //Arranged in blocks around the black and white notes
      case 48: case 50: case 52:
        samplepntGU = 0;
        samplecntGU = MINIMUM(GU_LEN,samplecutoff1);   //GU_LEN;
        break;
      case 49: case 51:
        samplepntBG2 = 0;
        samplecntBG2 = MINIMUM(BG2_LEN,samplecutoff1);   //BG2_LEN;
        break;
      case BDMIDI: case 53: case 55: case 57: case 59:
        samplepntBD = 0;
        samplecntBD = BD_LEN;
        break;
      case SDMIDI: case 54: case 56: case 58:
        samplepntCL = 0;
        samplecntCL = MINIMUM(CL_LEN,samplecutoff1);   //CL_LEN;
        break;
      case HHMIDI: case 60: case 62: case 64:
        samplepntCW = 0;
        samplecntCW = MINIMUM(CW_LEN,samplecutoff2);   //CW_LEN;
        break;
      case LTMIDI:
      case 61:
      case 63:
        samplepntCY = 0;
        samplecntCY = MINIMUM(CY_LEN,samplecutoff2);   //CY_LEN;
        break;
      case 65:
      case 67:
      case 69:
      case 71:
        samplepntMA = 0;
        samplecntMA = MINIMUM(MA_LEN,samplecutoff2);   //MA_LEN;
        break;
      case 66:
      case 68:
      case 70:
        samplepntQU = 0;
        samplecntQU = MINIMUM(QU_LEN,samplecutoff2);   //QU_LEN;
        break;
      default:
        break;
    }
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  //WARNING: this will mess with CLK_OUT
  //digitalWriteFast(LED_BUILTIN,LOW);
}

void handleControlChange(byte channel, byte CC, byte value) {
  switch (CC) {


  }

}


#endif

void setup() {

  OSCCAL = 0xFF;

  //Drum mute inputs
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(RUNSTOP_PIN, INPUT_PULLUP); //My run/stop pin!

  //pinMode(5,INPUT_PULLUP);
  //pinMode(6,INPUT_PULLUP);
  //pinMode(7,INPUT_PULLUP);
  pinMode(CLOCK_PIN, OUTPUT);      //Clock output
  //pinMode(9,INPUT_PULLUP);

  //pinMode(10,INPUT_PULLUP); //RUN - Stop input
  //8-bit PWM DAC pin
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);      //Reset output


  //These were for the AMUX - not needed now!
  //pinMode(14,OUTPUT);       //SEQ cnt output
  //pinMode(15,OUTPUT);
  //pinMode(16,OUTPUT);
  //pinMode(17,OUTPUT);


  pinMode(A0, INPUT_PULLUP); // pot read
  pinMode(A1, INPUT_PULLUP); // tempo pot
  pinMode(A2, INPUT_PULLUP); // pattern select pot
  pinMode(A3, INPUT_PULLUP); // pattern select pot
  pinMode(A4, INPUT_PULLUP); // pattern select pot
  pinMode(A5, INPUT_PULLUP); // pattern select pot
  //WARNING: SETTING PINMODE ON A6 AND A7 CAUSES THIS SKETCH TO FAIL!!
  //pinMode(A6, INPUT); // pattern select pot
  //pinMode(A7, INPUT); // pattern select pot
  pinMode(LED_BUILTIN, OUTPUT); //on board LED for

  // Set up Timer 1 to send a sample every interrupt.
  cli();
  // Set CTC mode
  // Have to set OCR1A *after*, otherwise it gets reset to 0!
  TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
  TCCR1A =  TCCR1A & ~(_BV(WGM11) | _BV(WGM10));
  // No prescaler
  TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
  // Set the compare register (OCR1A).
  // OCR1A is a 16-bit register, so we have to do this with
  // interrupts disabled to be safe.
  //OCR1A = F_CPU / SAMPLE_RATE;
  // Enable interrupt when TCNT1 == OCR1A
  TIMSK1 |= _BV(OCIE1A);
  sei();
  OCR1A = 800;//800; //40KHz Samplefreq

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
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 62hz increments
  OCR0A = 255;// = 61Hz
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
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  MIDI.setHandleNoteOff(handleNoteOff);  // Put only the name of the function
  MIDI.setHandleControlChange(handleControlChange);

  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to messages on channel 1

  //Serial.begin(115200); // This works with ttymid
  Serial.begin(31250);//This is the Midi standard - use for sending via RX
#endif

}




#ifdef DOSERIAL
void print_binary(int v, int num_places)
{
  int mask = 0, n;

  for (n = 1; n <= num_places; n++)
  {
    mask = (mask << 1) | 0x0001;
  }
  v = v & mask;  // truncate v to specified number of places

  while (num_places)
  {

    if (v & (0x0001 << num_places - 1))
    {
      Serial.print("1");
    }
    else
    {
      Serial.print("0");
    }

    --num_places;
    if (((num_places % 4) == 0) && (num_places != 0))
    {
      Serial.print("_");
    }
  }
}
#endif



void process_pitched_voice_masked(uint16_t *samplecnt, uint8_t pitch, uint8_t *phacc, const unsigned char *SAMPLE, uint16_t *spnt, uint8_t bitmask, int16_t *total) {

  if (*samplecnt) {
    *phacc += pitch;
    if (*phacc & 128) {
      *phacc &= 127;

      uint8_t s = (pgm_read_byte_near(SAMPLE + (*spnt)++));
      int8_t s2 = s - 128;
      (*total) += s2;
      (*samplecnt)--;
    }
  }
}





void loop() {

  //uint16_t samplecntBG2,samplecntCL,samplecntCW,samplecntCY,samplecntMA,samplecntQU;

  uint16_t pitch;

  samplecntBD = 0;
  samplecntBG2 = 0;
  samplecntCL = 0;
  samplecntCW = 0;
  samplecntCY = 0;
  samplecntGU = 0;
  samplecntMA = 0;
  samplecntQU = 0;

  //uint16_t samplepntBG2,samplepntCL,samplepntCW,samplepntCY,samplepntMA,samplepntQU;

  int16_t total;

  uint8_t stepcnt = 0;
  uint16_t tempo = 3500; //, pot_tempo=tempo;
  uint16_t tempocnt = 1;
  //uint8_t MUX=4;
  uint8_t playing = 1;

  uint8_t patselect = 0;
  uint8_t patlength = pgm_read_byte_near(patlen + patselect);

  uint8_t bitshift1 = 0,
          bitshift2 = 0;

  uint8_t bitmask1 = 0xff,
          bitmask2 = 0xff;

  //Pitch control:
  uint8_t divider, samplepitch1 = 129, samplepitch2 = 129;
  uint8_t phaccGU, phaccBG2, phaccBD, phaccCY,
          phaccCL, phaccCW , phaccMA, phaccQU;
  uint8_t MUX = 0;
  uint8_t pp;

  uint8_t togglestartstop = 1; //change to zero if you don't want beat to start on boot

  uint8_t clockdiv = 4; //number of
  uint16_t gatediv = 16;

  unsigned long now, then;
  uint8_t ledonoff = 0;

  uint8_t sw2 = 0, sw3 = 0;
  uint8_t beatCount = 0;
  uint8_t rand_thresh;

  while (1) {

    //----------------------------------------------------------------------
    //------ Add current sample word to ringbuffer FIFO --------------------

    if (RingCount < 255) { //if space in ringbuffer
      //total = 0;
      int16_t total1 = 0,
              total2 = 0;

      // BANK 1
      process_pitched_voice_masked(&samplecntGU, samplepitch1, &phaccGU, GU, &samplepntGU, bitmask1, &total1);
      process_pitched_voice_masked(&samplecntBG2, samplepitch1, &phaccBG2, BG2, &samplepntBG2, bitmask1, &total1);
      process_pitched_voice_masked(&samplecntBD, samplepitch1, &phaccBD, BD, &samplepntBD, bitmask1, &total1);
      process_pitched_voice_masked(&samplecntCL, samplepitch1, &phaccCL, CL, &samplepntCL, bitmask1, &total1);

      total1 = total1 > 0 ? total1 & bitmask1 : -((-total1) & bitmask1);
      total = total1;

      //BANK 2
      process_pitched_voice_masked(&samplecntCW, samplepitch2, &phaccCW, CW, &samplepntCW, bitmask2, &total2);
      process_pitched_voice_masked(&samplecntMA, samplepitch2, &phaccMA, MA, &samplepntMA, bitmask2, &total2);
      process_pitched_voice_masked(&samplecntCY, samplepitch2, &phaccCY, CY, &samplepntCY, bitmask2, &total2);
      process_pitched_voice_masked(&samplecntQU, samplepitch2, &phaccQU, QU, &samplepntQU, bitmask2, &total2);
      
      total2 = total2 > 0 ? total2 & bitmask2 : -((-total2) & bitmask2);
      total += total2;

      if (total < -127) total = -127;
      if (total > 127) total = 127;
      cli();
      Ringbuffer[RingWrite] = total + 128;
      RingWrite++;
      RingCount++;
      sei();


      //------------------------------------------------------------------------
      //--------- sequencer block ----------------------------------------------
      if (playing) {
        if (!(tempocnt--)) {
          tempocnt = tempo;

          if ((beatCount & 0x02) == 0)
            digitalWriteFast(CLOCK_PIN, HIGH); //Clock out Hi
          else
            digitalWriteFast(CLOCK_PIN, LOW); //Clock out Lo
          beatCount++;

          uint8_t trig = pgm_read_byte_near(pattern + (patselect << 4) + stepcnt++);
          PORTC = stepcnt; //Not sure what this does!
 
          // Uncomment if you want to mask drums...
          //uint8_t mask=(PIND>>2)|((PINB&3)<<6);
          //trig&=mask;

          if (stepcnt > patlength) stepcnt = 0;
          if (stepcnt == 0) digitalWriteFast(12, HIGH); //Reset out Hi
          if (stepcnt != 0) digitalWriteFast(12, LOW); //Reset out Lo

          if (trig & 128) {
            if(rand_thresh > rng_next()){
              samplepntGU = 0;
              samplecntGU = MINIMUM(GU_LEN,samplecutoff1);   //GU_LEN < samplecutoff1 ? GU_LEN : samplecutoff1;
            }
          }
          if (trig & 64) {
            if(rand_thresh > rng_next()){
              samplepntBG2 = 0;
              samplecntBG2 = MINIMUM(BG2_LEN,samplecutoff1);   //BG2_LEN < samplecutoff1 ? BG2_LEN : samplecutoff1;
            }
          }
          if (trig & 32 & rand_thresh) {
            if(rand_thresh > rng_next()){
              samplepntBD = 0;
              samplecntBD = BD_LEN; //  < samplecutoff ? BD_LEN : samplecutoff;
            }
          }
          if (trig & 16 & rand_thresh) {
            if(rand_thresh > rng_next()){
              samplepntCL = 0;
              samplecntCL = MINIMUM(CL_LEN,samplecutoff1);   //CL_LEN < samplecutoff1 ? CL_LEN : samplecutoff1;
            }
          }
          if (trig & 8 & rand_thresh) {
            samplepntCW = 0;
            samplecntCW = MINIMUM(CW_LEN,samplecutoff2);   //CW_LEN < samplecutoff2 ? CW_LEN : samplecutoff2;
          }
          if (trig & 4 & rand_thresh) {
            samplepntMA = 0;
            samplecntMA = MINIMUM(MA_LEN,samplecutoff2);   //MA_LEN < samplecutoff2 ? MA_LEN : samplecutoff2;
          }
          if (trig & 2 & rand_thresh) {
            samplepntCY = 0;
            samplecntCY = MINIMUM(CY_LEN,samplecutoff2);   //CY_LEN < samplecutoff2 ? CY_LEN : samplecutoff2;
          }
          if (trig & 1 & rand_thresh) {
            samplepntQU = 0;
            samplecntQU = MINIMUM(QU_LEN,samplecutoff2);  //QU_LEN < samplecutoff2 ? QU_LEN : samplecutoff2;
          }
        }
      }
    }

    //------------------------------------------------------------------------
    // Control pots & switches block -----------------------------------------
    if (!(divider++)) {
#ifdef DOMIDI
      MIDI.read();
#endif

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
            samplecutoff1 = ((ADCL + (ADCH << 8)) << 3);
            break;
          case 1:
            samplepitch1 = sw2 ? ((ADCL + (ADCH << 8)) >> 3) + 1 : 128;
            break;
          case 2:
            //bitshift1 = sw3 ? (ADCL + (ADCH << 8)) >> 7 : 0; //TODO: interesting effects if bitshift and samplecutoff are on the same mux!
            //bitmask1 = 0xff << (bitshift1 == 7 ? 6 : bitshift1);
            rand_thresh = sw3 ? (((ADCL + (ADCH << 8)) << 3)>>2) : B11111111;////(((ADCL + (ADCH << 8)) << 3)>>2) < rng_next() ? 1 : 0;
            break;
          case 3:
            samplecutoff2 = ((ADCL + (ADCH << 8)) << 3);
            break;
          case 4:
            samplepitch2 = sw2 ? ((ADCL + (ADCH << 8)) >> 3) + 1 : 128;
            break;
          case 5:
            bitshift2 = sw3 ? (ADCL + (ADCH << 8)) >> 7 : 0; //TODO: interesting effects if bitshift and samplecutoff are on the same mux!
            bitmask2 = 0xff << (bitshift2 == 7 ? 6 : bitshift2);
            break;
          case 6:
            patselect = (ADCL + (ADCH << 8)) >> 6;
            patlength = pgm_read_byte_near(patlen + patselect);
            break;
          case 7:
            tempo = 100 + ((ADCL + (ADCH << 8)) << 2);
            break;
        }

        MUX++;
        if (MUX == MAXMUX) MUX = 0;
        ADMUX = 64 | MUX; //Select MUX
        sbi(ADCSRA, ADSC); //start next conversation1
      }

      //Try run and stop in here - within the divider to keep things quick - no obvious latency...
      if (playing = digitalReadFast(RUNSTOP_PIN)) {
      }
      else {
        //playing = 0;//change to zero if you want to turn beat on or off
        stepcnt = 0;
        beatCount = 0;
        digitalWriteFast(CLOCK_PIN, LOW); //Clock out Lo
      }

      //TODO: if this works, put it in the MUX block to explicity disable reading from DAC - quicker that way and it means control can be opened up to MIDI!
      //Trying to use the other two switches to turn off the effects...
      //NB this seems to turn on/off some of the voices - need to check out why!
      sw2 = digitalReadFast(SW2_PIN);
      sw3 = digitalReadFast(SW3_PIN);

#ifdef DOSERIAL
      //------------------------------------------------------------------------
      // Serial keyboard control block
      if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
          case ('j'): /* next pattern */
            ++patselect;
            patselect &= 15;   /* only 16 patterns */
            patlength = pgm_read_byte_near(patlen + patselect);
            Serial.print("p "); Serial.println(patselect);
            Serial.print("p<<4 "); Serial.println(patselect << 4);
            break;
          case ('k'): /* previous pattern */
            --patselect;
            patselect &= 15;   /* only 16 patterns */
            patlength = pgm_read_byte_near(patlen + patselect);
            Serial.print("p "); Serial.println(patselect);
            Serial.print("p<<4 "); Serial.println(patselect << 4);
            break;
          case (' '):
            //if (playing){
            //	playing=0;
            //} else {
            //	playing=1;
            //}
            playing != playing;
            break;
          case ('f'):
            if (tempo > 100) {
              tempo -= 100;
            }
            Serial.println(tempo);
            //Serial.println(pot_tempo);
            break;
          case ('d'):
            tempo += 100;
            Serial.println(tempo);
            //Serial.println(pot_tempo);
            break;
          //case('u'):
          //        if(pitch>100){
          //          pitch -= 100;
          //       }
          //        break;
          //case('i'):
          //        pitch += 100;
          //        break;
          case ('p'):
            Serial.println("---------------");
            Serial.println("Current Pattern");
            Serial.print("Tempo: "); Serial.println(tempo);
            Serial.print("Pot 0 val is "); Serial.println(samplepitch1);
            Serial.print("Pot 4 val is "); Serial.println(samplepitch2);
            Serial.print("Pattern is "); Serial.println(patselect);
            Serial.print("Patlen is "); Serial.println(patlength);
            for (pp = 0; pp < 16; pp++) {
              print_binary(pgm_read_byte_near(pattern + (patselect << 4) + pp), 8);
              Serial.println();
            }
            Serial.println("---------------");
            Serial.println("---------------");
            break;
          default:
            break;
        }

      }
#endif
    }
  }
}
