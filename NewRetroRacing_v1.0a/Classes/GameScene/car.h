/*
pineoc
Car class
2014.08.01
*/
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