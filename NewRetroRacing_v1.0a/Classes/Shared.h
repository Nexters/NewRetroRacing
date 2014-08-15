#ifndef SHARED_H_
#define SHARED_H_

#include "cocos2d.h"

#define GAME_SCENE_WIDTH 720.0
#define GAME_SCENE_HEIGHT 1280.0

#define SPEED_CONSTANT 10.0
#define BASIC_SPEED 300.0
#define SPEED_LIMIT 1000.0

#define BG_MOVING_SPEED 100.0;

USING_NS_CC;

class Shared {

public:
    static Shared* getInstance();
    static void releaseInstance();
    static Vec2 adjustPoint(Vec2 point);
    
    void resetGameSceneData();

    float getCurrentSpeed();
    float getScreenSizeRatio();
    float getCurrentElapsedTime();
    
    void setScreenSizeRatio(float ratio);
    
    void resetElapsedTime();
    void incrementElapsedTime(int sec);

private:
    Shared();
    virtual ~Shared();
    
private:
    static Shared* shared_instance;
    
private:
    int elapsed_time;
    float screen_size_ratio;
    float current_speed;
    
};

#endif /* CONSTANTS_H_ */
