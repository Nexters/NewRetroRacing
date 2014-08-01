#include "BackgroundLayer.h"

USING_NS_CC;

const unsigned int BG_MOVING_TIME = 10;
const unsigned int RAIL_MOVING_TIME = 3;
bool flag1, flag2;

Layer* BackgroundLayer::createBGLayer() {

	auto layer = BackgroundLayer::create();
	return layer;
}

bool BackgroundLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto spr_bg_img1 = Sprite::create("bg.png");
    spr_bg_img1->setAnchorPoint(Point::ZERO);
    spr_bg_img1->setPosition(Point::ZERO);
    this->addChild(spr_bg_img1, 0);

    float spr_height = spr_bg_img1->getContentSize().height;
    float spr_width = spr_bg_img1->getContentSize().width;

    auto spr_bg_img2 = Sprite::create("bg.png");
    spr_bg_img2->setAnchorPoint(Point::ZERO);
    spr_bg_img2->setPosition(Point(0.0, spr_height));
    this->addChild(spr_bg_img2, 0);

    flag1 = true;
    flag2 = false;

    auto act1 = MoveBy::create(BG_MOVING_TIME, Point(0.0, -spr_height));
    auto act2 = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::action_call_back1, this));
    auto act3 = Sequence::create(act1, act2, NULL);
    auto act4 = RepeatForever::create(act3);
    spr_bg_img1->runAction(act4);

    auto act5 = MoveBy::create(BG_MOVING_TIME, Point(0.0, -spr_height));
	auto act6 = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::action_call_back2, this));
	auto act7 = Sequence::create(act5, act6, NULL);
	auto act8 = RepeatForever::create(act7);
	spr_bg_img2->runAction(act8);

	////////////////////////////////////////

	Array *rail_arr = Array::create();
	rail_arr->retain();

	for (int i = 0; i < 4; i++) {
		auto spr_rail = Sprite::create("rail.png");
		spr_rail->setAnchorPoint(Point(0.5, 0.0));
		spr_rail->setPosition(Point(spr_bg_img1->getContentSize().width/2, spr_rail->getContentSize().height * i));
		this->addChild(spr_rail);
		rail_arr->addObject(spr_rail);
	}
/*
	for (int i = 0; i < 4; i++) {
		Sprite *spr_rail = (Sprite*)rail_arr->getObjectAtIndex(i);
		auto act_rail1 = MoveTo::create(RAIL_MOVING_TIME, Point(spr_bg_img1->getContentSize().width/2, -spr_rail->getContentSize().height));
		auto act_rail2 = Place::create(Point(spr_bg_img1->getContentSize().width/2, spr_rail->getContentSize().height * 3));
		auto act_rail3 = Sequence::create(act_rail1, act_rail2, NULL);
		auto act_rail4 = RepeatForever::create(act_rail3);
		spr_rail->runAction(act_rail4);
	}
*/

    return true;
}

void BackgroundLayer::action_call_back1(Ref *sender) {

	auto spr = (Sprite*)sender;
	if (flag1) {
		spr->setPosition(Point(0.0, spr->getContentSize().height));
		flag1 = false;
	}
	else {
		spr->setPosition(Point(0.0, 0.0));
		flag1 = true;
	}
}

void BackgroundLayer::action_call_back2(Ref *sender) {

	auto spr = (Sprite*)sender;
	if (flag1) {
		spr->setPosition(Point(0.0, spr->getContentSize().height));
		flag2 = false;
	}
	else {
		spr->setPosition(Point(0.0, 0.0));
		flag2 = true;
	}
}
