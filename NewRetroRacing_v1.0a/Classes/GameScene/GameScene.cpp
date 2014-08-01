#include "GameScene/GameScene.h"
#include "GameScene/BackgroundLayer.h"

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



    return true;
}
