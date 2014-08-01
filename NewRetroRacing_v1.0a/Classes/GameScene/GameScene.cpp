#include "GameScene/GameScene.h"
#include "GameScene/BackgroundLayer.h"

#define SENS 0.02
USING_NS_CC;

const unsigned width_basis = 720;

Scene* GameScene::createScene() {

	auto scene = Scene::create();
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->setAnchorPoint(Point::ZERO);
    this->setPosition(Point::ZERO);
    this->setScale(visibleSize.width / width_basis);


    auto bg_layer = BackgroundLayer::createBGLayer();
    this->addChild(bg_layer);

	initData();

	playerCar = new car("default","rocket.png");
	playerCar->addOnRoad(this);
	playerCar->setMoveLength(230);

	this->scheduleUpdate();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

void GameScene::initData()
{
	isTouchDown=false;
	initTouchPos[0]=0;
	initTouchPos[1]=0;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	initTouchPos[0] = touch->getLocation().x;
	initTouchPos[1] = touch->getLocation().y;
	currTouchPos[0] = touch->getLocation().x;
	currTouchPos[1] = touch->getLocation().y;

	isTouchDown = true;
	return true;
}
void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	currTouchPos[0] = touch->getLocation().x;
	currTouchPos[1] = touch->getLocation().y;
}
void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	isTouchDown=false;
}
void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
	onTouchEnded(touch,event);
}

void GameScene::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if(true==isTouchDown)
	{
		if(initTouchPos[0]-currTouchPos[0] > visibleSize.width*SENS)
		{
			float leftsize = playerCar->getCarPosition().x;
			int running = playerCar->getSpriteCar()->getNumberOfRunningActions();
			if (leftsize <= 260 || running>0)
			{

			}
			else
			{
				CCLog("Left ");
				playerCar->moveLeft();
			}
			isTouchDown=false;
		}
		else if(initTouchPos[0]-currTouchPos[0] < -visibleSize.width*SENS)
		{
			float rightsize = playerCar->getCarPosition().x;
			int running = playerCar->getSpriteCar()->getNumberOfRunningActions();
			if (rightsize >= 430 || running>0)
			{

			}
			else
			{
				CCLog("Right ");
				playerCar->moveRight();
			}
			isTouchDown=false;
		}
	}
}
