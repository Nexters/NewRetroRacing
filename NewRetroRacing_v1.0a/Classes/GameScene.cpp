#include "GameScene.h"
#include "HelloWorldScene.h"

/* for test */
#define LEFT_BTN_TAG1 	10
#define LEFT_BTN_TAG2 	11
#define LEFT_BTN_TAG3	12
#define LEFT_BTN_TAG4	13
#define LEFT_BTN_TAG5	14
#define LEFT_BTN_TAG6	15

#define RIGHT_BTN_TAG1 	20
#define RIGHT_BTN_TAG2 	21
#define RIGHT_BTN_TAG3	22
#define RIGHT_BTN_TAG4	23
#define RIGHT_BTN_TAG5	24
#define RIGHT_BTN_TAG6	25
/* ******** */

#define SENS 0.01
USING_NS_CC;

using namespace CocosDenshion;

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
    
	initGameSceneData();

// about BgLayerController
    bg_cont = new BgLayerController();
    bg_cont->initBgLayerWithDefault();
    bg_cont->runBgActions();
    bg_cont->attachBgLayerTo(this, 0);
    
// about RoadController
    road_cont = new RoadController();
    road_cont->attachRoadLayerTo(this, 1);

// update elpased time
    this->schedule(schedule_selector(GameScene::updateElpasedTime), 1.0);
    this->scheduleUpdate();

// test buttons
    attachTestButtons();
    
//
    s = new Spaceship(0);
    s->attachShipTo(this, 3);
    road_cont->addRoadChangeObserver(s);
    
    robj_cont = new RObjectController(2);
    robj_cont->attachRObjectsTo(this, 4);
    road_cont->addRoadChangeObserver(robj_cont);
    
    speed_label = Label::create();
    speed_label->setString("Speed: 0.0");
    speed_label->setSystemFontSize(30);
    speed_label->setAnchorPoint(Point(0.0, 0.5));
    speed_label->setPosition(Point(450.0, 1000.0));
    this->addChild(speed_label, 10);

    return true;
}

void GameScene::initGameSceneData() {
    
    speed_label = NULL;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Shared* shared = Shared::getInstance();
    shared->resetGameSceneData();
    shared->setScreenSizeRatio(visibleSize.width / GAME_SCENE_WIDTH);
    this->setAnchorPoint(Point::ZERO);
    this->setPosition(Point::ZERO);
    this->setScale(shared->getScreenSizeRatio());
    
    isTouchDown=false;
	initTouchPos[0]=0;
	initTouchPos[1]=0;
    
    auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
    
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}

void GameScene::updateElpasedTime(float delta) {
    
    Shared::getInstance()->incrementElapsedTime((int)delta);
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
    
    /* for test */
    buttonTouched(touch);
    /* ******** */
    
	initTouchPos[0] = touch->getLocation().x;
	initTouchPos[1] = touch->getLocation().y;
	currTouchPos[0] = touch->getLocation().x;
	currTouchPos[1] = touch->getLocation().y;

	isTouchDown = true;
	return true;
}
void GameScene::onTouchMoved(Touch* touch, Event* event) {
	
    currTouchPos[0] = touch->getLocation().x;
	currTouchPos[1] = touch->getLocation().y;
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {
    
	isTouchDown=false;
}

void GameScene::onTouchCancelled(Touch* touch, Event* event) {
    
	onTouchEnded(touch,event);
}

void GameScene::update(float dt) {
    
    if (speed_label != NULL) {
        std::string *speed_str = new std::string("Speed: ");
        char speed[10];
        sprintf(speed, "%f", Shared::getInstance()->getCurrentSpeed());
        speed_str->append(speed);
        speed_label->setString(speed_str->c_str());
        free(speed_str);
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*
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
				CCLOG("Left ");
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
				CCLOG("Right ");
				playerCar->moveRight();
			}
			isTouchDown=false;
		}
	}
     */
}

void GameScene::gameOver(float delta) {

	Director::getInstance()->replaceScene(HelloWorld::createScene());
}



// for test

