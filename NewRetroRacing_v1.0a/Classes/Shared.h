#ifndef SHARED_H_
#define SHARED_H_

#include "cocos2d.h"

#define GAME_SCENE_WIDTH 720.0
#define GAME_SCENE_HEIGHT 1280.0

#define ROAD_WIDTH 520.0

#define SPEED_CONSTANT 10.0
#define BASIC_SPEED 300.0
#define SPEED_LIMIT 1000.0

#define RELOCATION_TIME 0.2

#define BG_MOVING_SPEED 100.0

USING_NS_CC;

class Shared {

public:
    static Shared* getInstance();
    static void releaseInstance();
    static Vec2 adjustPoint(Vec2 point);
    
    float getCurrentSpeed();
    float getScreenSizeRatio();
    float getCurrentElapsedTime();
    Vec2 getValidHorizontalRangeOfCar();
    Vec2 getValidHorizontalRangeOfObstacle();
    Vec2 getTheNumberOfLanes();
    
    void setScreenSizeRatio(float ratio);
    void setValidHorizontalRangeOfCar(Vec2 range);
    void setValidHorizontalRangeOfObstacle(Vec2 range);
    void setTheNumberOfLanes(Vec2 _num_of_lanes);
    void incrementElapsedTime(int sec);
    
    void resetGameSceneData();
    void resetElapsedTime();
    
private:
    Shared();
    virtual ~Shared();
    
private:
    static Shared* shared_instance;
    
private:
    int elapsed_time;
    float screen_size_ratio;
    float current_speed;
    
    Vec2 car_valid_range;
    Vec2 obs_valid_range;
    
    Vec2 num_of_lanes;  // num_of_lanes.x: the number of current lanes
                        // num_of_lanes.y: the number of next lanes
};

#endif /* CONSTANTS_H_ */
