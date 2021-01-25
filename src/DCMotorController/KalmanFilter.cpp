#include "KalmanFilter.h"

KalmanFilter::KalmanFilter() {
	this->g1 = 0.5f;
	this->memory = 25;
	values = new int[25];
}

KalmanFilter::KalmanFilter(float g1, int memory) {
	this->g1 = g1;
	this->memory = memory;
	values = new int[memory];
}

int KalmanFilter::Filter(int value) {
	float sum = 0;
	float avg = 0;
	float gainInverse = (1 - g1);

	if (currentAmount < memory) {
		values[currentAmount++] = value;
	}
	else {
		values = ShiftArray(values);//pop first
		values[memory - 1] = value;
	}

	for (int i = 0; i < currentAmount; i++) {
		sum += values[i];
	}

	if (currentAmount > 0) {
		avg = sum / currentAmount;
	}

	return (g1 * value) + (gainInverse * avg);
}

int* KalmanFilter::ShiftArray(int arr[]) {
	for (int i = 0; i < memory; i++) {
		arr[i] = arr[i + 1];
	}

	arr[memory - 1] = 0.0;

	return arr;
}