#include "GameScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;

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

    auto bg_layer = BackgroundLayer::createBGLayer();
    this->addChild(bg_layer);

    return true;
}
