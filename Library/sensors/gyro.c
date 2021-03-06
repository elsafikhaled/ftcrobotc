#ifndef FTC_GYRO
#define FTC_GYRO

#include "../../drivers/hitechnic-gyro.h"

int LEFT_TURN_GYRO_OVERRUN = 5;
int RIGHT_TURN_GYRO_OVERRUN = 5;

const int GYRO_PERIOD = 10;
const int GYRO_CAL_SAMPLES = 25;

tSensors GYRO_SENSOR;
void RegisterGyroSensor(tSensors gyroSensorName)
{
	GYRO_SENSOR = gyroSensorName;
}

bool GYRO_READY = false;
float GYRO_ANGLE = 0.0;

// Return the raw speed reading from the gyro
float readGyroSpeed()
{
	return HTGYROreadRot(GYRO_SENSOR);
}

task gyro() {
	GYRO_READY = false;
	GYRO_ANGLE = 0.0;

	// Calibrate -- assume we are stationary
	float cal = 0.0;
	HTGYROsetCal(GYRO_SENSOR, 0);
	for (int i = 0; i < GYRO_CAL_SAMPLES; i++) {
		cal += HTGYROreadRot(GYRO_SENSOR);
		wait1Msec(5);
	}
	HTGYROsetCal(GYRO_SENSOR, cal / (float)GYRO_CAL_SAMPLES);

	// Loop indefinately
	time1[T4] = 0;
	while (true) {

		// Wait in small slices, giving up the CPU
		while (time1[T4] < GYRO_PERIOD) {
			abortTimeslice();
		}

		// Immediately reset the timer in case we get de-scheduled
		time1[T4] = 0;

		// Read and integrate
		GYRO_ANGLE += readGyroSpeed() * ((float)GYRO_PERIOD / 1000.0);
		GYRO_READY = true;
	}
	// only runs when you stop the gyro task
	GYRO_READY = false;
}

// Reset the accumulated angle
void resetGyro() {
	GYRO_ANGLE = 0.0;
}

// Return the accumulated angle
int readGyro() {
	return (int)GYRO_ANGLE;
}

// Return true if the provided gyro reading is sensible
bool gyroValid() {
	if (!GYRO_READY) {
		return false;
	}
	if (abs(readGyroSpeed()) > 200.0) {
		return false;
	}
	return true;
}

void stopGyro() {
	GYRO_READY = false;
	StopTask(gyro);
}

void startGyro() {
	StartTask(gyro);
	while (!GYRO_READY) {
		abortTimeslice();
	}
}

void DisplayGyroAngleOnNXTDisplay()
{
	nxtDisplayTextLine(0, "Angle: %d", readGyro());
}

#endif
