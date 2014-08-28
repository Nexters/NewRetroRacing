#ifndef _ROBJECT_CONTROLLER_H_
#define _ROBJECT_CONTROLLER_H_

#include "cocos2d.h"
#include "RoadChangeObserver.h"
#include "RObjectSet.h"


USING_NS_CC;
using namespace std;

class RObjectController : public RoadChangeObserver {
    
public:
    RObjectController(int lane_cnt = 2);
    void attachRObjectsTo(Layer *_layer, int _zOrder);
    
    void startGeneratingRObjects();
    void stopGeneratingRObjects();
    
    vector<RObjectSet*>* getRObjectSetList() { return robj_set_list; }
    
    void release();
    
public:
    virtual void onLaneChange(int current, int next, int to_where);
    virtual void onVerticalRangeChange(Vec2 range);
    
private:
    void generateRObjects(float dt);
    void _generateRObjects(int lane_num);
    
    void relocateRObects(int lane_change, int where, bool* _flag);
    
    int generateRandomNumber(unsigned int max);
    
private:
    ~RObjectController();
    
private:
    Layer *parent_layer;
    int zOrder;
    
    vector<RObjectSet*> *robj_set_list;
    
    int lane_cnt;
    Vec2 v_range;
    
    bool start_gen_flag;
    bool is_relocating;
    int sche_cnt;
};

#endif