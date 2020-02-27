#include <Arduino.h>
#include "../../../Arduino/ToF/ToF.h"
#include "../../../Arduino/Motors/Motors.h"
#include "../../../Arduino/Constants/constants.h"

Motion M(/*robe che deve mettere Gabriele*/);   //per maggiori dettagli guardare la dichiarazione nella libreria 
ToF ToF(TOF_ADDRESS);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	double d = ToF.getDistance();
	Serial.println(d);
	if (d < MIN_OBSTACLE_DIST)
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
	}
}