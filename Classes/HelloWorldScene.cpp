#include "HelloWorldScene.h"


#define LEFT_BTN_TAG 	10
#define RIGHT_BTN_TAG 	11

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SCREEN_SIZE_RATIO = visibleSize.width / 720;
    CURRENT_SPEED_LEVEL = 1.0;

    this->setAnchorPoint(Point::ZERO);
    this->setPosition(Point::ZERO);
    this->setScale(SCREEN_SIZE_RATIO);

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
*/

    auto left_btn = Sprite::create("CloseSelected.png");
    left_btn->setAnchorPoint(Point(0.5, 0.5));
    left_btn->setPosition(Point(40, 100));
    left_btn->setScale(2.0);
    left_btn->setTag(LEFT_BTN_TAG);
    this->addChild(left_btn);

    auto right_btn = Sprite::create("CloseSelected.png");
    right_btn->setAnchorPoint(Point(0.5, 0.5));
    right_btn->setPosition(Point(720 - 40, 100));
    right_btn->setScale(2.0);
    right_btn->setTag(RIGHT_BTN_TAG);
    this->addChild(right_btn);

    auto touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()
    		->addEventListenerWithFixedPriority(touch_listener, 1);

    road_cont = new RoadController();
    road_cont->attachRoadLayerTo(this);

    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {

	Point touch_location = touch->getLocation();
	touch_location = touch_location / SCREEN_SIZE_RATIO;

	Sprite *left_btn = (Sprite*)this->getChildByTag(LEFT_BTN_TAG);
	Rect left_btn_rect = left_btn->getBoundingBox();
	Sprite *right_btn = (Sprite*)this->getChildByTag(RIGHT_BTN_TAG);
	Rect right_btn_rect = right_btn->getBoundingBox();

	if (left_btn_rect.containsPoint(touch_location)) {
		CCLOG("LEFT BTN TOUCHED!!");
		road_cont->attachLane(1);
		return true;
	}
	else if (right_btn_rect.containsPoint(touch_location)) {
		CCLOG("RIGHT BTN TOUCHED!!");
		road_cont->attachLane(2);
		return true;
	}
	else {
		CCLOG("NOT TOUCHED!!");
		return false;
	}
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
