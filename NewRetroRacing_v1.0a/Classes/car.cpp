#include "car.h"


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
	sCar->setPosition(s.width/4,180);
	road->addChild(sCar,3);
	moveLength = s.width/2;
	addFire();
}

void car::addFire()
{
	Sprite* sFire = Sprite::create("fire_1.png");
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
	MoveBy* act = MoveBy::create(0.2,Vec2(moveLength,0));
	sCar->runAction(act);
}

void car::moveLeft()
{
	MoveBy* act = MoveBy::create(0.2,Vec2(-moveLength,0));
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

void car::setMoveLength(float _moveLength)
{
	moveLength = _moveLength;
}