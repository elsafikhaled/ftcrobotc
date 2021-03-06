#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irsensor,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorArm,      tmotorNormal, PIDControl)
#pragma config(Servo,  srvo_S1_C3_1,    servoLeft,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servoRight,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "C:\ftc\drivers\2.3\drivers\HTIRS2-driver.h"
#include "JoystickDriver.c"

task main ()
{
    waitForStart(); //wait until FCS tells us to go

    //move forward away from wall
    motor[motorLeft] = 50;
    motor[motorRight] = 50;
    wait1Msec(700);
    motor[motorLeft] = 0;
    motor[motorRight] = 0;

    //lift arm so hand is at height of lowest peg. check time.
    motor[motorArm] = -100;
    wait1Msec(1500);
    motor[motorArm] = 0;

    //create variables to store sensor outputs and set it to AC 1200Hz
    int dirAC = 1;
    int acs1, acs2, acs3, acs4, acs5 = 0;
    int maxSig = 0;
    int val = 0;
    tHTIRS2DSPMode mode = DSP_1200;

    while(dirAC != 0) //End the loop when the sensor can't read a value. Testing shows that this happens when the sensor is below the peg in front of the IR column.
    {
        dirAC = HTIRS2readACDir(irsensor);
        HTIRS2readAllACStrength(irsensor, acs1, acs2, acs3, acs4, acs5);
        maxSig = (acs1 > acs2) ? acs1 : acs2;
        maxSig = (maxSig > acs3) ? maxSig : acs3;
        maxSig = (maxSig > acs4) ? maxSig : acs4;
        maxSig = (maxSig > acs5) ? maxSig : acs5;
        nxtDisplayCenteredBigTextLine(1, "dir=%d", dirAC);
        nxtDisplayCenteredBigTextLine(4, "sig=%d", maxSig);
        val = dirAC - 5;

        if ( val == 0 )
        {
            motor[motorLeft] = 5;
            motor[motorRight] = 5;
        }
        else
        {
            motor[motorLeft] = 10 * val;
            motor[motorRight] = 10 * -val;
        }
        //nxtDisplayCenteredBigTextLine(4, "

        servo[servoRight] = 160;
        servo[servoLeft] = 90;

        wait10Msec(2);
    }
    /*//drive forwards into peg
    motor[motorLeft] = 10;
    motor[motorRight] = 10;
    wait1Msec(200); // check time for proper peg touching
    motor[motorLeft] = 0;
    motor[motorRight] = 0;*/

    //Place ring on rack. Servos are involved. Perhaps adjusting the arm position or the robot position.
    //Open hand?
    servo[servoRight] = 50;
    servo[servoLeft] = 200;
    wait10Msec(20);

    motor[motorArm] = 100;
    wait1Msec(1000);
    motor[motorArm] = 0;
}
