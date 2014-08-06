#ifndef ROADCONTROLLER_H_
#define ROADCONTROLLER_H_

#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class RoadController : cocos2d::Layer {

public:
	RoadController();
	virtual ~RoadController();

	void release();
	void attachRoadLayerTo(cocos2d::Layer* _layer);

	void attachLane(int to_where);
	void detachLane(int from_where);

private:
	bool __attachLane(int to_where);
	void removeCurrentRoad_callback(CCNode *spr_cur_road);
	void makeNewRoad_callback(CCNode *spr_cur_road);

private:
	Layer *road_layer;
	Sprite *cur_road;
	Sprite *next_road;
	int lane_cnt;
	Vec2 hor_range;		// Horizontal range
	float lane_width;
};

#endif /* ROADCONTROLLER_H_ */
