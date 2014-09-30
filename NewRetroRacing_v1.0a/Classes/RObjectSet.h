#ifndef _ROBJECT_SET_H_
#define _ROBJECT_SET_H_

#include "cocos2d.h"

#define OBS_CNT 6
#define TYPE_CNT 1

USING_NS_CC;

typedef enum {
    robj_obstacle,
    robj_coin,
    robj_item,
    robj_notype,
} RObjectType;

typedef enum {
    img_alien,
    img_android,
    img_meteor,
    img_moon,
    img_planet,
    img_satellite,
    img_coin,
} RObjectImage;

typedef enum {
    robj_set1,
} RObjectSetType;

/* ***** ***** ***** ***** ***** ***** ***** ***** ***** *****
                            RObject
   ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */

class RObjIterator;

class RObject : public Sprite {
    
public:
    
    static RObject* createRObject(RObjectType _type, RObjectImage _image);
    RObjectType getRObjectType() { return robj_type; }
    
public:
    friend class RObjectSet;
    
private:
    RObjectType robj_type;
};

class RObjectSet {
    
public:
    static RObjectSet* generateRObjectSet(RObjectSetType _type);
    void releaseRObjectSet();

    void locateRObjectSet(Vec2 _point, float scale_ratio);
    void attachToLayer(Layer* _layer, int zOrder);
    void moveDownRObjectSet();
    Vec2 getPosition() { return robj_bg->getPosition(); }
    void setLaneNumber(int num) { lane_num = num; }
    int getLaneNumber() { return lane_num; }
    
    std::vector<RObject*>* getRObjectList() { return robj_list; }
    void relocateRObjectSet(Vec2 _point, float scale_ratio, bool* _flag);
    void removeRObject(RObject* robj);
    
private:
    void _generateRObjectSet(RObjectSetType _type);
        void _generate_setType1();

    void _relocateRObjectSet_callback(Ref* _robj, void* _flag);
    
private:
    RObjectSet();
    ~RObjectSet();
    
private:
    Sprite *robj_bg;
    std::vector<RObject*>* robj_list;
    int lane_num;
};

#endif
