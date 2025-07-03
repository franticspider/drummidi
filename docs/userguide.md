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
- 8 linear potentiometers
- 9 100nf capacitors
- 1 1k ohm resistor

## Drummidi sketch

This is the main sketch for this project at the moment and is based around some of the many versions of Jan Ostman's minipops code that has been floating around the internet for a while now.

Here's what the 

