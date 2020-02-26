#include "ToF/ToF.h"

ToF ToF();

void setup()
{
	//setup
}

void loop()
{
	Serial.println(ToF.getDistance());
}