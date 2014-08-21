#ifndef __RoadChangeObserver__
#define __RoadChangeObserver__

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
    no_type,
    spaceship_type,
    obstacle_type,
    item_type,
} ObserverType;

class RoadChangeObserver {

public:
    virtual void onLaneIncrement(int how_many, int to_where) = 0;
    virtual void onLaneDecrement(int how_many, int from_where) = 0;
    virtual void onVerticalRangeChange(Vec2 range) = 0;
    ObserverType getObserverType() { return o_type; }
    
protected:
    void setObserverType(ObserverType _type) { o_type = _type; }
    
protected:
    ObserverType o_type;
};

#endif
