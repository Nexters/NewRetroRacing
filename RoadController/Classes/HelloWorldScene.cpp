#include "HelloWorldScene.h"
#include "Shared.h"

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

float ttt = 1.0;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SHARED::SCREEN_SIZE_RATIO = visibleSize.width / 720;

    this->setAnchorPoint(Point::ZERO);
    this->setPosition(Point::ZERO);
    this->setScale(SHARED::SCREEN_SIZE_RATIO);
/*
    auto spr = Sprite::create("HelloWorld.png");
    spr->setAnchorPoint(Point(0.5, 0.5));
    spr->setPosition(Point(GAME_SCENE_WIDTH / 2.0, GAME_SCENE_HEIGHT / 2.0));
    this->addChild(spr, 10);
    auto spr2 = Sprite::create("HelloWorld.png");
	spr2->setAnchorPoint(Point(0.5, 0.5));
	spr2->setPosition(Point(GAME_SCENE_WIDTH / 2.0, GAME_SCENE_HEIGHT / 2.0 + 300));
	this->addChild(spr2, 11);

    Rect spr_rect = spr->getBoundingBox();
    spr->setTextureRect(Rect(0, 100,
    		spr_rect.size.width, spr_rect.size.height / 2.0));
    		*/

/*
    auto hello_world = Sprite::create("HelloWorld.png");
    hello_world->setAnchorPoint(Point(0.5, 0.5));
    hello_world->setPosition(720 / 2, 1280 / 2);
    this->addChild(hello_world);

    auto rocket = Sprite::create("rocket.png");
    rocket->setAnchorPoint(Point(0.5, 0.5));
    rocket->setPosition(hello_world->getContentSize().width / 2, hello_world->getContentSize().height / 2);
    hello_world->addChild(rocket);


    auto act1 = MoveTo::create(2.0,
    		Point(hello_world->getContentSize().width - rocket->getContentSize().width / 2 + 50,
    				hello_world->getContentSize().height / 2));
    rocket->runAction(act1);

    auto act1 = MoveBy::create(ttt, Point(50.0, 0));
    auto act2 = CallFuncN::create(CC_CALLBACK_1(HelloWorld::action_callback, this));
    auto act3 = Sequence::create(act1, act2, NULL);
    rocket->runAction(act3);
*/

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
	left_btn6->setPosition(Point(40, 1100));
	left_btn6->setScale(2.0);
	left_btn6->setTag(LEFT_BTN_TAG6);
	this->addChild(left_btn6,3);


    auto touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()
    		->addEventListenerWithFixedPriority(touch_listener, 1);

    bg_cont = new BgLayerController();
    bg_cont->initBgLayerWithDefault();
    bg_cont->attachBgLayerTo(this, 0);
    bg_cont->runBgActions();
    
    road_cont = new RoadController();
    road_cont->attachRoadLayerTo(this, 1);

    this->schedule(schedule_selector(HelloWorld::update_time), 5.0);

    return true;
}

void HelloWorld::update_time(float delta) {

	SHARED::ELAPSED_TIME += 5.0;
	//CCLOG("%f", ELAPSED_TIME);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {

	Point touch_location = touch->getLocation();
	touch_location = touch_location / SHARED::SCREEN_SIZE_RATIO;

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


	if (left_btn1_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN1 TOUCHED!!");
		road_cont->attachLane(1, 1);
		return true;
	}
	else if (left_btn2_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN2 TOUCHED!!");
		road_cont->attachLane(1, 2);
		return true;
	}
	else if (left_btn3_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN3 TOUCHED!!");
		road_cont->attachLane(2, 1);
		return true;
	}
	else if (left_btn4_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN4 TOUCHED!!");
		road_cont->attachLane(2, 2);
		return true;
	}
	else if (left_btn5_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN5 TOUCHED!!");
		road_cont->attachLane(2, 3);
		return true;
	}
	else if (right_btn1_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN1 TOUCHED!!");
		road_cont->detachLane(1, 1);
		return true;
	}
	else if (right_btn2_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN2 TOUCHED!!");
		road_cont->detachLane(1, 2);
		return true;
	}
	else if (right_btn3_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN3 TOUCHED!!");
		road_cont->detachLane(2, 1);
		return true;
	}
	else if (right_btn4_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN4 TOUCHED!!");
		road_cont->detachLane(2, 2);
		return true;
	}
	else if (right_btn5_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN5 TOUCHED!!");
		road_cont->detachLane(2, 3);
		return true;
	}
	else if (left_btn6_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN6 TOUCHED!!");
		SHARED::ELAPSED_TIME = 0.0;
		return true;
	}
	else {
		CCLOG("NOT TOUCHED!!");
		return false;
	}
}

void HelloWorld::action_callback(Ref *spr) {

	CCLOG("aaa");
	Sprite *rocket = (Sprite*)spr;
	auto act1 = MoveBy::create(ttt, Point(50.0, 0));
	auto act2 = CallFuncN::create(CC_CALLBACK_1(HelloWorld::action_callback, this));
	auto act3 = Sequence::create(act1, act2, NULL);
	rocket->runAction(act3);

		ttt += 3.0;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
