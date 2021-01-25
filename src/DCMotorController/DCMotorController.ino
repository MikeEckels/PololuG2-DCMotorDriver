#include "PololuG2.h"

PololuG2 motorDriver;

void setup()
{
	Serial.begin(9600);

	motorDriver.Begin();
	motorDriver.Sleep();
	//motorDriver.SetSpeedRpm(100);
	//motorDriver.SetDirection(1); //Can only be called after SetSpeedRpm() or SetVoltage()
	motorDriver.SetVoltage(0);
	motorDriver.Wake();
}

void loop()
{
	while (Serial.available() > 0) {
		int speedType = Serial.parseInt();
		int speed = Serial.parseInt();
		int dir = Serial.parseInt();

		if (speedType) {
			Serial.print("Setting RPM: ");
      Serial.println(speed);
			motorDriver.Sleep();
			motorDriver.SetSpeedRpm(speed);
			motorDriver.SetDirection((bool)dir);
			motorDriver.Wake();
		}
		else {
			Serial.print("Setting Voltage: ");
      Serial.println(speed);
			motorDriver.SetVoltage((short)speed);
		}
	}
}
