#ifndef GYRO_DRIVE_C
#define GYRO_DRIVE_C
// Gyro Based Drive Functions

// NOTE: This file relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "../drive_modes/drive_modes.h"
#include "../sensors/gyro.c"

///@todo: write a time protection so that we don't turn longer than some given time

void TurnLeftDegrees(int degrees, int power)
{
	// MAKE SURE THE ROBOT IS STATIONARY WHEN THIS FUNCTION IS CALLED
	startGyro();
	wait1Msec(200);
	resetGyro();
	ClearTimer(T4);
	TurnLeft(power);
	bool failed = false;
	degrees -= LEFT_TURN_GYRO_OVERRUN;
	while(true)
	{
		// Stop if the gyro reading is invalid
		if (!gyroValid()) {
			failed = true;
			break;
		}
		// Turn until we exceed the requested (absolute) angle
		int angle = abs(readGyro());
		if (angle > degrees) {
			break;
		}
	}
	StopAllDriveMotors();
	stopGyro();
}

void TurnRightDegrees(int degrees, int power)
{
	// MAKE SURE THE ROBOT IS STATIONARY WHEN THIS FUNCTION IS CALLED
	startGyro();
	wait1Msec(200);
	resetGyro();
	ClearTimer(T4);
	TurnRight(power);
	bool failed = false;
	degrees -= RIGHT_TURN_GYRO_OVERRUN;
	while(true)
	{
		// Stop if the gyro reading is invalid
		if (!gyroValid()) {
			failed = true;
			break;
		}
		// Turn until we exceed the requested (absolute) angle
		int angle = abs(readGyro());
		if (angle > degrees) {
			break;
		}
	}
	StopAllDriveMotors();
	stopGyro();
}
#endif
