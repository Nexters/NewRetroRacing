#include "GameScene.h"
#include "../HelloWorldScene.h"

#define SENS 0.01
USING_NS_CC;

using namespace CocosDenshion;

const unsigned width_basis = 720;
unsigned int sound1, sound2;
static float call_back_term = 1.5;

Scene* GameScene::createScene() {

	auto scene = Scene::create();
    auto layer = GameScene::create();

    scene->addChild(layer);
    call_back_term = 1.5;

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
    bg_layer->setTag(101);
    this->addChild(bg_layer);

    obstacles = new Obstacles();
    this->schedule(schedule_selector(GameScene::makeObstacles), call_back_term);
    this->scheduleUpdate();

    ///////

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

	sound1 = SimpleAudioEngine::getInstance()->playEffect("JetEngine.wav", true);
	SimpleAudioEngine:: getInstance()->setEffectsVolume(1.0);

    return true;
}

//////// obstacle

void GameScene::makeObstacles(float delta) {

	obstacles->addObstacle(this);
	if (call_back_term > 0.1)
		call_back_term -= 0.05;
}


/////// car


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
/*
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
	*/
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



	Sprite *spr_car = playerCar->getSpriteCar();
	Rect rect_car = spr_car->getBoundingBox();
	Array *obs_array = obstacles->getObstacleArray();
	for (int i = 0; i < obs_array->count(); i++) {
		Sprite *spr_obs = (Sprite*)obs_array->getObjectAtIndex(i);
		Rect rect_obs = spr_obs->getBoundingBox();
		if (rect_car.intersectsRect(rect_obs)) {
			CCLOG("충돌!!!!");

			SimpleAudioEngine::getInstance()->stopEffect(sound1);
			sound2 = SimpleAudioEngine::getInstance()->playEffect("Bomb.wav", false);

			spr_obs->stopAllActions();
			auto particle = ParticleExplosion::create();
			particle->setPosition(spr_car->getPosition());
			particle->setLife(1.0);
			particle->setZOrder(10);
			this->addChild(particle);
			this->unschedule(schedule_selector(GameScene::makeObstacles));
			//spr_obs->removeFromParent();
			//obs_array->removeObject(spr_obs, true);
			this->getChildByTag(101)->getChildByTag(0)->stopAllActions();
			this->getChildByTag(101)->getChildByTag(1)->stopAllActions();
			this->getChildByTag(101)->getChildByTag(2)->stopAllActions();
			this->getChildByTag(101)->getChildByTag(3)->stopAllActions();
			this->getChildByTag(101)->getChildByTag(10)->stopAllActions();
			this->getChildByTag(101)->getChildByTag(11)->stopAllActions();
			for (int j = 0; j < obs_array->count(); j++) {
				Sprite *spr_obs2 = (Sprite*)obs_array->getObjectAtIndex(j);
				spr_obs2->stopAllActions();
			}
			spr_car->stopAllActions();
			spr_car->getChildByTag(777)->removeFromParent();
			this->pause();
			this->scheduleOnce(schedule_selector(GameScene::gameOver), 3.0);
		}
	}
}

void GameScene::gameOver(float delta) {

	Director::getInstance()->replaceScene(HelloWorld::createScene());
	SimpleAudioEngine::getInstance()->stopEffect(sound2);
}
