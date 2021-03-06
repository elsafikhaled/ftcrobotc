#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S3, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motorSweep,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoFL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoBL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servoTubeSlide,       tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_4,    servo1_3_4,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_5,    servo1_3_5,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo1_3_6,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S2_C3_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S2_C3_3,    servoTubeLift,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_4,    servo2_3_4,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_5,    servo2_3_5,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_6,    servo2_3_6,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_1,    servoSweepArm,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_2,    servoTubeWinch,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_3,    servoLoader,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_4,    servo3_1_4,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_5,    servo3_1_5,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    servo3_1_6,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_1,    servoSweep1,        tServoStandard)
#pragma config(Servo,  srvo_S3_C2_2,    servoSweep2,       tServoStandard)
#pragma config(Servo,  srvo_S3_C2_3,    servoGrabber,         tServoStandard)
#pragma config(Servo,  srvo_S3_C2_4,    servo3_2_4,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_5,    servo3_2_5,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_6,    servo3_2_6,           tServoStandard)

task main()
{

while(true)
{

servo[servoTubeWinch] = 182;

if (nNxtButtonPressed == 2)
{
	servo[servoTubeSlide] = 255;
}

if (nNxtButtonPressed == 1)
{
	servo[servoTubeSlide] = 0;
}

if (nNxtButtonPressed == 3)
{
	servo[servoTubeSlide] = 127;
}

}

}
