#pragma once
#include "Arduino.h"

class PololuG2 {
private:
	unsigned char pwmPin;
	unsigned char dirPin;
	unsigned char sleepPin;
	unsigned char faultPin;
	unsigned char currentSensePin;

	bool direction;
	unsigned int currentOffset;

	void InitPins();
	void CalibrateCurrent();
	unsigned int GetRawCurrent();

public:
	PololuG2();
	PololuG2(unsigned char pwmPin, unsigned char dirPin, unsigned char sleepPin, unsigned char faultPin, unsigned char currentSensePin);

	void Wake();
	void Sleep();

	bool GetFault();
	bool GetDirection();
	unsigned int GetCurrentA();
	unsigned int GetCurrentMa();
	
	void SetVoltage(char voltage);
	void SetSpeedRpm(char RPM);
};
