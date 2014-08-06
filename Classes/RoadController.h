#ifndef ROADCONTROLLER_H_
#define ROADCONTROLLER_H_

#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class RoadController {

public:
	RoadController();
	virtual ~RoadController();

	void release();
	void attachRoadLayerTo(cocos2d::Layer* _layer);

	bool attachLane(int to_where);
	bool detachLane(int from_where);

private:
	void addRailTo(Sprite* road);
	void addRail_callback(Ref *spr);
	void stopRailActionOf(Sprite* road);
	bool __attachLane(int to_where);
	bool __detachLane(int from_where);
	void removeCurrentRoad_callback();
	void makeNewRoad_callback();

private:
	Layer *road_layer;
	Sprite *cur_road;
	Sprite *next_road;
	int lane_cnt;
	Vec2 hor_range;		// Horizontal range
	float lane_width;
	bool act_is_running;	// Action Locking variable
};

#endif /* ROADCONTROLLER_H_ */
