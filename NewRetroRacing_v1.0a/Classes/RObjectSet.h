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
    friend class RObjIterator;
    
private:
    RObjectType robj_type;
    RObject *next_robj;
};

/* ***** ***** ***** ***** ***** ***** ***** ***** ***** *****
                            RObjectSet
   ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */

//class RObjIterator {
//    
//public:
//    RObjIterator(RObject* _robj = 0) : _it(_robj) {}
//    RObjIterator& operator=(const RObjIterator _another) {
//        _it = _another._it;
//        return *this;
//    }
//    RObjIterator& operator++() {
//        _it = _it->next_robj;
//        return *this;
//    }
//    RObject* operator*()
//    {
//        return _it;
//    }
//    bool operator==(const RObjIterator _another)
//    {
//        return (_it == _another._it);
//    }
//    bool operator!=(const RObjIterator _another)
//    {
//        return (_it != _another._it);
//    }
//
//private:
//    RObject* _it;
//};

class RObjectSet {
    
public:
    static RObjectSet* generateRObjectSet(RObjectSetType _type);

    void locateRObjectSet(Vec2 _point, float scale_ratio);
    void attachToLayer(Layer* _layer, int zOrder);
    void moveDownRObjectSet();
    void release();
    Vec2 getPosition() { return robj_bg->getPosition(); }
    void setLaneNumber(int num) { lane_num = num; }
    int getLaneNumber() { return lane_num; }
    
    std::vector<RObject*>* getRObjectList() { return robj_list; }
    
    void relocateRObjectSet(Vec2 _point, float scale_ratio, bool* _flag);
    
    void removeRObject(RObject* robj);

public:
    //RObjIterator begin() { return RObjIterator(robj_list); }
    //RObjIterator end() { return RObjIterator(robj_end); }
    
private:
    void _generateRObjectSet(RObjectSetType _type);
        void _generate_setType1();

    void _relocateRObjectSet_callback(Ref* _robj, void* _flag);
    
private:
    RObjectSet();
    ~RObjectSet();
    
public:
    //friend class RObjIterator;
    //typedef RObjIterator iterator;
    
private:
    Sprite *robj_bg;
    std::vector<RObject*>* robj_list;
    //RObject *robj_list;
    //RObject *robj_end;
    int lane_num;
};

#endif
