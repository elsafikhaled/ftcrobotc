#ifndef SWERVE_4M_C
#define SWERVE_4M_C

///////////// CODE REVIEW BY DRYW ///////////////////
// File name is too simialr to simpleswerve_4m.c and simple_swerve_4m.c
// Some functions below need comments to describe what they do
// File doesn't comile

#include "../controllers/controller_defines.h"
#include "../motors/motors.c"
#include "../../ftc6220/includes/writing.c"



//MotorEnum datatype used to refer to each of the four drive modules
typedef enumWord
{
	FRONT_RIGHT,
	FRONT_LEFT,
	BACK_LEFT,
	BACK_RIGHT,
}
MotorEnum;

//swerve module structure for storing all values specific to any given drive assembly
typedef struct
{
	float offsetAngle;        //in radians

	float servoPosition;     	//in degrees (0 - 360)
	float motorPower;         //in motor power units (0 - 100)

}
DriveAssemblyState;

DriveAssemblyState Drive[4];


//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following function MUST be called, else the drive will not work. !!! //
//-------------------------------------------------------------------------------------------------//

//initializes the drive assembly by setting all the values in the drive assembly structures
void initializeDriveAssemblies()
{
	//  FRONT_RIGHT Swerve Drive Module   //
	Drive[FRONT_RIGHT].offsetAngle     = PI / 4.0;

	//  FRONT_LEFT Swerve Drive Module   //
	Drive[FRONT_LEFT].offsetAngle      = 3.0 * PI / 4.0;

	//  BACK_RIGHT Swerve Drive Module   //
	Drive[BACK_LEFT].offsetAngle       = 5.0 * PI / 4.0;

	//  BACK_RIGHT Swerve Drive Module   //
	Drive[BACK_RIGHT].offsetAngle      = 7.0 * PI / 4.0;

}
//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//

//Attenuate the joystick used for rotation based on the maximum angular speed possible
//and find the "desired" angular velocity.
float JoystickToRadsPerSec(float joystickZ)
{
	float maxRadsPerSecond = (MAX_MOTOR_SPEED_CMPS * MOTOR_GEAR_RATIO) / CENTER_RADIUS;
	//maximum rotational speed possible.

	float attenuationSlope =  maxRadsPerSecond / joystickRange;
	//mapping maximum rotational speed to the allowed joystick input range, aka. finding the slope.

	float attenuationIntercept = -1 * ANALOG_DEAD_ZONE * sgn(joystickZ) * attenuationSlope;
	//finding the range taken up by the dead zone, aka. finding the intercept.

	if (abs(joystickZ) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return attenuationSlope * joystickZ + attenuationIntercept;
	}

}

//Attenuate the joystick inputs being used for planar motion based on the maximum linear speed possible in any
//direction at this instant.
//Which is in turn scaled off of the current angular speed. This means that the angular velocity limits the
//linear velocity.
float JoystickToCMPerSec(float joystickXorY, float joystickZ)
{
	float fastestMotorRotationRate = JoystickToRadsPerSec(joystickZ) * CENTER_RADIUS;
	//find the largest component of motor velocity used to rotate the robot (limiting factor)

	float maximumLinearSpeed = sqrt( pow(MAX_MOTOR_SPEED_CMPS, 2) - pow(fastestMotorRotationRate, 2) );
	//calculate the maximum linear speed "left over" from the current rotational motion.

	float attenuationSlope = maximumLinearSpeed / joystickRange;
	//map the maximum linear speed to the joystick range, aka. finding the slope.

	float attenuationIntercept = -1 * sgn(joystickXorY) * attenuationSlope * ANALOG_DEAD_ZONE;
	//finding the range taken by the dead zone, aka. finding the intercept.

	float linearVelocityInXorY = attenuationSlope * joystickXorY + attenuationIntercept;
	//slope-intercept for of attenuation.

	if (abs(joystickXorY) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return linearVelocityInXorY;
	}
	//return linearVelocityInXorY; // this is the "desired" linear velocity along whichever axis this was applied to.
}

