#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motorSweep,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoFL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoFR,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servoBL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_4,    servoBR,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_5,    servoGrabber,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servoHopper,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C3_1,    servoSweep,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S2_C3_3,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S2_C3_4,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C3_5,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C3_6,    servo4,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "includes/writing.c"
#include "JoystickDriver.c"

task main()
{
	RegisterMotors(
	motorFR,
	motorFL,
	motorBL,
	motorBR,
	motorSweep,
	motorFan1,
	motorFan2
	);
	RegisterServos(
	servoFL,
	servoFR,
	servoBL,
	servoBR,
	servoGrabber,
	servoSweep,
	servoTube
	);
	waitForStart();
	while(true)
	{
		float Kp = 0.008;
		float Ki = 0.015;
		float Kd = 0.002;
		float errorPrevSum[4] = {0, 0, 0, 0};
		float errorPrev[4] = {0, 0, 0, 0};
		float error[4];
		float ang[4] = {0.0, 0.0, 0.0, 0.0};
		float newAng[4] = {0.0, 0.0, 0.0, 0.0};
		float n[4] = {0.0, 0.0, 0.0, 0.0};
		float angPrev[4] = {0.0, 0.0, 0.0, 0.0};
		float newAngPrev[4] = {0.0, 0.0, 0.0, 0.0};
		float servoSpeed[4] = {0.0, 0.0, 0.0, 0.0};

		waitForStart();
		while(true)
		{
			if (abs(joystick.joy1_x1) > 20)
			{
				int powe = joystick.joy1_x1;
				motor[FRONT_LEFT_MOTOR] = powe;
				motor[FRONT_RIGHT_MOTOR] = -1 * powe;
				motor[BACK_LEFT_MOTOR] = powe;
				motor[BACK_RIGHT_MOTOR] = -1 * powe;
			}
			else if ( sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_y2, 2) ) > 20)
			{
				int powe = sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_y2, 2) );
				motor[FRONT_LEFT_MOTOR] = powe;
				motor[FRONT_RIGHT_MOTOR] = -1 * powe;
				motor[BACK_LEFT_MOTOR] = powe;
				motor[BACK_RIGHT_MOTOR] = -1 * powe;
			}
			else
			{
				motor[FRONT_LEFT_MOTOR] = 0;
				motor[FRONT_RIGHT_MOTOR] = 0;
				motor[BACK_LEFT_MOTOR] = 0;
				motor[BACK_RIGHT_MOTOR] = 0;
			}

			angPrev[0] = ang[0];
			angPrev[1] = ang[1];
			angPrev[2] = ang[2];
			angPrev[3] = ang[3];
			newAngPrev[0] = newAng[0];
			newAngPrev[1] = newAng[1];
			newAngPrev[2] = newAng[2];
			newAngPrev[3] = newAng[3];
			if (abs(joystick.joy1_x1) > 20)
			{
				ang[0] = 45;
				ang[1] = 135;
				ang[2] = 225;
				ang[3] = 315;
				for (int p; p < 4; p++)
				{
					if (abs(ang[p]) > 90)
					{
						if (sgn(ang[p] * angPrev[0]) == -1)
						{
							n[p] = n[p] + -1 * sgn(ang[p]);
						}
					}
					newAng[p] = ang[p] + n[p] * 360 - 90;
				}
			}
			else if ( sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_y2, 2) ) > 20)
			{
				ang[0] = 57.5 * atan2(joystick.joy1_y2, joystick.joy1_x2);
				ang[1] = ang[0];
				ang[2] = ang[0];
				ang[3] = ang[0];

				for (int p; p < 4; p++)
				{
					if (abs(ang[p]) > 90)
					{
						if (sgn(ang[p] * angPrev[0]) == -1)
						{
							n[p] = n[p] + -1 * sgn(ang[p]);
						}
					}
					newAng[p] = ang[p] + n[p] * 360 - 90;
				}
			}
			error[0] = newAng[0] - GetCRServoPosition(FRONT_LEFT_MOTOR);
			error[1] = newAng[1] - GetCRServoPosition(FRONT_RIGHT_MOTOR);
			error[2] = newAng[2] - GetCRServoPosition(BACK_LEFT_MOTOR);
			error[3] = newAng[3] - GetCRServoPosition(BACK_RIGHT_MOTOR);
			for (int p; p < 4; p++)
			{
				servoSpeed[p] = ( Kp * error[p] ) + ( Ki * errorPrevSum[p] ) + ( Kd * (error[p] - errorPrev[p]) );
				errorPrev[p] = error[p];
				errorPrevSum[p] = errorPrevSum[p] + errorPrev[p] * 0.005;
			}

			servo[BACK_RIGHT_SERVO] = 127 * ( -1 * servoSpeed[0] + 1);
			servo[BACK_LEFT_SERVO] = 127 * ( -1 * servoSpeed[1] + 1);
			servo[FRONT_RIGHT_SERVO] = 127 * ( -1 * servoSpeed[2] + 1);
			servo[FRONT_LEFT_SERVO] = 127 * ( -1 * servoSpeed[3] + 1);
			wait1Msec(100);
		}
	}
}
