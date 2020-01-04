#include "Motors.h"
#include "Arduino.h"
#include "../IMU/imu.h"
#include "../Constants/constants.h"



Motor::Motor(const int D1 = 0,
	const bool status1 = false,
	const int D2 = 0,
	const bool status2 = false,
	const int PWM_PIN = 0,
	const int direction = 0,
	const int enable = 0) :
	DigIN1(D1),
	DigIN2(D2),
	SetValueSpeedInput(PWM_PIN),
	Direction(direction),
	Enable(enable)
{
	digitalWrite(enable, LOW);  //motor initially at rest
	if (status1)
		digitalWrite(DigIN1, HIGH);
	else
		digitalWrite(DigIN1, LOW);

	if (status2)
		digitalWrite(DigIN2, HIGH);
	else
		digitalWrite(DigIN2, LOW);
}

void Motor::setParameters(const int D1 = 0,
	const bool status1 = false,
	const int D2 = 0,
	const bool status2 = false,
	const int PWM_PIN = 0,
	const int direction = 0,
	const int enable = 0)
{
	DigIN1 = D1;
	DigIN2 = D2;
	SetValueSpeedInput = PWM_PIN;
	Direction = direction;
	Enable = enable;
	digitalWrite(enable, LOW);  //motor initially at rest
	if (status1)
		digitalWrite(DigIN1, HIGH);
	else
		digitalWrite(DigIN1, LOW);

	if (status2)
		digitalWrite(DigIN2, HIGH);
	else
		digitalWrite(DigIN2, LOW);
}


void Motor::move(int speed)
{
	if (speed >= 0)
		digitalWrite(Direction, FORWARD);
	else
		digitalWrite(Direction, BACKWARD);


	if (speed == 0)
		digitalWrite(Enable, LOW); //the motor only stops with speed = 0 (choose a very low minimum speed)
	else
		digitalWrite(Enable, HIGH);


	analogWrite(SetValueSpeedInput, speed);
}

Motion::Motion(const int D1_sx,
	const int D2_sx,
	const int PWM_PIN_sx,
	const int direction_sx,
	const int enable_sx,
	const int D1_dx,
	const int D2_dx,
	const int PWM_PIN_dx,
	const int direction_dx,
	const int enable_dx,
	const bool status1,
	const bool status2)
{
	M_sx.setParameters(D1_sx, status1, D2_sx, status2, PWM_PIN_sx, direction_sx, enable_sx);
	M_dx.setParameters(D1_dx, status1, D2_dx, status2, PWM_PIN_dx, direction_dx, enable_dx);
}


void Motion::move(int speed_sx, int speed_dx)
{
	M_sx.move(speed_sx);
	M_dx.move(speed_dx);
}
			   
double abs(double x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

double signOf(double x)
{
	if (x == 0)
		return 1;
	return x / abs(x);
}

void Motion::turn(double angle)   //we use mathematical convention (counterclockwise --> positive)
{
	imu.setAngle();

	for(double alpha = imu.getRotationOnX(); alpha < agle - 2 || alpha > angle + 2; alpha = imu.getRotationOnX())
	{
		move(-STD_SPEED * signOf(angle - alpha), STD_SPEED * signOf(angle - alpha));
	}

	move(0, 0);  //stop the motors to have a more precise maneuver
	
}