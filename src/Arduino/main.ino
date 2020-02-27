#include <Arduino.h>
#include "IMU/imu.h"
#include "ToF/ToF.h"
#include "Motors/Motors.h"
#include "Constants/constants.h"
#include "Comm/Arduino_comm.h"

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
		M.stop();   // stop
		M.turn(90);   //check for the sign 
		M.move_for(MAX_OBSTACLE_DIM);
		M.stop();   // stop
		M.turn(-90);   //check for the sign 
		M.move_for(MAX_OBSTACLE_DIM);
		M.stop();   // stop
		M.turn(-90);   //check for the sign 
		M.move_for(MAX_OBSTACLE_DIM);
		M.stop();   // stop
		M.turn(90);   //check for the sign 

		/*
		******experimental******

		M.stop();   // stop
		M.turn(90);   //check for the sign
		M.move_for(MAX_OBSTACLE_DIM);
		M.stop();   // stop
		M.turn(-90);   //check for the sign
		M.move_for(MAX_OBSTACLE_DIM);
		M.stop();   // stop
		M.turn(-30);    //low slope for better insertion on the line
		M.move(STD_SPEED, STD_SPEED);   //robot will see INTERRUPT until he reaches the line

		*/
	}
	else
	{
		type = read_int();

		switch (type)
		{
		case INTERRUPT:
			M.move_for(INTERRUPT_JUMP);   //try just        M.move(STD_SPEED, STD_SPEED)
			break;
		case STD_LINE:
			int left_correction = STD_SPEED + adjustment, right_correction = STD_SPEED - adjustment;
			if(left_correction > 255)
				left_correction = 255;
			else if(left_correction < -255)
				left_correction = -255;
			
			if(right_correction > 255)
				right_correction = 255;
			else if(right_correction < -255)
				right_correction = -255;

			M.move(left_correction, right_correction);
			break;
		case INTERSECTION:
			//check for green regions (information via USB)
			bool greenPos[2];
			greenPos[0] = (read_char() == 'T');
			greenPos[1] = (read_char() == 'T');
			if(greenPos[0] && greenPos[1])
				M.turn(180);
			else if(greenPos[0])
			{
				M.move_for(3);  //move for 3 cm
				M.turn(90);
				M.move_for(3);  //move for 3 cm
				delay(300);
			}
			else if(greenPos[1])
			{
				M.move_for(3);  //move for 3 cm
				M.turn(-90);
				M.move_for(3);  //move for 3 cm
			}
			break;
		case UNKNOWN:
			M.move_for(INTERRUPT_JUMP);
			break;
		default:
			break;
		}
	}
}