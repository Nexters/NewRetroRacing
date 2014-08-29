#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Shared.h"
#include "RoadController.h"
#include "BgLayerController.h"
#include "Spaceship.h"
#include "RObjectController.h"
#include "GameState.h"
#include "ConflictDetector.h"

class GameScene : public cocos2d::Layer, public GameState
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void gameOver();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    void initGameSceneData();
    void gameOver(float delta);
    
    void updateElpasedTime(float delta);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void update(float dt);
    
    /* for test */
    void attachTestButtons();
    bool buttonTouched(Touch *touch);
    /* ******** */
    
private:
    BgLayerController *bg_cont;
    RoadController *road_cont;
    Spaceship *s;
    RObjectController *robj_cont;
    ConflictDetector *detector;
    
    Label* speed_label;
    
    bool isTouchDown;
    float initTouchPos[2];
	float currTouchPos[2];
};

#endif // __GAME_SCENE_H__
