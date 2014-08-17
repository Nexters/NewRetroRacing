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

float Shared::getCurrentSpeed() {
    
    return current_speed;
}

float Shared::getScreenSizeRatio() {
    
    return screen_size_ratio;
}

float Shared::getCurrentElapsedTime() {
    
    return elapsed_time;
}

Vec2 Shared::getValidHorizontalRangeOfCar() {
    
    return car_valid_range;
}

Vec2 Shared::getValidHorizontalRangeOfObstacle() {
    
    return obs_valid_range;
}

float Shared::getTheNumberOfLanes() {
    
    return num_of_lanes;
}

void Shared::setScreenSizeRatio(float ratio) {
    
    screen_size_ratio = ratio;
}

void Shared::setValidHorizontalRangeOfCar(Vec2 range) {

    car_valid_range = range;
}

void Shared::setValidHorizontalRangeOfObstacle(Vec2 range) {
    
    obs_valid_range = range;
}

void Shared::setTheNumberOfLanes(float _num_of_lanes) {
    
    num_of_lanes =  _num_of_lanes;
}

void Shared::incrementElapsedTime(int sec) {
    
    elapsed_time += sec;
    if (current_speed < SPEED_LIMIT)
        current_speed = BASIC_SPEED + powf(((float)elapsed_time * (SPEED_CONSTANT * 0.01)), 3);
}

void Shared::resetGameSceneData() {
    
    elapsed_time = 0.0;
    current_speed = BASIC_SPEED;
    car_valid_range = Vec2::ZERO;
    obs_valid_range = Vec2::ZERO;
    num_of_lanes = 0;
}

void Shared::resetElapsedTime() {
    
    elapsed_time = 0;
}

Shared::Shared() {
    
    elapsed_time = 0.0;
    screen_size_ratio = 1.0;
    current_speed = BASIC_SPEED;
    car_valid_range = Vec2::ZERO;
    obs_valid_range = Vec2::ZERO;
    num_of_lanes = 0;
}

Shared::~Shared() {
    
}