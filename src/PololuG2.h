#pragma once
#include "Arduino.h"
#include "KalmanFilter.h"

class PololuG2 {
private:
	unsigned char pwmPin;
	unsigned char dirPin;
	unsigned char sleepPin;
	unsigned char faultPin;
	unsigned char currentSensePin;

	bool direction;
	unsigned int currentOffset;
	int MaxInputVoltage = 35;
	int MaxInputRPM = 4000;

	void CalibrateCurrent();
	unsigned int GetRawCurrent();
	KalmanFilter currentKF = KalmanFilter(0.01f, 25);

public:
	PololuG2();
	PololuG2(unsigned char pwmPin, unsigned char dirPin, unsigned char sleepPin, unsigned char faultPin, unsigned char currentSensePin);

	void Begin();
	void Wake();
	void Sleep();

	bool GetFault();
	bool GetDirection();
	float GetCurrentA();
	float GetCurrentMa();
	
	void SetBrake();
	void SetDirection(bool dir);
	void SetVoltage(short voltage);
	void SetSpeedRpm(int RPM);
};
