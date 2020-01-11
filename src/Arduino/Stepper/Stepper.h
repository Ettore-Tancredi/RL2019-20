#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include "BasicStepperDriver.h"

extern const int MOTOR_STEPS;
extern const int RPM;
extern const int MICRO_STEPS;
extern const double ANGLE;

class Stepper:BasicStepperDriver {

private:
	int DIR;
	int STEP;
public:
	Stepper(int, int);
	void catch_the_ball();
};

#endif
