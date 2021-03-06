#ifndef FTC8923_FUNCTIONS
#define FTC8923_FUNCTIONS

#include "../../Library/motors/servos.c"
#include "../../Library/motors/motors.c"

const int GRAB_GOAL_POS = 170;
const int RELEASE_GOAL_POS = 100;

//Goal grabber functions
void SetGoalGrabberPosition(int pos)
{
	SetServoPosition(goalGrabber, pos);
}
void GrabGoal()
{
	SetGoalGrabberPosition(GRAB_GOAL_POS);
}
void ReleaseGoal()
{
	SetGoalGrabberPosition(RELEASE_GOAL_POS);
}

//Collector functions
const int RUN_COLLECTOR_FORWARD = -100;
const int RUN_COLLECTOR_BACKWARD = 100;
const int STOP_COLLECTOR = 0;

void RunCollector(int power)
{
	SetMotorPower(collector, power, false); // controller input is a button so we don't attenuate
}
void CollectBalls()
{
	RunCollector(RUN_COLLECTOR_FORWARD);
}
void ReleaseBalls()
{
	RunCollector(RUN_COLLECTOR_BACKWARD);
}
void StopCollector()
{
	RunCollector(STOP_COLLECTOR);
}

//Container functoins
const int HOLD_BALLS = 185;
const int DUMP_BALLS = 125;

void SetContainerPos(int pos)
{
	SetServoPosition(container, pos);
}
void HoldBalls()
{
	SetContainerPos(HOLD_BALLS);
}
void DumpBalls()
{
	SetContainerPos(DUMP_BALLS);
}

//Lift functions

/* DAR Says:
 * For Enums, it is helpful to have the enum name in each enum
 * because it helps you recognize they are enums. Like this:
 * LiftPositionsEnum for enum type.
 * LiftPositionLowGoal
 * LiftPositionMidGoal
 * LiftPositionHighGoal
 * Yes the names are long but they also document your code so no comments are necessary.
 *
 * You have them declared in an enum but you are passing them into an int. It would be
 * better to declare these as const ints:
 * const int LIFT_POSITION_LOW_GOAL = 3800;
 * const int LIFT_POSITION_MID_GOAL = 8700;
 * const int LIFT_POSITION_HIGH_GOAL = 13500;
 */

//Positions of lift
typedef enum
{
	LowGoalPos = 3800,
	MediumGoalPos = 8700,
	HighGoalPos = 13500,
}
LiftPositionsEnum;

// DAR Says: The hook colon is unnecessary. This is equivalent to saying
// return (true ? true : false);
// May as well just do return (TSreadState(touchSensor));
bool LiftIsDown()
{
	return (TSreadState(touchSensor) ? true : false);
}

int LiftHeight()
{
	return abs(nMotorEncoder[mtrLifterL]);
}

void ResetLiftHeight()
{
	nMotorEncoder[mtrLifterL] = 0;
}

void SetLiftPower(int power)
{
	SetMotorPower(mtrLifterL, power, false); // controller input is a button so we don't attenuate
	SetMotorPower(mtrLifterR, power, false); // controller input is a button so we don't attenuate
}

void StopLift()
{
	SetLiftPower(0);
}
void LowerLift()
{
	if(!LiftIsDown())
	{
		SetLiftPower(-100);
	}
	else
	{
		StopLift();
	}
}
void RaiseLift()
{
	SetLiftPower(100);
}

bool LiftAboveDetect(int pos)
{
	if(LiftHeight() > pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LiftBelowDetect(int pos)
{
	if(LiftHeight() < pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MoveLifter(int pos)
{
	while(LiftAboveDetect(pos))
	{
		LowerLift();
	}
	while(LiftBelowDetect(pos))
	{
		RaiseLift();
	}
	StopLift();
}

void ZeroLift()
{
	while(!LiftIsDown())
	{
		LowerLift();
	}
	StopLift();
	wait1Msec(500);
	ResetLiftHeight();

	//Robot crashes if this line isn't here
	StopLift();
}
#endif
