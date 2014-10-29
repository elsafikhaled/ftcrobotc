#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*   HiTechnic Experimenter's Kit for the SuperPro

Experiment - 1 Introduction
Read the status of a switch and display the status on an LED

*/

#include "drivers/hitechnic-superpro.h"

task main() {
  int inputdata;

  // Set B0 for output
  HTSPBsetupIO(HTSPB, 0x1);

  while(true) {
    // Read a 10bit wide analogue value from A0
    inputdata = HTSPBreadADC(HTSPB, 0, 10);
    nxtDisplayTextLine(1, "A0: %d", inputdata);

    // If A0 is less than 50% of the max value
    // turn off the LED, otherwise switch it on
    if(inputdata < 512)
      HTSPBwriteIO(HTSPB, 0x00);
    else
      HTSPBwriteIO(HTSPB, 0x01);

    wait1Msec(50);
  }
}
