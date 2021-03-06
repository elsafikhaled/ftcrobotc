#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     IROne,          sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     IRTwo,          sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Left2,         tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define TANK_4M;

/* Code Review by Darrell
 - *Good use of library.*
 - First few lines should probably go in an initialization function.
 - While loop is likely unneccessary. You probably want to run the BeaconPosition code only once, not forever.
*/

#include "Joystickdriver.c"
#include "../../library/drive_modes/drive_modes.h"
#include "autonomous/beacon.c"

task main()
{
	RegisterDriveMotors(Left,Left2,Right,Right2);
	waitForStart();
	nMotorEncoder[Right] = 0;
	nMotorEncoder[Left] = 0;

	while(true)
	{
			if(SensorValue[IROne] == 4 && SensorValue[IRTwo] == 6)
			{
				BeaconPos1();
			}
			else if(SensorValue[IROne] == 5 && SensorValue[IRTwo] == 7)
			{
				BeaconPos2();
			}
			else if(SensorValue[IROne] == 6 && SensorValue[IRTwo] == 5)
			{
				BeaconPos3();
			}
	}
}
