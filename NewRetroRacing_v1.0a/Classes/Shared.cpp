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

void Shared::resetGameSceneData() {
    
    elapsed_time = 0.0;
    current_speed = BASIC_SPEED;
}

float Shared::getCurrentSpeed() {
    
    return current_speed;
}

void Shared::setScreenSizeRatio(float ratio) {
    
    screen_size_ratio = ratio;
}

float Shared::getScreenSizeRatio() {
    
    return screen_size_ratio;
}

void Shared::resetElapsedTime() {
    
    elapsed_time = 0;
}

void Shared::incrementElapsedTime(int sec) {
    
    elapsed_time += sec;
    if (current_speed < SPEED_LIMIT)
        current_speed = BASIC_SPEED + powf(((float)elapsed_time * (SPEED_CONSTANT * 0.01)), 3);
}

float Shared::getCurrentElapsedTime() {
    
    return elapsed_time;
}

Shared::Shared() {
    
    elapsed_time = 0.0;
    screen_size_ratio = 1.0;
    current_speed = BASIC_SPEED;
}

Shared::~Shared() {
    
}