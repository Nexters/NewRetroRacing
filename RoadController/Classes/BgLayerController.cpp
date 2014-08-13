#include "BgLayerController.h"
#include "Shared.h"

BgLayerController::BgLayerController() {
    
    bg_layer = Layer::create();
    bg_spr1 = NULL;
    bg_spr2 = NULL;
    bg_action_is_running = false;
}

void BgLayerController::initBgLayerWithDefault() {
    
    bg_action_is_running = false;
    
    if (bg_spr1 != NULL) {
        bg_spr1->removeFromParent();
        bg_spr1 = NULL;
    }
    if (bg_spr2 != NULL) {
        bg_spr2->removeFromParent();
        bg_spr2 = NULL;
    }
    
    bg_spr1 = Sprite::create("bg.png");
    bg_spr1->setAnchorPoint(Point(0.0, 0.0));
    bg_spr1->setPosition(Point(0.0, 0.0));
    bg_layer->addChild(bg_spr1);
    
    bg_spr2 = Sprite::create("bg.png");
    bg_spr2->setAnchorPoint(Point(0.0, 0.0));
    bg_spr2->setPosition(Point(0.0, bg_spr1->getBoundingBox().size.height));
    bg_layer->addChild(bg_spr2);
}

void BgLayerController::attachBgLayerTo(Layer* _layer, int zOrder) {
    
    _layer->addChild(bg_layer, zOrder);
}

void BgLayerController::runBgActions() {
    
    if (bg_action_is_running == true) {
        return ;
    }
    
    bg_action_is_running = true;
    
    float moving_distance = bg_spr1->getBoundingBox().size.height;
    float moving_time = moving_distance / BG_MOVING_SPEED;
    
    auto act1 = MoveBy::create(moving_time, Point(0.0, -moving_distance));
    auto act1_2 = CallFuncN::create(CC_CALLBACK_1(BgLayerController::bgActions_callback, this));
    auto act1_3 = Sequence::create(act1, act1_2, NULL);
    auto act1_4 = RepeatForever::create(act1_3);
    bg_spr1->runAction(act1_4);
    
    auto act2 = MoveBy::create(moving_time, Point(0.0, -moving_distance));
    auto act2_2 = CallFuncN::create(CC_CALLBACK_1(BgLayerController::bgActions_callback, this));
    auto act2_3 = Sequence::create(act2, act2_2, NULL);
    auto act2_4 = RepeatForever::create(act2_3);
    bg_spr2->runAction(act2_4);
}

void BgLayerController::bgActions_callback(Ref* _bg_spr) {
    
    Sprite *bg_spr = (Sprite*)_bg_spr;
    
    if (bg_spr->getPositionY() < 0.0) {
        bg_spr->setPosition(Point(0.0, bg_spr->getBoundingBox().size.height));
    }
    else {
        bg_spr->setPosition(Point::ZERO);
    }
}

void BgLayerController::release() {
    
    this->~BgLayerController();
}

BgLayerController::~BgLayerController() {
    
}