//calculate the direction a drive assembly should be pointed in:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s.
//velocityY is the vertical (Front-to-back) component in m/s.
//velocityZ is the angular (Round and round) component in rad/s.
//This reference frame is relative to the robot in all instances, meaning the angular argument
//drives it kind of like a car.
float CalculateDriveAngle(float velocityX, float velocityY, float velocityZ, MotorEnum driveIdentifier)
{
	//used the arctangent function to find the angular component of the velocity vector for the chosen motor
	float driveXComponent = velocityX + (velocityZ * CENTER_RADIUS * cos(Drive[driveIdentifier].offsetAngle));
	float driveYComponent = velocityY - (velocityZ * CENTER_RADIUS * sin(Drive[driveIdentifier].offsetAngle));
	int tangent = 57.3 * atan2(driveXComponent, driveYComponent); //drive angle
	if (tangent < 0)
	{
		return tangent + 360;
	}
	else
	{
		return tangent;
	}

}

//Calculate the speed that a drive assembly should be traveling at:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s
//velocityY is the vertical (Front-to-back) component in m/s
//velocityZ is the angular (Round and round) component in rad/s
//This reference frame is relative to the robot in all instances, meaning the angular argument
//drives it kind of like a car.
float CalculateDriveSpeed(float velocityX,float velocityY,float velocityZ, MotorEnum driveIdentifier)
{
	float driveXComponent = velocityX + (velocityZ * CENTER_RADIUS * cos(57.3 * Drive[driveIdentifier].offsetAngle) / 6.28);
	float driveYComponent = velocityY - (velocityZ * CENTER_RADIUS * sin(57.3 * Drive[driveIdentifier].offsetAngle) / 6.28);
	float driveSpeed = sqrt(pow(driveXComponent, 2) + pow(driveYComponent, 2)); //drive speed
	return driveSpeed;
}

//Convert from SI units to MotorPower and Servo Position units, then set the motorPower and servoPosition
//arguments of the motor in question accordingly.

void WriteToServosInd()
{
	DegToCRServo(FRONT_RIGHT_SERVO, FRONT_RIGHT_MOTOR, Drive[FRONT_RIGHT].servoPosition);
	DegToCRServo(FRONT_LEFT_SERVO,  FRONT_LEFT_MOTOR,  Drive[FRONT_LEFT].servoPosition);
	DegToCRServo(BACK_RIGHT_SERVO,  BACK_RIGHT_MOTOR,  Drive[BACK_RIGHT].servoPosition);
	DegToCRServo(BACK_LEFT_SERVO,   BACK_LEFT_MOTOR,   Drive[BACK_LEFT].servoPosition);
}

void WriteToMotorsInd()
{
	CMPSToMotor(BACK_LEFT_MOTOR,   Drive[BACK_LEFT].motorPower);
	CMPSToMotor(BACK_RIGHT_MOTOR,  Drive[BACK_RIGHT].motorPower);
	CMPSToMotor(FRONT_LEFT_MOTOR,  Drive[FRONT_LEFT].motorPower);
	CMPSToMotor(FRONT_RIGHT_MOTOR, Drive[FRONT_RIGHT].motorPower);
}

void RadialDrive(int speed, float radius)
{
	if (radius < 25){
		radius = 25;
	}
	else if (radius > 150)
	{
		radius = 150;
	}
	int forwardRightAngle = atan2(15.875,  radius - 15.875);
	int forwardLeftAngle =  atan2(-15.875, radius - 15.875);
	int rearRightAngle =    atan2(15.875,  radius + 15.875);
	int rearLeftAngle =     atan2(-15.875, radius + 15.875);

	Drive[BACK_RIGHT].servoPosition =  forwardRightAngle + 90;
	Drive[BACK_LEFT].servoPosition =   forwardLeftAngle  + 90;
	Drive[FRONT_RIGHT].servoPosition = rearRightAngle    + 90;
	Drive[FRONT_RIGHT].servoPosition = rearLeftAngle     + 90;

	Drive[FRONT_LEFT].motorPower = speed;
	Drive[FRONT_RIGHT].motorPower = speed;

	Drive[BACK_LEFT].motorPower = speed * (2 * PI * (radius - 15.875)) / (2 * PI * (radius + 15.875));
	Drive[BACK_RIGHT].motorPower = speed * (2 * PI * (radius - 15.875)) / (2 * PI * (radius + 15.875));

}

#endif
