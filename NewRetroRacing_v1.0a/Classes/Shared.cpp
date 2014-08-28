#include "Shared.h"
#include <iostream>
#include <cmath>

Shared* Shared::shared_instance = NULL;

Shared* Shared::getInstance() {
    
    if (shared_instance == NULL) {
        shared_instance = new Shared();
    }
    return shared_instance;
}
void Shared::releaseInstance() {
    
    if (shared_instance != NULL) {
        shared_instance->~Shared();
    }
}

Vec2 Shared::adjustPoint(Vec2 point) {
    
    if (shared_instance == NULL)
        return point;
    
    return point / shared_instance->screen_size_ratio;
}
float Shared::getXPositionOfObject(int lane_cnt, int lane_num, float ratio) {
    float distance = (ROAD_WIDTH - (RAIL_WIDTH * ratio * 2)) / lane_cnt;
    float x_pos = LEFT_MARGIN + (RAIL_WIDTH * ratio) + (distance / 2);
    for (int i = 0; i < lane_num; i++)
        x_pos += distance;
    return x_pos;
}

float Shared::getScreenSizeRatio() {
    
    return screen_size_ratio;
}
void Shared::setScreenSizeRatio(float ratio) {
    
    screen_size_ratio = ratio;
}

float Shared::getCurrentElapsedTime() {
    
    return elapsed_time;
}
void Shared::incrementElapsedTime(int sec) {
    
    elapsed_time += sec;
    float variation = powf(((float)elapsed_time * (SPEED_CONSTANT * 0.01)), 3);
    if (current_speed + variation < SPEED_LIMIT)
        current_speed = BASIC_SPEED + variation;
}

float Shared::getCurrentSpeed() {
    
    return current_speed;
}

void Shared::resetGameSceneData() {
    
    elapsed_time = 0.0;
    current_speed = BASIC_SPEED;
}
void Shared::resetElapsedTime() {
    
    elapsed_time = 0;
}

Shared::Shared() {
    
    elapsed_time = 0.0;
    screen_size_ratio = 1.0;
    current_speed = BASIC_SPEED;
}
Shared::~Shared() {
    
}