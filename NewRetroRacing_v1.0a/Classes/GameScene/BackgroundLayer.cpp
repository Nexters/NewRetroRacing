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
    this->addChild(spr_bg_img1);

    float spr_height = spr_bg_img1->getContentSize().height;
    float spr_width = spr_bg_img1->getContentSize().width;

    auto spr_bg_img2 = Sprite::create("bg.png");
    spr_bg_img2->setAnchorPoint(Point::ZERO);
    spr_bg_img2->setPosition(Point(0.0, spr_height));
    this->addChild(spr_bg_img2);

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
