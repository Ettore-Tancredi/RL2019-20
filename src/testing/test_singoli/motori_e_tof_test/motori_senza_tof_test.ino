#include <Arduino.h>
#include "../../../Arduino/ToF/ToF.h"
#include "../../../Arduino/Motors/Motors.h"
#include "../../../Arduino/Constants/constants.h"

Motion M(/*robe che deve mettere Gabriele*/);   //per maggiori dettagli guardare la dichiarazione nella libreria 

void setup()
{
  /***********************/
}

void loop()
{
	M.move(STD_SPEED, STD_SPEED);
	M.stop();
	M.turn(90);
}