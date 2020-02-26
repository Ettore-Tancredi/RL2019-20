#include "IMU/imu.h"

IMU imu(0x28)

void setup()
{
	//setup
}

void loop()
{
	Serial.println(imu.getRotationOnX());
}