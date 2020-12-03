#include "PololuG2.h"

PololuG2::PololuG2() {
	this->pwmPin = 9;
	this->dirPin = 8;
	this->sleepPin = 7;
	this->faultPin = 6;
	this->currentSensePin = A0;
}

PololuG2::PololuG2(unsigned char pwmPin, unsigned char dirPin, unsigned char sleepPin, unsigned char faultPin, unsigned char currentSensePin) {
	this->pwmPin = pwmPin;
	this->dirPin = dirPin;
	this->sleepPin = sleepPin;
	this->faultPin = faultPin;
	this->currentSensePin = currentSensePin;
}

void PololuG2::Begin() {
	pinMode(this->pwmPin, OUTPUT);
	pinMode(this->dirPin, OUTPUT);
	pinMode(this->sleepPin, OUTPUT);
	pinMode(this->faultPin, INPUT_PULLUP);
	pinMode(this->currentSensePin, INPUT);
	analogWriteFrequency(this->pwmPin, 32000);//Teensy4.0 32Khz PWM
	//TCCR1B = TCCR1B & B11111000 | B00000001; //Uno 31.6Khz PWM
	CalibrateCurrent();
}

void PololuG2::Wake() {
	digitalWrite(this->sleepPin, HIGH);
}

void PololuG2::Sleep() {
	digitalWrite(this->sleepPin, LOW);
}

bool PololuG2::GetFault() {
	return !digitalRead(this->faultPin);
}

bool PololuG2::GetDirection() {
	return this->direction;
}

float PololuG2::GetCurrentA() {
	return ((float)((float)GetCurrentMa() / 1000.0f));
}

float PololuG2::GetCurrentMa() {
	unsigned int currentMa = (GetRawCurrent() - this->currentOffset);
	//5V/ADC resolution/G2 resolution
	return ((float)(((float)currentMa * (5000000.0f/1024.0f))/20.0f));
}

unsigned int PololuG2::GetRawCurrent() {
	return currentKF.Filter(analogRead(this->currentSensePin));
}

void PololuG2::SetDirection(bool dir) {
	this->direction = dir;
	digitalWrite(this->dirPin, this->direction);
}

void PololuG2::SetVoltage(short voltage) {
	this->direction = (voltage >= 0) ? 1 : 0;
	voltage = constrain(voltage, -this->MaxInputVoltage, this->MaxInputVoltage);
	voltage = (voltage < 0) ? -voltage : voltage;
	
	voltage = map(voltage, 0, this->MaxInputVoltage, 0, 255);
	
	digitalWrite(this->dirPin, this->direction);
	analogWrite(this->pwmPin, voltage);
}

void PololuG2::SetSpeedRpm(int RPM) {
	//Least squares best fit
	RPM = constrain(RPM, 0, this->MaxInputRPM);
	char voltage = ceil((double)0.008555 * (double)RPM + (double)0.224365);
	if (RPM <= 0) {
		voltage = 0;
	}
	SetVoltage(voltage);
}

void PololuG2::SetBrake() {
	//Current reading is not accurate while braking
	digitalWrite(this->pwmPin, 0);
}

void PololuG2::CalibrateCurrent() {
	SetVoltage(0);
	Wake();
	delay(1);
	this->currentOffset = GetRawCurrent();
}