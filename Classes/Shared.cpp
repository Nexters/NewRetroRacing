#include "Shared.h"
#include <cmath>

float getCurrentSpeed(int elapsed_time) {

	float speed = 0.0;
	speed += BASIC_SPEED;
	speed += pow((elapsed_time * (SPEED_CONSTANT * 0.01)), 3);

	return speed;
}
