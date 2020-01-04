#include <Arduino.h>
#include "IMU/imu.h"
#include "ToF/ToF.h"
#include "Motors/Motors.h"
#include "Constants/constants.h"

ToF ToF(TOF_ADDRESS);
Motion M(/*parametes that I don't want to write*/);

LINE_TYPE type;   //contiene il caso in cui ci troviamo


void setup()
{
	//setup
}

void loop()
{
	//prendere roba in input attraverso seriale (int) e immagazzinarla in type


	if (ToF.getDistance() < MIN_OBSTACLE_DIST)
	{
		M.move(0, 0);   // stop
		M.turn(90);   //check for the sign 
		M.move(STD_SPEED, STD_SPEED);
		delay(OBSTACLE_DELAY);
		M.move(0, 0);   // stop
		M.turn(-90);   //check for the sign 
		M.move(STD_SPEED, STD_SPEED);
		delay(OBSTACLE_DELAY);
		M.move(0, 0);   // stop
		M.turn(-90);   //check for the sign 
		M.move(STD_SPEED, STD_SPEED);
		delay(OBSTACLE_DELAY);
		M.move(0, 0);   // stop
		M.turn(90);   //check for the sign 
	}
	else
	{

		switch (type)
		{
		case INTERRUPT:
			M.move(STD_SPEED, STD_SPEED);
			delay(INTERRUPT_DELAY);
			break;
		case STD_LINE:
			//use Pid
			break;
		case T_INTERSECTION:
			//check for green regions (information via USB)
			break;
		case C_INTERSECTION:
			//check for green regions (information via USB)
			break;
		case UNKNOWN:
			M.move(STD_SPEED, STD_SPEED);
			break;
		default:
			break;
		}
	}
}