#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     SMUX,           sensorI2CCustom9V)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     mtrBR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     mtrFR,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     mtrLifterL,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_2,     mtrLifterR,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    container,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define PARALLEL_PAIRS

#include "include_files/teleop_includes.c"

const tMUXSensor touchSensor = msensor_S3_1;
const tMUXSensor irSensor = msensor_S3_2;

task main()
{
	InitializeTeleop();
	waitForStart();

	StartTask(DriveTank);
	while(true)
	{
		getJoystickSettings(joystick);

		//Goal grabber commands
		if(joy1Btn(8) == 1)
		{
			GrabGoal();
		}
		if(joy1Btn(7) == 1)
		{
			ReleaseGoal();
		}

		//Collector commands
		if(joy2Btn(8) == 1)
		{
			CollectBalls();
		}
		else if(joy2Btn(7) == 1)
		{
			ReleaseBalls();
		}
		else
		{
			StopCollector();
		}

		//Container commands
		if(joystick.joy2_TopHat == 0)
		{
			HoldBalls();
		}
		else if(joystick.joy2_TopHat == 4)
		{
			DumpBalls();
		}

		//Lift Commands

		//This is for using the lift without encoders
		if(joystick.joy2_y2 > ANALOG_DEAD_ZONE)
		{
			RaiseLift();
		}
		else if(joystick.joy2_y2 < -1*ANALOG_DEAD_ZONE)
		{
			LowerLift();
		}
		else
		{
			StopLift();
		}

		//This is for using the lift with the encoder/.  bjvu gu v
		if(joy2Btn(1) == 1)
		{
			MoveLifter(DownPos);
		}
		else if(joy2Btn(2) == 1)
		{
			MoveLifter(LowGoalPos);
		}
		else if(joy2Btn(3) == 1)
		{
			MoveLifter(MediumGoalPos);
		}
		else if(joy2Btn(4) == 1)
		{
			MoveLifter(HighGoalPos);
		}
		else if(joy2Btn(10) == 1)
		{
			MoveLifter(CenterGoalPos);
		}
	}
}
