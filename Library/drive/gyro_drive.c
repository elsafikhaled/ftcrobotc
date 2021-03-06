#ifndef GYRO_DRIVE_C
#define GYRO_DRIVE_C
// Gyro Based Drive Functions

// NOTE: This file relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "../drive/auto_drive.c"
#include "../sensors/gyro.c"

typedef enum
{
	DriveActionForward,
	DriveActionBackward,
	DriveActionForwardForever,
	DriveActionBackwardForever,
	DriveActionTurnLeft,
	DriveActionTurnRight
} DriveActionEnum;

///@todo: write a time protection so that we don't turn or drive for longer than some given time
// Depending on driveAction, this will turn driveArg degrees or drive forward or backward driveArg inches at
// a power of drivePower
void GyroDrive(DriveActionEnum driveAction, int driveArg, int drivePower)
{
	StopAllDriveMotors();
	wait1Msec(250); //The wait is here to ensure the robot comes to a stop before calibrating the gyro

	ResetEncoderValue();
	startGyro();

	resetGyro();
	bool stopAction = false;

	//Makes robot go in opposite direction to avoid rewriting code
	if(driveAction == DriveActionBackward || driveAction == DriveActionTurnLeft)
	{
		drivePower *= -1;
	}

	// Action loop
	while(true)
	{
		if(stopAction == true)
			break;
		// Stop if the gyro reading is invalid
		if (!gyroValid())
		{
			break;
		}
		switch(driveAction)
		{
			//Driving strait code
			case DriveActionBackward:
			case DriveActionForward:
				//If the distance has been reached, it stops running
				if(EncoderDistance(abs(ReadEncoderValue())) > abs(driveArg)) // hopefully you have configured your encoder!
				{
					stopAction = true;
					break;
				}
				//Adjusts power according to gyro reading
				DriveRightMotors(drivePower+readGyro()*5);
				DriveLeftMotors(drivePower-readGyro()*5);
				break;
			//Turning code
			case DriveActionTurnLeft:
			case DriveActionTurnRight:
				//Turns until requested angle is reached
				TurnRight(drivePower);
				int angle = abs(readGyro());
				if (angle > driveArg)
					stopAction = true;
				break;
		}
	}
	StopAllDriveMotors();
	stopGyro();

}

void TurnLeftDegrees(int degrees, int power)
{
	GyroDrive(DriveActionTurnLeft, degrees-LEFT_TURN_GYRO_OVERRUN, power);
}

void TurnRightDegrees(int degrees, int power)
{
	GyroDrive(DriveActionTurnRight, degrees-RIGHT_TURN_GYRO_OVERRUN, power);
}

void DriveForwardDistanceGyro(int distance, int power)
{
	GyroDrive(DriveActionForward, distance, power);
}

void DriveBackwardDistanceGyro(int distance, int power)
{
	GyroDrive(DriveActionBackward, distance, power);
}










//////////////////// DO WE STILL NEED THIS? /////////////////////////

// May need to calibrate to specific robots
int MOTOR_POWER_SHAVE = 3;

bool wasTurningRight = false;
bool wasTurningLeft = false;
int shavedPower = 0;

void InitSpecialGyroDrive(DriveActionEnum driveAction, int drivePower)
{
	wasTurningRight = false;
	wasTurningLeft = false;
	shavedPower = drivePower;
	if(driveAction == DriveActionBackward)
	{
		drivePower *= -1;
		shavedPower *= -1;
		MOTOR_POWER_SHAVE *= -1;
	}
}

bool SpecialGyroDrive(DriveActionEnum driveAction, int drivePower)
{
	// Stop if the gyro reading is invalid
	if (!gyroValid() || shavedPower == 0)
	{
		return false;
	}
	if(readGyro() > 1) // turning right
	{
		// Reset shavedPower if we just switched turn directions //
		wasTurningLeft = true;
		if(wasTurningRight == true)
		{
			wasTurningRight = false;
			shavedPower = drivePower;
		}
		shavedPower = shavedPower - (MOTOR_POWER_SHAVE);
		DriveLeftMotors(shavedPower);
		DriveRightMotors(drivePower);
	}
	else if(readGyro() < -1) // turning left
	{
		// Reset shavedPower if we just switched turn directions //
		wasTurningRight = true;
		if(wasTurningLeft == true)
		{
			wasTurningLeft = false;
			shavedPower = drivePower;
		}
		shavedPower = shavedPower - (MOTOR_POWER_SHAVE);
		DriveRightMotors(shavedPower);
		DriveLeftMotors(drivePower);
	}
	else
	{
		DriveForward(drivePower);
	}
	return true;
}












#endif
