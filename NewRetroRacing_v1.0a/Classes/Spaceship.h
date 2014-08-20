#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include <iostream>
#include "cocos2d.h"

#define LEFT_MARGIN 100.0
#define RAIL_WIDTH 30.0

#define INITIAL_X (LEFT_MARGIN + RAIL_WIDTH + 115.0)
#define INITIAL_Y 100.0



USING_NS_CC;

class Spaceship {
    
public:
    Spaceship(int ship_num);
    virtual ~Spaceship();
    
    void attachShipTo(Layer* layer, int zOrder);
    
    Sprite* getSpaceshipSprite();
    
    void setScheduler();
    
    bool relocateShip(int lane_change, int where);
    
private:
    float getXPositionOfShip(int lane_num);
    void abc(float delta);
    
private:
    Sprite *ship;

    float ratio;
    float distance;
    
    int num_lane;       // lane 개수
    int cur_lane_num;   // 현재 spaceship이 위치한 lane 번호
};

#endif


/*
 pineoc
 Car class
 2014.08.01
 */

/*
#pragma once

#include "cocos2d.h"
#include <string>

using namespace std;
using namespace cocos2d;

class car
{
public:
	car(std::string name, std::string carSpriteFileName);
	~car(void);
    
	void addOnRoad(Node* road);
	void addFire();
	void moveRight();
	void moveLeft();
	
	Vec2 getCarPosition();
	void setCarPosition(Vec2 pos);
    
	Sprite* getSpriteCar();
    
	void setMoveLength(float _moveLegnth);
    
private:
	//status for car
	string carName; // car Name
	string carSpriteFileName;
	Sprite* sCar;//car Sprite
	Size carSize;
	float moveLength;//move size of road
	int actionCount;
};

*/