#pragma config(Motor,  motorA,          single,        tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("nxtLCDScreen");
//#pragma debuggerWindows("Servos");
//#pragma debuggerWindows("joystickSimple");

#include "../../Library/motors/motors.c"
#include "JoystickDriver.c"
#include "struct_stuff.c"

int retVal = 50;

task main()
{
	retVal = RunMotorForOneSecond(100);
	while(true)
	{
		getJoystickSettings(joystick);
		// coding assignment //
		// 1. write a function in Library/motors/motors.c which takes an integer input and sets the motor to drive at that speed
		// 2. use an if-statement within this while loop to check the left analog joystick y value and pass that to the function written for 1.
		// 3. BONUS - move the joystick running code to its own task and start that task from within task main() - note this is not easy

	}
}
