#include "Shared.h"
#include <cmath>

float SHARED::ELAPSED_TIME = 1.0;
float SHARED::SCREEN_SIZE_RATIO = 1.0;

float SHARED::getCurrentSpeed(int elapsed_time) {

	float speed = 0.0;
	speed += BASIC_SPEED;
	float accel = pow((elapsed_time * (SPEED_CONSTANT * 0.01)), 3);
	//float accel = elapsed_time * 10;
	if (accel <= 700)
		speed += accel;
	else
		speed += 700;

	return speed;
}
