#include "car.h"
#include "Shared.h"


car::car(std::string name, std::string _carSpriteFileName)
{
	carName = name;
	sCar = Sprite::create(_carSpriteFileName);
	sCar->setAnchorPoint(Vec2(0.5,0.5));
	carSize = sCar->getContentSize();
	

	actionCount = 0;

}

car::~car(void)
{
	sCar->autorelease();
}

void car::addOnRoad(Node* road)
{
	Size s = road->getContentSize();
	sCar->setPosition(245,180);
	road->addChild(sCar,3);
	moveLength = s.width/2;
	addFire();
}

void car::addFire()
{
	Sprite* sFire = Sprite::create("fire_1.png");
	sFire->setTag(777);
	sFire->setPosition(Vec2(85,-20));

	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("fire.plist");
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrameWithFileName("fire_1.png");
	animation->addSpriteFrameWithFileName("fire_2.png");
	animation->addSpriteFrameWithFileName("fire_3.png");
	animation->addSpriteFrameWithFileName("fire_4.png");

	sFire->runAction(RepeatForever::create(Animate::create(animation)));
	sCar->addChild(sFire);
}

void car::moveRight()
{

	MoveBy* act = MoveBy::create(0.01*SPEEDVAL,Vec2(moveLength,0));
	sCar->runAction(act);
}

void car::moveLeft()
{

	MoveBy* act = MoveBy::create(0.01*SPEEDVAL,Vec2(-moveLength,0));
	sCar->runAction(act);
}

Vec2 car::getCarPosition()
{
	return sCar->getPosition();
}

void car::setCarPosition(Vec2 pos)
{
	sCar->setPosition(pos);
}

void car::setCarScale(float scale)
{
	sCar->setScale(scale);
}

void car::setMoveLength(float _moveLength)
{
	moveLength = _moveLength;
}

Sprite* car::getSpriteCar()
{
	return this->sCar;
}

void car::changeRoadMode(float _roadMinX,float _roadMaxX,int currRoadNum, int changedRoadNum, int dir)
{
	roadMinX = _roadMinX+sCar->getContentSize().width/2;
	roadMaxX = _roadMaxX-sCar->getContentSize().width/2;
	roadNum = changedRoadNum;
	moveLength = (_roadMaxX-_roadMinX)/changedRoadNum;
	ScaleBy* act1;
	if(dir==-1)
	{//오른쪽으로 늘어날때
		sCar->setAnchorPoint(Vec2(0,0.5));
		act1 = ScaleBy::create(RELOCATION_TIME,(float)currRoadNum/(float)changedRoadNum);
	}
	else if(dir==0)
	{
		sCar->setAnchorPoint(Vec2(0.5,0.5));
		act1 = ScaleBy::create(RELOCATION_TIME,(float)currRoadNum/(float)changedRoadNum);
	}
	else if(dir==1)
	{//왼쪽으로 늘어날때
		sCar->setAnchorPoint(Vec2(1,0.5));
		act1 = ScaleBy::create(RELOCATION_TIME,(float)currRoadNum/(float)changedRoadNum);
	}
	
	sCar->runAction(act1);
	//sCar->setAnchorPoint(Vec2(0.5,0.5));
}

float car::getMinX()
{
	return roadMinX;
}
float car::getMaxX()
{
	return roadMaxX;
}