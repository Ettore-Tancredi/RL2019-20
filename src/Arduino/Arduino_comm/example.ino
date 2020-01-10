#include "Arduino_comm.h"
#include "Arduino.h"

const int THRESHOLD = 50;

void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int n = read_int();
    if(n > THRESHOLD)
    {
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
    }
}