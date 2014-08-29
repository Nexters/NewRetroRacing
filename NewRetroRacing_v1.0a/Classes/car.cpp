#include "car.h"
#include "Shared.h"


car::car(std::string name, std::string _carSpriteFileName)
{
	carName = name;
	sCar = Sprite::create(_carSpriteFileName);
	sCar->setAnchorPoint(Vec2(0.5,0.5));
	carSize = sCar->getContentSize();
	currLine=1;
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
	currLine++;
	MoveBy* act = MoveBy::create(0.01*SPEEDVAL,Vec2(moveLength,0));
	sCar->runAction(act);
}

void car::moveLeft()
{
	currLine--;
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
	
	roadNum = changedRoadNum;
	//moveLength = (_roadMaxX-_roadMinX)/changedRoadNum;
	//moveLength = 125*(4.0/(float)changedRoadNum);
	
	if(roadNum==2)
	{	moveLength=240.0;}
	else if(roadNum==3)
	{	moveLength=163.0;}
	else if(roadNum==4)
	{	moveLength=120.0;}
	
	roadMinX = _roadMinX+moveLength;
	roadMaxX = _roadMaxX-moveLength;
	ScaleBy* act1;
	DelayTime* act2;
	Sequence* actR;
	CCLog("changedRoadNum : %d",changedRoadNum);
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
	act2 = DelayTime::create(0);
	if((float)currRoadNum/(float)changedRoadNum>1)
		act2 = DelayTime::create(Shared::getInstance()->getCurrentElapsedTime());
	actR = Sequence::create(act2,act1,NULL);
	
	sCar->runAction(actR);
	setPositionCorrect(currRoadNum,changedRoadNum);
}

void car::setPositionCorrect(int fromRoad, int toRoad)
{//도로의 갯수와 현재 위치해 있는 도로에 따라 위치값 정렬
	sCar->setAnchorPoint(Vec2(0.5,0.5));
	//currLine : 현재 도로 위치
	//roadNum : 도로의 수
	/*
	switch (currLine)
	{
	case 1://현재 위치 맨 왼쪽
		{
			if(roadNum==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(245,180));
				sCar->runAction(act1);
			}
			else if(roadNum==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(200,180));
				sCar->runAction(act1);
			}
			else if(roadNum==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(180,180));
				sCar->runAction(act1);
			}
		}
		break;
	case 2:
		{
			if(roadNum==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(485,180));
				sCar->runAction(act1);
			}
			else if(roadNum==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(363,180));
				sCar->runAction(act1);
			}
			else if(roadNum==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(300,180));
				sCar->runAction(act1);
			}
		}
		break;
	case 3:
		{
			if(roadNum==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(485,180));
				sCar->runAction(act1);
			}
			else if(roadNum==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(526,180));
				sCar->runAction(act1);
			}
			else if(roadNum==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(420,180));
				sCar->runAction(act1);
			}
		}
		break;
	case 4:
		{
			if(roadNum==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(485,180));
				sCar->runAction(act1);
			}
			else if(roadNum==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(526,180));
				sCar->runAction(act1);
			}
			else if(roadNum==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(540,180));
				sCar->runAction(act1);
			}
		}
		break;
	default:
		break;
	}
	*/
	/*
	switch (roadNum)
	{
	case 2:
		{
			if(currLine==1)
			{
				auto act1 = MoveTo::create(0.2,Vec2(245,180));
				sCar->runAction(act1);
			}
			else if(currLine==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(485,180));
				sCar->runAction(act1);
			}
			else if(currLine==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(485,180));
				sCar->runAction(act1);
				currLine=2;
			}
			else if(currLine==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(485,180));
				sCar->runAction(act1);
				currLine=2;
			}
		}
		break;
	case 3:
		{
			if(currLine==1)
			{
				auto act1 = MoveTo::create(0.2,Vec2(200,180));
				sCar->runAction(act1);
			}
			else if(currLine==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(363,180));
				sCar->runAction(act1);
			}
			else if(currLine==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(526,180));
				sCar->runAction(act1);
				currLine=3;
			}
			else if(currLine==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(526,180));
				sCar->runAction(act1);
				currLine=3;
			}
		}
		break;
	case 4:
		{
			if(currLine==1)
			{
				auto act1 = MoveTo::create(0.2,Vec2(180,180));
				sCar->runAction(act1);
			}
			else if(currLine==2)
			{
				auto act1 = MoveTo::create(0.2,Vec2(300,180));
				sCar->runAction(act1);
			}
			else if(currLine==3)
			{
				auto act1 = MoveTo::create(0.2,Vec2(420,180));
				sCar->runAction(act1);
			}
			else if(currLine==4)
			{
				auto act1 = MoveTo::create(0.2,Vec2(540,180));
				sCar->runAction(act1);
			}
		}
		break;
	default:
		break;
	}
	*/

}

float car::getMinX()
{
	return roadMinX;
}
float car::getMaxX()
{
	return roadMaxX;
}