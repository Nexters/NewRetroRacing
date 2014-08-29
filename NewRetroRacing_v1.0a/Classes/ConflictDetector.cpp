#include "ConflictDetector.h"

USING_NS_CC;
using namespace std;

ConflictDetector* ConflictDetector::create
(GameState *gs, RoadController* rc, Spaceship* ss, RObjectController *roc) {
    
    if (gs == NULL || rc == NULL || ss == NULL || roc == NULL)
        return NULL;
    
    return new ConflictDetector(gs, rc, ss, roc);
}

bool ConflictDetector::handleConflict() {
    
    //CCLOG("a flag %d", handle_flag);
    
    if (handle_flag)
        return false;
    
    //CCLOG("b flag %d", handle_flag);
    
    handle_flag = true;
    
    Rect ship_rect = _ship->getRect();
    
    // road controller check
    Vector<Sprite*> *hori_rails = _road_cont->getHorizontalRails();
    for (vector<Sprite*>::iterator it = hori_rails->begin(); it != hori_rails->end(); ++it) {
		Sprite *hori_rail = (Sprite*)*it;
		if (ship_rect.intersectsRect(hori_rail->getBoundingBox())) {
            hori_rail->getBoundingBox();
            //_handleHorizontalRail(hori_rail);
            return true;
        }
	}
    
    // robject controller check
    vector<RObjectSet*> *robj_set_list = _robj_cont->getRObjectSetList();
    for (vector<RObjectSet*>::iterator it = robj_set_list->begin(); it != robj_set_list->end(); ++it) {
        RObjectSet* robj_set = (RObjectSet*)*it;
        float ratio = 2.0 / _road_cont->getCurrentLaneCount();
        vector<RObject*>* robj_list = robj_set->getRObjectList();
        Point basic_p = robj_set->getPosition();
        for (vector<RObject*>::iterator in_it = robj_list->begin(); in_it != robj_list->end(); ++in_it) {
            RObject* robj = (RObject*)*in_it;
            Rect tmp_rect = robj->getBoundingBox();
            float diff_x = (tmp_rect.size.width - tmp_rect.size.width * ratio) / 2;
            float diff_y = (tmp_rect.size.height - tmp_rect.size.height * ratio) / 2;
            Size robj_size = tmp_rect.size * ratio;
            tmp_rect.setRect(tmp_rect.getMinX() + diff_x, tmp_rect.getMinY() + diff_y,
                             robj_size.width, robj_size.height);
            Rect robj_rect = Rect(basic_p.x + tmp_rect.getMinX(),
                                  basic_p.y + tmp_rect.getMinY(),
                                  basic_p.x + tmp_rect.getMaxX(),
                                  basic_p.y + tmp_rect.getMaxY());
            if (ship_rect.intersectsRect(robj_rect)) {
                _handleRObject(robj_set, robj);
                handle_flag = false;
                return true;
            }
        } // 무한 루프??????????????
    }
    
    handle_flag = false;
    
    return false;
}

void ConflictDetector::_handleHorizontalRail(Sprite* hori_rail) {
    
    //CCLOG("hori rail conflict");
}
void ConflictDetector::_handleRObject(RObjectSet* set, RObject* robj) {
   
    if (robj->getRObjectType() == robj_obstacle) {
        CCLOG("obstacle conflict");
    }
    else if (robj->getRObjectType() == robj_coin) {
        CCLOG("coin conflict");
    }
    set->removeRObject(robj);
}

ConflictDetector::ConflictDetector
(GameState *gs, RoadController* rc, Spaceship* ss, RObjectController* roc)
: _gameState(gs), _road_cont(rc), _ship(ss), _robj_cont(roc) {

    handle_flag = false;
}

