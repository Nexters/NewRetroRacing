#ifndef SHARED_H_
#define SHARED_H_

#include "cocos2d.h"

#define GAME_SCENE_WIDTH 720.0
#define GAME_SCENE_HEIGHT 1280.0

#define ROAD_WIDTH 520.0
#define ROAD_HEIGHT 250.0
#define RAIL_WIDTH 30.0
#define LEFT_MARGIN 100.0
#define MAX_LANE_CNT 4

#define SPEED_CONSTANT 10.0
#define BASIC_SPEED 500.0
#define SPEED_LIMIT 2200.0

#define RELOCATION_TIME 0.2

#define BG_MOVING_SPEED 100.0

USING_NS_CC;

class Shared {

public:
    static Shared* getInstance();
    static void releaseInstance();
    
public:
    static Vec2 adjustPoint(Vec2 point);
    
public:
    float getScreenSizeRatio();
    void setScreenSizeRatio(float ratio);
    
    float getCurrentElapsedTime();
    void incrementElapsedTime(int sec);
    
    float getCurrentSpeed();
    
    void resetGameSceneData();
    void resetElapsedTime();

	void setCoinData(int coin);
	int getCoinData();

	void addObsCount();
	int getObsCount();
    
private:
    Shared();
    virtual ~Shared();
    
private:
    static Shared* shared_instance;
    
private:
    int elapsed_time;
    float screen_size_ratio;
    float current_speed;
    int cur_lane_cnt;
	int coin_count;
	int obstacle_count;

private:
	bool feverModeBit;
	float saved_speed;

public:
	bool isFeverMode();
	void setFeverMode(bool bit);
	
};

float getXPositionOfObject(int lane_cnt, int lane_num, float ratio);
void releaseObject(Node *node);

#endif
