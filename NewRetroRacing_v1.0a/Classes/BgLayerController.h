#ifndef _BGLAYERCONTROLLER_H_
#define _BGLAYERCONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class BgLayerController {
    
public:
    
    BgLayerController();
    void releaseBgLayerCont();
    
    void initBgLayerWithDefault();
    void attachBgLayerTo(Layer* _layer, int zOrder);
    void runBgActions();
    
    
private:
    void bgActions_callback(Ref* _bg_spr);
    ~BgLayerController();
    
private:
    Layer *bg_layer;
    Sprite *bg_spr1;
    Sprite *bg_spr2;
    bool bg_action_is_running;
};

#endif
