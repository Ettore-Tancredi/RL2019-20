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
	double radius;

public:
	Motor(const int, const bool, const int, const bool, const int, const int, const int, const double);
	void setParameters(const int, const bool, const int, const bool, const int, const int, const int, const double);
	void stop();
	void move(int);
	void move(int, bool);
};

class Motion
{
private:
	Motor M_sx, M_dx;
	IMU imu(IMU_ADDRESS); 
	int digIN1_status;
	int digIN2_status;
	double radius;
	double k;    //motor's angular speed / wheel's angular speed
public:
	Motion(const int, const int, const int, const int, const int, const int, const int, const int, const int, const int, const bool, const bool, const double, const double);
	void move(int, int);
	void move(int, bool, int, bool);
	void turn(double);
	void move_for(double);
	void stop();
};

#endif