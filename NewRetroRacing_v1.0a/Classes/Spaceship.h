#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include "cocos2d.h"
#include "RoadChangeObserver.h"

#define INITIAL_X (LEFT_MARGIN + RAIL_WIDTH + 115.0)
#define INITIAL_Y 150.0

#define SPEEDVAL 5

USING_NS_CC;

class Spaceship : public RoadChangeObserver {
    
public:
    Spaceship(int ship_num);
    void releaseSpaceship();
    
    void attachShipTo(Layer* layer, int zOrder);
    Rect getRect() { return ship->getBoundingBox(); }
    
    virtual void onLaneChange(int current, int next, int to_where);
    virtual void onVerticalRangeChange(Vec2 range);

	Vec2 getSpaceShipPos();
	Vec2 getMoveRange();
	Sprite* getSpriteSpaceShip();
	void moveRight();
	void moveLeft();

private:
    void relocateShip(int lane_change, int where);
    float getXPositionOfShip(int lane_num);
    void abc(float delta);
	void addFire();
    ~Spaceship();
    
private:
    Sprite *ship;

    float ratio;
    float distance;
    
    int num_lane;       // lane 개수
    int cur_lane_num;   // 현재 spaceship이 위치한 lane 번호
	Vec2 roadRange;
};

#endif
