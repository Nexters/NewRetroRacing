#ifndef ROADCONTROLLER_H_
#define ROADCONTROLLER_H_

#include "cocos2d.h"
#include "RoadChangeObserver.h"

USING_NS_CC;
using namespace std;

class RoadController {

public:
	RoadController();
	void release();
    
	void attachRoadLayerTo(Layer* _layer, int zOrder);

	bool attachLane(int how_many, int to_where);
	bool detachLane(int how_many, int from_where);
    
    void addRoadChangeObserver(RoadChangeObserver *observer);
    void removeRoadChangeObserver(RoadChangeObserver *observer);

private:
    
    void __attachLane(int how_many, int to_where);
        void __attach_beforeScalingCurrentRoad(int how_many, int to_where, float resizing_ratio);
        void __attach_scaleCurrentRoad(float resizing_ratio);
            void __attach_moveRoadsAfterScaling();
                void __attach_makeNewRoadAfterMovingRoads();
    
    void __detachLane(int how_many, int from_where);
        void __detach_beforeMovingRoads(int how_many, int from_where, float resizing_ratio);
        void __detach_moveRoads(float resizing_ratio);
            void __detach_scaleNextRoadAfterMovingRoads(Ref* sender, void* ratio);
                void __detach_makeNewRoadAfterScalingNextRoad();
    
    void addRailTo(Sprite* road, int _num_lane);
    void railAction_callback(Ref* _rail_spr, Ref* _road);
    
    void pauseRailActionsOfNextRoad(Sprite* n_road);
	void pauseRailActionsOfCurrentRoad(Sprite* c_road, float resizing_ratio);
	void resumeRailActionsOf(Sprite* road);
    
	void addHorizontalRailTo(Sprite* road, int _num_lane, int lane_num);
	void removeHorizontalRail();
    
private:
    void notifyLaneIncrement();
    void notifyLaneDecrement();
    
private:
    void setChangeRunningFlag();
    void unsetChangeRunningFlag();
    bool getChangeRunningFlag();
    
private:
    ~RoadController();

private:
	Layer *road_layer;
	Sprite *cur_road;
	Sprite *next_road;
	Vector<Sprite*> *hori_rails;
    vector<RoadChangeObserver*> *observers;
    
	int lane_count;
	bool change_running;
    
private:
    int tmp_how_many;
    int tmp_where;
};

#endif
