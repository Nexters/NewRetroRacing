#include "ConflictDetector.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

ConflictDetector* ConflictDetector::create
(GameState *gs, RoadController* rc, Spaceship* ss, RObjectController *roc) {
    
    if (gs == NULL || rc == NULL || ss == NULL || roc == NULL)
        return NULL;
    
    return new ConflictDetector(gs, rc, ss, roc);
}

bool ConflictDetector::handleConflict() {
    
    if (handle_flag)
        return false;
    
    //handle_flag = true;
    
    Rect ship_rect = _ship->getRect();
    
    // road controller check
    Vector<Sprite*> *hori_rails = _road_cont->getHorizontalRails();
    for (vector<Sprite*>::iterator it = hori_rails->begin(); it != hori_rails->end(); ++it) {
		Sprite *hori_rail = (Sprite*)*it;
        Sprite *road = (Sprite*)hori_rail->getParent();
        Rect tmp_rect = hori_rail->getBoundingBox();
        Rect road_rect = Rect::ZERO;
        if (road != NULL)
            road_rect = road->getBoundingBox();
        
        float ratio = 2.0 / _road_cont->getCurrentLaneCount();
        Point basic_p = Point(road_rect.getMinX(), road_rect.getMinY());
        
        Rect hori_rail_rect = Rect::ZERO;
        
        if (tmp_rect.origin.y > GAME_SCENE_HEIGHT) {
            hori_rail_rect =
            Rect(basic_p.x + tmp_rect.origin.x + ((tmp_rect.size.width/2) * (1-ratio)),
                 basic_p.y + tmp_rect.origin.y + ((tmp_rect.size.height/2) * (1-ratio)),
                 tmp_rect.size.width * ratio,
                 tmp_rect.size.height * ratio);
        }
        else {
        }
//        
//        CCLOG("hori rail %f %f %f %f",
//              hori_rail_rect.getMinX(), hori_rail_rect.getMaxX(),
//              hori_rail_rect.getMinY(), hori_rail_rect.getMaxY()
//              );
		if (ship_rect.intersectsRect(hori_rail_rect)) {
            
            _handleHorizontalRail(hori_rails, hori_rail);
            return true;
        }
	}
    
    //CCLOG("ship %f %f", ship_rect.getMinX(), ship_rect.getMaxX());
    
    // robject controller check
    vector<RObjectSet*> *robj_set_list = _robj_cont->getRObjectSetList();
    for (vector<RObjectSet*>::iterator it = robj_set_list->begin(); it != robj_set_list->end(); ++it) {
        RObjectSet* robj_set = (RObjectSet*)*it;
        float ratio = 2.0 / _road_cont->getCurrentLaneCount();
        vector<RObject*>* robj_list = robj_set->getRObjectList();
        Point basic_p = Point(robj_set->getPosition().x-100, robj_set->getPosition().y-100*ratio);
        
        for (vector<RObject*>::iterator in_it = robj_list->begin(); in_it != robj_list->end(); ++in_it) {
            RObject* robj = (RObject*)*in_it;
            Rect tmp_rect = robj->getBoundingBox();
            
            Rect robj_rect =
                Rect(basic_p.x + tmp_rect.origin.x*ratio + ((tmp_rect.size.width/2) * (1-ratio)),
                    basic_p.y + tmp_rect.origin.y*ratio + ((tmp_rect.size.height/2) * (1-ratio)),
                    tmp_rect.size.width * ratio,
                    tmp_rect.size.height * ratio);
            if (robj->getRObjectType() == robj_obstacle) {
                //CCLOG("robj %f %f h %f", robj_rect.getMinX(), robj_rect.getMaxX(), robj_rect.getMinY());
            }
            if (ship_rect.intersectsRect(robj_rect)) {
                _handleRObject(robj_set, robj);
                
                return true;
            }
        } // 무한 루프??????????????
    }
    
    handle_flag = false;
    
    return false;
}

void ConflictDetector::_handleHorizontalRail(Vector<Sprite*>* hori_rails, Sprite* hori_rail) {
    
    CCLOG("hori rail conflict");
    Rect ship_rect = _ship->getRect();
    
//    CCLOG("shipship %f %f %f %f", ship_rect.getMinX(), ship_rect.getMaxX(), ship_rect.getMinY(), ship_rect.getMaxY());
    
    ssize_t index = hori_rails->getIndex(hori_rail);
    hori_rails->erase(index);
    
    SimpleAudioEngine::getInstance()->playEffect("bomb.wav", false);
    _gameState->gameOver();
    handle_flag = false;
}
void ConflictDetector::_handleRObject(RObjectSet* set, RObject* robj) {
   
    if (robj->getRObjectType() == robj_obstacle) {
        //CCLOG("obstacle conflict");
        SimpleAudioEngine::getInstance()->playEffect("bomb.wav", false);
        _gameState->gameOver();
    }
    else if (robj->getRObjectType() == robj_coin) {
        //CCLOG("coin conflict");
        SimpleAudioEngine::getInstance()->playEffect("coinGet.wav", false);
		Shared::getInstance()->setCoinData(1);
    }
    set->removeRObject(robj);
    handle_flag = false;
}

ConflictDetector::ConflictDetector
(GameState *gs, RoadController* rc, Spaceship* ss, RObjectController* roc)
: _gameState(gs), _road_cont(rc), _ship(ss), _robj_cont(roc) {

    handle_flag = false;
}

