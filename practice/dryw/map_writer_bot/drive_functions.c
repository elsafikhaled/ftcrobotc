#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTOINS

void LeaveBase()
{
	DriveBackwardTime(250, DEFAULT_POWER);
	TurnLeftTime(250, DEFAULT_POWER);
}

void FollowRightWall(int distanceFromWall, int power, int sonarNum)
{
	while(SensorValue(bumper) == 0)
	{
	 	DriveRightMotors(power + (ReadSonar(sonarNum) - distanceFromWall));
	 	DriveLeftMotors(power - (ReadSonar(sonarNum) - distanceFromWall));
	}
}

void DrivePerimeterRight()
{
	while(true)
	{
		FollowRightWall(3, DEFAULT_POWER, 2);
		//If the bumper hits a wall, the function above breaks and we turn, then follow the wall again
		DriveBackwardTime(250, DEFAULT_POWER);
		TurnLeftTime(250, DEFAULT_POWER);
	}
}

#endif
