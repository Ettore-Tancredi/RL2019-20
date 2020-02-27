#include "Motors.h"
#include <Arduino.h>
#include "../IMU/imu.h"
#include "../Constants/constants.h"



Motor::Motor(const int D1 = 0,
	const bool status1 = false,
	const int D2 = 0,
	const bool status2 = false,
	const int PWM_PIN = 0,
	const int direction = 0,
	const int enable = 0,
	const double r = 2.5) :   //radius [cm]
	DigIN1(D1),
	DigIN2(D2),
	SetValueSpeedInput(PWM_PIN),
	Direction(direction),
	Enable(enable),
	radius(r)
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
	const int enable = 0,
	const double r = 2.5)
{
	DigIN1 = D1;
	DigIN2 = D2;
	SetValueSpeedInput = PWM_PIN;
	Direction = direction;
	Enable = enable;
	radius = r;


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

void Motor::stop()
{
	digitalWrite(Enable, LOW);
}

void Motor::move(int speed)   //if speed = 0 motor angular velocity would be tha minimum one
{
	if (speed >= 0)
		digitalWrite(Direction, FORWARD);
	else 
		digitalWrite(Direction, BACKWARD);

	digitalWrite(Enable, HIGH);

	analogWrite(SetValueSpeedInput, speed);
}

void Motor::move(int speed, bool sign)   //sign = true for positive sign
{
	if (sign)
		digitalWrite(Direction, FORWARD);
	else
		digitalWrite(Direction, BACKWARD);

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
	const bool status2,
	const double r,
	const double k)
{
	K = k;
	radius = r;
	
	if (status1)
		digIN1_status = 1;
	else
		digIN1_status = 0;

	if (status2)
		digIN1_status = 1;
	else
		digIN1_status = 0;


	M_sx.setParameters(D1_sx, status1, D2_sx, status2, PWM_PIN_sx, direction_sx, enable_sx, r);
	M_dx.setParameters(D1_dx, status1, D2_dx, status2, PWM_PIN_dx, direction_dx, enable_dx, r);
}

void Motion::stop()
{
	M_sx.stop();
	M_dx.stop();
}


void Motion::move(int speed_sx, int speed_dx)
{
	M_sx.move(speed_sx);
	M_dx.move(speed_dx);
}

void Motion::move(int speed_sx, bool sign_sx, int speed_dx, bool sign_dx)
{
	M_sx.move(speed_sx, sign_sx);
	M_dx.move(speed_dx, sign_dx);
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

	stop();  //stop the motors to have a more precise maneuver
}

const double pi = 3.14159;

void Motion::move_for(double dist)   //  [cm]
{
	stop();  //for better precision

	double std_linear_speed = (table[digIN1_status][digIN2_status].v_min + ((table[digIN1_status][digIN2_status].v_max - table[digIN1_status][digIN2_status].v_min) * double(STD_SPEED) / 255.0)) * 2 * pi * K * radius * 60;  //  [cm / sec]
	int delta_t = dist * 1000 / std_linear_speed;  // [milliseconds]

	move(STD_SPEED, STD_SPEED);   //minimum speed
	delay(delta_t);

	stop();
}