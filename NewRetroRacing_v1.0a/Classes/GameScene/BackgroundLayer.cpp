#include "BackgroundLayer.h"

USING_NS_CC;

const float BG_MOVING_TIME = 10;
const float RAIL_MOVING_TIME = 0.5;
bool flag1, flag2;

Layer* BackgroundLayer::createBGLayer() {

	return BackgroundLayer::create();
}

bool BackgroundLayer::init() {

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto spr_bg_img1 = Sprite::create("bg.png");
    auto spr_bg_img2 = Sprite::create("bg.png");
    spr_bg_img1->setTag(10);
    spr_bg_img2->setTag(11);
    auto *flag_bg_img1 = new bool(true);
    auto *flag_bg_img2 = new bool(false);

    float spr_height = spr_bg_img1->getContentSize().height;
    //float spr_width = spr_bg_img1->getContentSize().width;

    spr_bg_img1->setAnchorPoint(Point::ZERO);
    spr_bg_img1->setPosition(Point::ZERO);
    this->addChild(spr_bg_img1, 0);

    spr_bg_img2->setAnchorPoint(Point::ZERO);
    spr_bg_img2->setPosition(Point(0.0, spr_height));
    this->addChild(spr_bg_img2, 0);

    auto bg_img1_act1 = MoveBy::create(BG_MOVING_TIME, Point(0.0, -spr_height));
    auto bg_img1_act2 = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::BgActionCallBack, this));
    auto bg_img1_act3 = Sequence::create(bg_img1_act1, bg_img1_act2, NULL);
    auto bg_img1_act4 = RepeatForever::create(bg_img1_act3);
    spr_bg_img1->runAction(bg_img1_act4);

    auto bg_img2_act1 = MoveBy::create(BG_MOVING_TIME, Point(0.0, -spr_height));
	auto bg_img2_act2 = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::BgActionCallBack, this));
	auto bg_img2_act3 = Sequence::create(bg_img2_act1, bg_img2_act2, NULL);
	auto bg_img2_act4 = RepeatForever::create(bg_img2_act3);
	spr_bg_img2->runAction(bg_img2_act4);

	for (int i = 0; i < 4; i++) {
		auto spr_rail = Sprite::create("rail.png");
		spr_rail->setTag(i);
		spr_rail->setAnchorPoint(Point(0.5, 0.0));
		spr_rail->setPosition(Point(spr_bg_img1->getContentSize().width/2, spr_rail->getContentSize().height * i));
		this->addChild(spr_rail);

		auto rail_act1 = MoveBy::create(RAIL_MOVING_TIME, Point(0.0, -spr_rail->getContentSize().height));
		auto rail_act2 = CallFuncN::create(CC_CALLBACK_1(BackgroundLayer::RailActionCallBack, this));
		auto rail_act3 = Sequence::create(rail_act1, rail_act2, NULL);
		auto rail_act4 = RepeatForever::create(rail_act3);
		spr_rail->runAction(rail_act4);
	}

    return true;
}

void BackgroundLayer::BgActionCallBack(Ref *sender) {

	auto spr = (Sprite*)sender;
	float y_ax = spr->getPositionY();
	float spr_height = spr->getContentSize().height;

	if (y_ax <= -spr_height) {
		spr->setPosition(Point(0.0, spr->getContentSize().height));
	}
	else {
		spr->setPosition(Point(0.0, 0.0));
	}
}

void BackgroundLayer::RailActionCallBack(Ref *sender) {

	auto spr = (Sprite*)sender;
	float y_ax = spr->getPositionY();
	float spr_height = spr->getContentSize().height;

	if (y_ax <= -spr_height) {
		spr->setPosition(Point(spr->getPositionX(), spr->getContentSize().height * 3));
	}
	else if (y_ax <= 0) {
		spr->setPosition(Point(spr->getPositionX(), spr->getContentSize().height * 0));
	}
	else if (y_ax <= spr_height) {
		spr->setPosition(Point(spr->getPositionX(), spr->getContentSize().height * 1));
	}
	else if (y_ax <= spr_height * 2) {
		spr->setPosition(Point(spr->getPositionX(), spr->getContentSize().height * 2));
	}
}
