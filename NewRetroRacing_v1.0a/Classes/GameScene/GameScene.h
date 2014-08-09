#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#define TAG_SPRITE_COIN 1002
#define TAG_LABEL_COIN   3


#include "cocos2d.h"
#include "car.h"
#include "Obstacles.h"
#include "BackgroundLayer.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void makeObstacles(float delta);
	void initLabel();

	void initData();
	void setLabelCoin();

	Size visibleSize;
	int coin;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	bool isTouchDown;

	float initTouchPos[2];
	float currTouchPos[2];

	car* playerCar;
	Obstacles *obstacles;

	void gameOver(float delta);

	void update(float dt);
};

#endif // __GAME_SCENE_H__