void GameScene::attachTestButtons() {
    
    auto left_btn1 = Sprite::create("CloseSelected.png");
    left_btn1->setAnchorPoint(Point(0.5, 0.5));
    left_btn1->setPosition(Point(40, 100));
    left_btn1->setScale(2.0);
    left_btn1->setTag(LEFT_BTN_TAG1);
    this->addChild(left_btn1,3);
    
    auto left_btn2 = Sprite::create("CloseSelected.png");
	left_btn2->setAnchorPoint(Point(0.5, 0.5));
	left_btn2->setPosition(Point(40, 200));
	left_btn2->setScale(2.0);
	left_btn2->setTag(LEFT_BTN_TAG2);
	this->addChild(left_btn2,3);
    
    auto left_btn3 = Sprite::create("CloseSelected.png");
	left_btn3->setAnchorPoint(Point(0.5, 0.5));
	left_btn3->setPosition(Point(40, 300));
	left_btn3->setScale(2.0);
	left_btn3->setTag(LEFT_BTN_TAG3);
	this->addChild(left_btn3,3);
    
    auto left_btn4 = Sprite::create("CloseSelected.png");
	left_btn4->setAnchorPoint(Point(0.5, 0.5));
	left_btn4->setPosition(Point(40, 400));
	left_btn4->setScale(2.0);
	left_btn4->setTag(LEFT_BTN_TAG4);
	this->addChild(left_btn4,3);
    
    auto left_btn5 = Sprite::create("CloseSelected.png");
	left_btn5->setAnchorPoint(Point(0.5, 0.5));
	left_btn5->setPosition(Point(40, 500));
	left_btn5->setScale(2.0);
	left_btn5->setTag(LEFT_BTN_TAG5);
	this->addChild(left_btn5,3);
    
    
    auto right_btn1 = Sprite::create("CloseSelected.png");
    right_btn1->setAnchorPoint(Point(0.5, 0.5));
    right_btn1->setPosition(Point(720 - 40, 100));
    right_btn1->setScale(2.0);
    right_btn1->setTag(RIGHT_BTN_TAG1);
    this->addChild(right_btn1,3);
    
    auto right_btn2 = Sprite::create("CloseSelected.png");
	right_btn2->setAnchorPoint(Point(0.5, 0.5));
	right_btn2->setPosition(Point(720 - 40, 200));
	right_btn2->setScale(2.0);
	right_btn2->setTag(RIGHT_BTN_TAG2);
	this->addChild(right_btn2,3);
    
	auto right_btn3 = Sprite::create("CloseSelected.png");
	right_btn3->setAnchorPoint(Point(0.5, 0.5));
	right_btn3->setPosition(Point(720 - 40, 300));
	right_btn3->setScale(2.0);
	right_btn3->setTag(RIGHT_BTN_TAG3);
	this->addChild(right_btn3,3);
    
	auto right_btn4 = Sprite::create("CloseSelected.png");
	right_btn4->setAnchorPoint(Point(0.5, 0.5));
	right_btn4->setPosition(Point(720 - 40, 400));
	right_btn4->setScale(2.0);
	right_btn4->setTag(RIGHT_BTN_TAG4);
	this->addChild(right_btn4,3);
    
	auto right_btn5 = Sprite::create("CloseSelected.png");
	right_btn5->setAnchorPoint(Point(0.5, 0.5));
	right_btn5->setPosition(Point(720 - 40, 500));
	right_btn5->setScale(2.0);
	right_btn5->setTag(RIGHT_BTN_TAG5);
	this->addChild(right_btn5,3);
    
	auto left_btn6 = Sprite::create("CloseSelected.png");
	left_btn6->setAnchorPoint(Point(0.5, 0.5));
	left_btn6->setPosition(Point(40, 900));
	left_btn6->setScale(2.0);
	left_btn6->setTag(LEFT_BTN_TAG6);
	this->addChild(left_btn6,3);
    
    auto right_btn6 = Sprite::create("CloseSelected.png");
	right_btn6->setAnchorPoint(Point(0.5, 0.5));
	right_btn6->setPosition(Point(720 - 40, 900));
	right_btn6->setScale(2.0);
	right_btn6->setTag(RIGHT_BTN_TAG6);
	this->addChild(right_btn6,3);
}

