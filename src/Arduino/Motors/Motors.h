#ifndef MOTORS_H
#define MOTORS_H

#include "../IMU/imu.h"
#include "../Constants/constants.h"


class Motor
{
private:
	const unsigned int FORWARD = 0x0;  //Arduino's LOW
	const unsigned int BACKWARD = 0x1;  //Arduino's HIGH
	int DigIN1;   //digital pin 
	int DigIN2;   //digital pin  
	int SetValueSpeedInput;   //pin on which we aplly the PWM to determine the speed ( range between the minimum and the maximum speed )
	int Direction;   //simply gives the direction of motion (forward - LOW;  backward - HIGH)
	int Enable; //(set on LOW to stop the motor)

public:
	Motor(const int, const bool, const int, const bool, const int, const int, const int);
	void setParameters(const int, const bool, const int, const bool, const int, const int, const int);
	void move(int);
};

class Motion
{
private:
	Motor M_sx, M_dx;
	IMU imu(IMU_ADDRESS); 
public:
	Motion(const int, const int, const int, const int, const int, const int, const int, const int, const int, const int, const bool, const bool);
	void move(int, int);
	void turn(double);
};

#endif