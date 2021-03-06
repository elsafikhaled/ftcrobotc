#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Seeker,         sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorC,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ForkLift,      tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//All comments to most of this code is in TeleOpJarrod.c
//Other programs that are needed for the competition: Bert_Middle, Bert_sides, Bert_Spoil, and BERTau
#include "JoystickDriver.c"
int deadZone = 15;
long Peg1 = 2196;//peg 1 encoder value
long Peg2 = 5203;//peg 2 encoder value
long Peg3 = 8584;//peg 3 encoder value
long Zero = 0;
long goPosition;

//variables used for stall code
long timeStalling[] = {0, 0, 0}; //amount of time the motors are stalling
long valueOfLastMove[] = {0, 0, 0}; //the value of the encoders when the motor last moved
long timeStoppedMoving[] = {0, 0, 0}; //the time the motors stopped

int StallCode(int motorSentTo, int wantedPower)
{
	int motorIndex;//index value for the arrays
	switch(motorSentTo)//which motor power is being sent to
	{
	case Left:
		motorIndex = 0;
		break;
	case Right:
		motorIndex = 1;
		break;
	case ForkLift:
		motorIndex = 2;
	default:
		break;
	}
	long Cur = nMotorEncoder[motorSentTo];//current encoder value of motor

	if((wantedPower < -15 || wantedPower > 15)&&(Cur == valueOfLastMove[motorIndex]))
	{
		if(timeStalling[motorIndex] + 150 >= time1[T1])
		{
			if(timeStoppedMoving[motorIndex] == 0)
			{
				timeStoppedMoving[motorIndex] = time1[T1];
			}
			if(timeStoppedMoving[motorIndex] + 10 >= time1[T1])
			{
				return 0;
			}
			else
			{
				valueOfLastMove[motorIndex] = Cur;
				timeStoppedMoving[motorIndex] = 0;
				timeStalling[motorIndex] = time1[T1];
			}
		}
		return wantedPower;
	}
	timeStalling[motorIndex] = time1[T1];
	return wantedPower;
}

task Joystick2()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//D-pad fork-lift control
		if(joystick.joy2_TopHat ==0)
		{
			motor[ForkLift] = StallCode(ForkLift, 75);
			//motor[ForkLift] = 100;
		}
		else if(joystick.joy2_TopHat ==4)
		{
			motor[ForkLift] = StallCode(ForkLift, -75);
			//motor[ForkLift] = -100;
		}
		else
		{
			motor[ForkLift] = StallCode(ForkLift, 0);
			//motor[ForkLift] = 0;
		}
		//going to peg 1
		if(joystick.joy2_Buttons == 2)
		{
			goPosition = (Peg1 - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] < Peg1) // to position
				{
					motor[ForkLift] = 75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] > Peg1) // to position
				{
					motor[ForkLift] = -75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}
		//going to peg 2
		else if(joystick.joy2_Buttons == 1)
		{
			goPosition = (Peg2 - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] < Peg2) // to position
				{
					motor[ForkLift] = 75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] > Peg2) // to position
				{
					motor[ForkLift] = -75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}
		//going to peg 3
		else if(joystick.joy2_Buttons == 4)
		{
			goPosition = (Peg3 - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] < Peg3) // to position
				{
					motor[ForkLift] = 75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] > Peg3) // to position
				{
					motor[ForkLift] = -75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}

		else if(joystick.joy2_Buttons == 3)
		{
			goPosition = (Zero - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] > Zero) // to position
				{
					motor[ForkLift] = -75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] < Zero) // to position
				{
					motor[ForkLift] = 75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}
	}
}


task main()
{
	waitForStart();
	StartTask(Joystick2);
	ClearTimer(T1);
	nMotorEncoder[ForkLift] = 0;
	//slow mode
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(7) == 1)
		{
			if(abs(joystick.joy1_y1) > deadZone)
			{
				motor[Left] = StallCode(Left, (joystick.joy1_y1) / 5);
			}
			else
			{
				motor[Left] = StallCode(Left, 0);
			}

			if(abs(joystick.joy1_y2) > deadZone)
			{
				motor[Right] = StallCode(Right, (joystick.joy1_y2) / 5);
			}
			else
			{
				motor[Right] = StallCode(Right, 0);
			}
		}
		else
		{
			if(abs(joystick.joy1_y1) > deadZone)
			{
				motor[Left] = ((StallCode(Left, (joystick.joy1_y1)) * 115) / 127) - 15;
			}
			else
			{
				motor[Left] = StallCode(Left, 0);
			}

			if(abs(joystick.joy1_y2) > deadZone)
			{
				motor[Right] = ((StallCode(Right, (joystick.joy1_y2)) * 115) / 127) - 15;
			}
			else
			{
				motor[Right] = StallCode(Right, 0);
			}
		}
	}
}
