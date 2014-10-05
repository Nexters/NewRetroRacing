#ifndef _CONFLICT_DETECTOR_H_
#define _CONFLICT_DETECTOR_H_

#include "RoadController.h"
#include "Spaceship.h"
#include "RObjectController.h"
#include "GameState.h"
#include "Shared.h"

class ConflictDetector {
  
public:
    static ConflictDetector* create(
            GameState *gs, RoadController* rc, Spaceship* ss, RObjectController *roc);
    bool handleConflict();
    
private:
    ConflictDetector(GameState *gs, RoadController* rc, Spaceship* ss, RObjectController* roc);
    
    void _handleRObject(RObjectSet* set, RObject* robj);
    void _handleHorizontalRail(Vector<Sprite*>* hori_rails, Sprite* hori_rail);
    
private:
    GameState *_gameState;
    RoadController *_road_cont;
    Spaceship *_ship;
    RObjectController *_robj_cont;
    
    bool handle_flag;
};

#endif
