#ifndef ROADCONTROLLER_H_
#define ROADCONTROLLER_H_

#include "cocos2d.h"
#include "Spaceship.h"

USING_NS_CC;

class RoadController {

public:
	RoadController();
	~RoadController();

	void release();
	void attachRoadLayerTo(Layer* _layer, int zOrder);

	bool attachLane(int how_many, int to_where);
	bool detachLane(int how_many, int from_where);

private:
	void addRailTo(Sprite* road, int _num_lane);
    void pauseRailActionsOfNextRoad(Sprite* n_road);
	void pauseRailActionsOfCurrentRoad(Sprite* c_road, float resizing_ratio);
	void resumeRailActionsOf(Sprite* road);
	void __attachLane(int how_many, int to_where);
	void __detachLane(int how_many, int from_where);
	void removeCurrentRoad_callback();
	void removeCurrentRoad_callback_d(Ref* sender, void* d);
	void makeNewRoad_callback();
	void railAction_callback(Ref* _rail_spr, Ref* _road);
	void addHorizontalRailTo(Sprite* road, int _num_lane, int lane_num);
	void removeHorizontalRail();

private:
	Layer *road_layer;		// Road를 대표하는 layer. 이 layer 위에 각 node들이 존재한다.
	Sprite *cur_road;		// 현재 화면 상에 나타나는 road sprite(사실상 불투명 직사각형 영). 이 sprite 위에 rail sprite들이 붙여지고 action이 가해진다.
	Sprite *next_road;		// road의 lane 갯수가 달라질 때, 화면 위에서 내려오는 다음 road sprite.
	Vector<Sprite*> *hori_rails;
    
	int num_lane;			// the number of lanes
	bool change_running;	// Locking variable for Actions(changing the number of lanes)

};

#endif /* ROADCONTROLLER_H_ */
