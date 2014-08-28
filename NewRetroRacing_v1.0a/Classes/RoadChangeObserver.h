#ifndef __RoadChangeObserver__
#define __RoadChangeObserver__

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
    no_type,
    spaceship_type,
    robj_type,
} ObserverType;

class RoadChangeObserver {

public:
    virtual void onLaneChange(int current, int next, int to_where) = 0;
    virtual void onVerticalRangeChange(Vec2 range) = 0;
    ObserverType getObserverType() { return o_type; }
    
protected:
    void setObserverType(ObserverType _type) { o_type = _type; }
    
protected:
    ObserverType o_type;
};

#endif
