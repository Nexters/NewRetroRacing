#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "RoadController.h"

USING_NS_CC;

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void action_callback(Ref *spr);
    void update_time(float delta);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual bool onTouchBegan(Touch *touch, Event *event);

public:
    RoadController* road_cont;
};

#endif // __HELLOWORLD_SCENE_H__
