#include "PololuG2.h"

PololuG2 motorDriver;

void setup()
{
	Serial.begin(9600);

	motorDriver.Begin();
	motorDriver.Sleep();
	//motorDriver.SetSpeedRpm(4000);
	motorDriver.SetVoltage(0);
	motorDriver.Wake();
}

void loop()
{
	Serial.println(motorDriver.GetCurrentA());
}
