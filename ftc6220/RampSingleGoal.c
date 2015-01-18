#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servoGrabber,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    servoTube1,           tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servoTube2,           tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* Code Review by Darrell
 - File does not compile.
 - *Great comments explainging code.*
 - *Good use of include files to reduce complexity.*
 - File name does not meet style guide rules -> ramp_single_goal.c
*/

/// !!! SETUP INSTRUCTIONS !!! ///
// Place robot facing away from ramp slope, 1/2 inch from rear edge, centered between ledge and field fence

#include "includes/auto_swive.c"
#include "Includes/manipulators.c"
#include "Includes/writing.c"
#include "JoystickDriver.c"


task main()
{
	RegisterMotors(
	motorFR,
	motorFL,
	motorBL,
	motorBR
	);

	RegisterServos(
	servoFR,
	servoFL,
	servoBL,
	servoBR,
	servoGrabber
	);
	EnableGoalGrabber(false);
	waitForStart();
	SimpleDriveDirection(BACKWARD, 60, 94 * INCH_TO_CM);  // Move off of the ramp and to the goal

	EnableGoalGrabber(true);   // Grab goal

	SimpleDriveDirection(FORWARD - 42.5, 60, 108 * INCH_TO_CM); // Move toparking zone

	RotateTo(-90);   // Move goal intp zone

}
