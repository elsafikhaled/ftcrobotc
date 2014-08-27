#pragma config(Sensor, S1,     MSPPS,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "drivers/mindsensors-pressure.h"

task main () {
  long abspressure;
  long gaugepressure;

  // set the sensor to kilo Pascals
  MSPPSsetUnit(MSPPS, MSPPS_UNIT_PSI);

  wait1Msec(100);
  MSPPSsetRefPressure(MSPPS);
  wait1Msec(100);

  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "PPS-v3");
  nxtDisplayCenteredTextLine(3, "Test 1");
  wait1Msec(2000);

  // Read the current pressure and feed that to the ref pressure
  // abspressure = MSPPSreadAbsPressure(MSPPS);
  // MSPPSsetRefPressure(MSPPS, abspressure);

  // you can also do this
  MSPPSsetRefPressure(MSPPS);

  while (true) {
    eraseDisplay();

    abspressure = MSPPSreadAbsPressure(MSPPS);
    gaugepressure = MSPPSreadGaugePressure(MSPPS);

    nxtDisplayTextLine(0,"MSPPS Test 1");

    nxtDisplayTextLine(2, "Pressure (KPA):");
    nxtDisplayTextLine(3, "Abs: %d", abspressure);
    nxtDisplayTextLine(4, "Gauge: %d", gaugepressure);
    wait1Msec(100);
  }
}

/*
 * $Id: mindsensors-pressure-test1.c 108 2012-09-16 09:06:13Z xander $
 */
