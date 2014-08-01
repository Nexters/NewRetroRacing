#include "BackgroundLayer.h"

USING_NS_CC;

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

    auto spr_bg_img1 = Sprite::create("bg.png");
    spr_bg_img1->setAnchorPoint(Point::ZERO);
    spr_bg_img1->setPosition(Point::ZERO);
    this->addChild(spr_bg_img1);

    auto spr_bg_img2 = Sprite::create("bg.png");
    spr_bg_img2->setAnchorPoint(Point::ZERO);


    return true;
}
