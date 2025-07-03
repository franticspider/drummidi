# User Guide

## PCB notes

The goals in designing the PCB were:

- to have a general-purpose board for audio with the nano
- to be able to use the PCB 'stand alone', but also be compatible with the AE Modular synth system
- two jack sockets out: one for clock and one for audio
- three swithces, the function of which is set up in software
- seven pots, the function of which is set up in software
- all remaining pins on the arduino accessible by solder points
- power either direct via the usb cable; or by the ae modular connector; or by wiring in a 5v power supply or battery pack

## BOM

- 1 arduino nano - this can either be soldered in directly, or via two 15-pin headers
- 2 jack sockets (supplied)
- 3 switches (supplied)
- 8 10k linear potentiometers
- 9 100nf capacitors
- 1 1k ohm resistor

## Drummidi sketch

This is the main sketch for this project at the moment and is based around some of the many versions of Jan Ostman's minipops code that has been floating around the internet for a while now.

Here's what the components do in this sketch:

- **AUD socket** audio out
- **CLK socket** clock out - can drive Korg volcas
- **Switch 1** start/stop
- **Switch 2** variable sample speed on/off
- **Switch 3** bitcrusher on/off
- **Pot 0** sample clip for voices 1-4 - trims the end of samples as they play
- **Pot 1** sample play speed for voices 1-4 (if Switch 2 is "on" (up position))
- **Pot 2** bitcrusher level for voices 1-4 (if Switch 3 is "on" (up position))
- **Pot 3** sample clip for voices 5-8 - trims the end of samples as they play
- **Pot 4** sample play speed for voices 5-8 (if Switch 2 is "on" (up position))
- **Pot 5** bitcrusher level for voices 5-8 (if Switch 3 is "on" (up position))
- **Pot 6** pattern select (1-16). NB: patterns can be edited in software only for this sketch!
- **Pot 7** pattern tempo

