#pragma config(Motor,  motorA,          single,        tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("nxtLCDScreen");
//#pragma debuggerWindows("Servos");
//#pragma debuggerWindows("joystickSimple");

#include "controlWithPID.c"
#include "PID.c"

task main()
{
	StartTask(controller);
	StartTask(PID);

	while(true)
	{
		// don't stop the task
	}
}
