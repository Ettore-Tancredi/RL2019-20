#include <Arduino.h>
#include "Stepper.h"

const int MOTOR_STEPS = 200;
const int RPM = 120;
const int MICRO_STEPS = 1;
const double ANGLE = 120;   //l'angolo di cui deve ruotare la pinza per prendere le palline

Stepper::Stepper(int dir, int step) :BasicStepperDriver(MOTOR_STEPS, dir, step)
{
	DIR = dir;
	STEP = step;
	begin(RPM, MICROSTEPS);
}

void Stepper::catch_the_ball()
{
	rotate(ANGLE);
	rotate(-ANGLE);
}