bool GameScene::buttonTouched(Touch *touch) {
    
    if (road_cont == NULL) {
        return false;
    }
    
    Point touch_location = Shared::getInstance()->adjustPoint(touch->getLocation());
    
	Sprite *left_btn1 = (Sprite*)this->getChildByTag(LEFT_BTN_TAG1);
	Rect left_btn1_rect = left_btn1->getBoundingBox();
    
	Sprite *left_btn2 = (Sprite*)this->getChildByTag(LEFT_BTN_TAG2);
	Rect left_btn2_rect = left_btn2->getBoundingBox();
    
	Sprite *left_btn3 = (Sprite*)this->getChildByTag(LEFT_BTN_TAG3);
	Rect left_btn3_rect = left_btn3->getBoundingBox();
    
	Sprite *left_btn4 = (Sprite*)this->getChildByTag(LEFT_BTN_TAG4);
	Rect left_btn4_rect = left_btn4->getBoundingBox();
    
	Sprite *left_btn5 = (Sprite*)this->getChildByTag(LEFT_BTN_TAG5);
	Rect left_btn5_rect = left_btn5->getBoundingBox();
    
	Sprite *left_btn6 = (Sprite*)this->getChildByTag(LEFT_BTN_TAG6);
	Rect left_btn6_rect = left_btn6->getBoundingBox();
    
	////
    
	Sprite *right_btn1 = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG1);
	Rect right_btn1_rect = right_btn1->getBoundingBox();
    
	Sprite *right_btn2 = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG2);
	Rect right_btn2_rect = right_btn2->getBoundingBox();
    
	Sprite *right_btn3 = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG3);
	Rect right_btn3_rect = right_btn3->getBoundingBox();
    
	Sprite *right_btn4 = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG4);
	Rect right_btn4_rect = right_btn4->getBoundingBox();
    
	Sprite *right_btn5 = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG5);
	Rect right_btn5_rect = right_btn5->getBoundingBox();
    
    Sprite *right_btn6 = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG6);
	Rect right_btn6_rect = right_btn6->getBoundingBox();
    
    
	if (left_btn1_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN1 TOUCHED!!");
		road_cont->attachLane(1, 1);    // 왼쪽에 한줄 추가
		return true;
	}
	else if (left_btn2_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN2 TOUCHED!!");
		road_cont->attachLane(1, 2);    // 오른쪽에 한줄 추가
		return true;
	}
	else if (left_btn3_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN3 TOUCHED!!");
		road_cont->attachLane(2, 1);    // 왼쪽에 두줄 추가
		return true;
	}
	else if (left_btn4_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN4 TOUCHED!!");
		road_cont->attachLane(2, 2);    // 오른쪽에 두줄 추가
		return true;
	}
	else if (left_btn5_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN5 TOUCHED!!");
		road_cont->attachLane(2, 3);    // 양쪽에 한줄씩 추가
		return true;
	}
	else if (right_btn1_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN1 TOUCHED!!");
		road_cont->detachLane(1, 1);    // 왼쪽에 한줄 삭제
		return true;
	}
	else if (right_btn2_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN2 TOUCHED!!");
		road_cont->detachLane(1, 2);    // 오른쪽에 한줄 삭제
		return true;
	}
	else if (right_btn3_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN3 TOUCHED!!");
		road_cont->detachLane(2, 1);    // 왼쪽에 두줄 삭제
		return true;
	}
	else if (right_btn4_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN4 TOUCHED!!");
		road_cont->detachLane(2, 2);    // 오른쪽에 두줄 삭제
		return true;
	}
	else if (right_btn5_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN5 TOUCHED!!");
		road_cont->detachLane(2, 3);    // 양쪽에 한줄씩 삭제
		return true;
	}
	else if (left_btn6_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN6 TOUCHED!!");
        Shared::getInstance()->resetElapsedTime();
		return true;
	}
    else if (right_btn6_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN6 TOUCHED!!");
        robj_cont->startGeneratingRObjects();
		return true;
	}
	else {
		CCLOG("NOT TOUCHED!!");
		return false;
	}
}
