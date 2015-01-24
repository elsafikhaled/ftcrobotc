#pragma config(Sensor, S1,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-compass-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * hitechnic-compass.h provides an API for the HiTechnic Compass Sensor.  This program
 * demonstrates how to use that API in combination with a SMUX.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 29 November 2009
 * version 0.1
 */

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-compass.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor HTCOMPASS = msensor_S1_1;

task main () {
  int _target = 0;

  eraseDisplay();
  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Compass");
  nxtDisplayCenteredTextLine(3, "SMUX Test");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and sensor to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);
  eraseDisplay();

  time1[T1] = 0;
  while(true) {
    // Reset the target no more than once a second
    // This also helps with debouncing the [enter] button.
    if (time1[T1] > 1000) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Changing");
      nxtDisplayTextLine(2, "target");
      wait1Msec(500);
      // Set the current heading as the value for the offset to be used as the
      // new zero-point for the relative heading returned by
      // HTMCreadRelativeHeading()
      _target = HTMCsetTarget(HTCOMPASS);
      PlaySound(soundBlip);
      while(bSoundActive) EndTimeSlice();
      time1[T1] = 0;
    }

    // Get the true heading and relative heading from the sensor and
    // display them on the screen.
    while(nNxtButtonPressed != kEnterButton) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Reading");
      nxtDisplayTextLine(2, "Target: %4d", _target);
      nxtDisplayTextLine(4, "Abs:   %4d", HTMCreadHeading(HTCOMPASS));
      nxtDisplayTextLine(5, "Rel:   %4d", HTMCreadRelativeHeading(HTCOMPASS));
      nxtDisplayTextLine(6, "Press enter");
      nxtDisplayTextLine(7, "to set target");
      wait1Msec(100);
    }
  }
}

/*
 * $Id: hitechnic-compass-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */
