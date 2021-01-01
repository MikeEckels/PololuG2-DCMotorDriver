#pragma once

class KalmanFilter {
private:
	float g1;
	int memory;
	int* values;
	int currentAmount = 0;

	int* ShiftArray(int arr[]);

public:
	KalmanFilter();
	KalmanFilter(float g1, int memory);
	int Filter(int value);

};