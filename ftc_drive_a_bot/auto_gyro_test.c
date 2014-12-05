#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     mot1,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mot2,          tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("nxtLCDScreen");
//#pragma debuggerWindows("Servos");
#pragma debuggerWindows("joystickGame");

#define TANK_2M

#include "JoystickDriver.c"
#include "../library/drive_modes/drive_modes.h"
#include "../library/sensors/gyro.c"
#include "../library/drive/gyro_drive.c"
#include "../library/controllers/tank_controller.c"

const int TURN_TEST_POWER = 30;

task main()
{
	ASSUME_CONTROLLER_INPUT = false;

	// Gyro Calibration for Drive-a-bot 3 //
	LEFT_TURN_GYRO_OVERRUN = 15;
	RIGHT_TURN_GYRO_OVERRUN = 10;

	RegisterDriveMotors(mot1, mot2);
	RegisterGyroSensor(gyroSensor);

	StartTask(DriveTank);

	while(true)
	{
		if(joy1Btn(1)==1)
		{
			StopTask(DriveTank);
			TurnLeftDegrees(90,TURN_TEST_POWER);
			StartTask(DriveTank);
		}
		if(joy1Btn(2)==1)
		{
			StopTask(DriveTank);
			TurnRightDegrees(90,TURN_TEST_POWER);
			StartTask(DriveTank);
		}
		if(joy1Btn(3)==1)
		{
			StopTask(DriveTank);
			TurnLeftDegrees(90,TURN_TEST_POWER);
			wait1Msec(1000);
			TurnRightDegrees(180,TURN_TEST_POWER);
			wait1Msec(1000);
			TurnLeftDegrees(180,TURN_TEST_POWER);
			wait1Msec(1000);
			TurnRightDegrees(90,TURN_TEST_POWER);
			wait1Msec(1000);
			StartTask(DriveTank);
		}
		if(joy1Btn(4)==1) // drive straight using gyro as long as button is held down
		{
			StopTask(DriveTank);
			// Button Down //
			StopAllDriveMotors();
			wait1Msec(250); //The wait is here to ensure the robot comes to a stop before calibrating the gyro
			ResetEncoderValue();
			startGyro();
			wait1Msec(200);
			// @todo use gyroValid() functionality somehow
			resetGyro();
			ClearTimer(T4);
			while(joy1Btn(4)==1)
			{
				int drivePower = 50;
				InitSpecialGyroDrive(DriveActionForwardForever, drivePower);
				if(!SpecialGyroDrive(DriveActionForwardForever, drivePower))
					break;
				wait1Msec(200); // so we don't attempt to adjust power 60 times a second thus reducing one motor power to zero
			}
			// Button Up //
			StopAllDriveMotors();
			stopGyro();
			StartTask(DriveTank);
		}
	}

}
