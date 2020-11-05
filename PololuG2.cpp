#include "PololuG2.h"

PololuG2::PololuG2() {
	this->pwmPin = 9;
	this->dirPin = 8;
	this->sleepPin = 7;
	this->faultPin = 6;
	this->currentSensePin = A0;
	InitPins();
}

PololuG2::PololuG2(unsigned char pwmPin, unsigned char dirPin, unsigned char sleepPin, unsigned char faultPin, unsigned char currentSensePin) {
	this->pwmPin = pwmPin;
	this->dirPin = dirPin;
	this->sleepPin = sleepPin;
	this->faultPin = faultPin;
	this->currentSensePin = currentSensePin;
	InitPins();
}

void PololuG2::InitPins() {
	pinMode(this->pwmPin, OUTPUT);
	pinMode(this->dirPin, OUTPUT);
	pinMode(this->sleepPin, OUTPUT);
	pinMode(this->faultPin, OUTPUT);
	pinMode(this->currentSensePin, INPUT);
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

unsigned int PololuG2::GetCurrentA() {
	//1000 milliamps per Amp
	return ((unsigned int)(GetCurrentMa() / 1000));
}

unsigned int PololuG2::GetCurrentMa() {
	unsigned int currentMa = (GetRawCurrent() - this->currentOffset);
	//5V/ADC resolution/G2 resolution
	return ((unsigned int)(currentMa * 5000000/1024/20));
}

unsigned int PololuG2::GetRawCurrent() {
	return analogRead(this->currentSensePin);
}

void PololuG2::SetVoltage(char voltage) {
	//Need to rewrite to change direction if negative or positive
	voltage = (voltage >= 42) ? 42 : voltage;
	voltage = (voltage <= -42) ? -42 : voltage;
	voltage = map(voltage, -42, 42, 0, 1024);

	analogWrite(this->pwmPin, voltage);
}

void PololuG2::SetSpeedRpm(char RPM) {
	//Calculate based off of voltage relationship
}

void PololuG2::CalibrateCurrent() {
	SetVoltage(0);
	Wake();
	delay(1);
	this->currentOffset = GetRawCurrent();
}