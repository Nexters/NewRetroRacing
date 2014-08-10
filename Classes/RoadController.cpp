#include "RoadController.h"
#include "Shared.h"

float road_size_change_time = 0.2;

RoadController::RoadController() {

	road_layer = cocos2d::Layer::create();

	num_lane = 2;		// 초기 lane 갯수는 2

	// current road sprite setting
	cur_road = cocos2d::Sprite::create("road.png");
	cur_road->setAnchorPoint(Point(0.5, 0.0));
	cur_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, 0.0));
	road_layer->addChild(cur_road);
	addRailTo(cur_road, num_lane);	// add rail sprites to current road sprite

	// next road sprite setting
	next_road = cocos2d::Sprite::create("road.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, cur_road->getContentSize().height));
	road_layer->addChild(next_road);

	// calculate horizontal range & lane width
	Rect road_rect = cur_road->getBoundingBox();
	hor_range = Vec2(road_rect.getMinX(), road_rect.getMaxX());
	lane_width = (road_rect.getMaxX() - road_rect.getMinX()) / 2; // 이 값을 어떻게 사용해야할까?

	change_running = false;

	//this->road_layer->scheduleUpdate();
}

void RoadController::attachRoadLayerTo(Layer* _layer, int zOrder) {

	try {
		if (road_layer == NULL) {
			throw 1;
		}
		_layer->addChild(road_layer, zOrder);
	}
	catch (int e) {
		CCLOG("RoadController::attachRoadLayerTo(Layer* _layer) Exception: %d", e);
		return;
	}
}

bool RoadController::attachLane(int how_many, int to_where) {

	if (change_running)
		return false;

	if (num_lane + how_many > 4) {	// The number of lanes should be smaller than 5.
		CCLOG("RoadController::attachLane(int how_many, int to_where) Exception: how_many(%d) err, current number of lanes(%d)",
				how_many, num_lane);
		return false;
	}

	if (how_many == 1) {		// when attach 1 lane.
		switch(to_where) {
		case 1:
		case 2:
			__attachLane(how_many, to_where);
			return true;
		default:
			CCLOG("RoadController::attachLane(int how_many, int to_where) Exception: to_where(%d) err, how_many(%d)",
					to_where, how_many);
			return false;
		}
	}
	else if (how_many == 2) {	// when attach 2 lanes.
		switch (to_where) {
		case 1:
		case 2:
		case 3:
			__attachLane(how_many, to_where);
			return true;
		default:
			CCLOG("RoadController::attachLane(int how_many, int to_where) Exception: to_where(%d) err, how_many(%d)",
					to_where, how_many);
			return false;
		}
	}
	else {
		CCLOG("RoadController::attachLane(int how_many, int to_where) Exception: how_many(%d) err", how_many);
		return false;
	}
}

bool RoadController::detachLane(int how_many, int from_where) {

	if (change_running)
		return false;

	if (num_lane - how_many < 2) {	// The number of lanes should be smaller than 5.
		CCLOG("RoadController::detachLane(int how_many, int to_where) Exception: how_many(%d) err, current number of lanes(%d)",
				how_many, num_lane);
		return false;
	}

	if (how_many == 1) {		// when attach 1 lane.
		switch(from_where) {
		case 1:
		case 2:
			__detachLane(how_many, from_where);
			return true;
		default:
			CCLOG("RoadController::detachLane(int how_many, int to_where) Exception: to_where(%d) err, how_many(%d)",
					from_where, how_many);
			return false;
		}
	}
	else if (how_many == 2) {	// when attach 2 lanes.
		switch (from_where) {
		case 1:
		case 2:
		case 3:
			__detachLane(how_many, from_where);
			return true;
		default:
			CCLOG("RoadController::detachLane(int how_many, int to_where) Exception: to_where(%d) err, how_many(%d)",
					from_where, how_many);
			return false;
		}
	}
	else {
		CCLOG("RoadController::detachLane(int how_many, int to_where) Exception: how_many(%d) err", how_many);
		return false;
	}
}

void RoadController::__attachLane(int how_many, int to_where) {

	change_running = true;	// __attachLane & __detachLane function is locked
	pauseRailActionsOf(cur_road); 	// Actions of rail sprites on road sprite should be paused

	float cur_road_height = cur_road->getBoundingBox().getMaxY() - cur_road->getBoundingBox().getMinY();
	float moving_speed = getCurrentSpeed(ELAPSED_TIME);
	float resizing_ratio = 1.0;

	// calculate resizing ratio of current road sprite & add rail sprites to next road sprite.
	/*
	if (how_many == 1) {	// when you attach one lane
		resizing_ratio = (float)num_lane / (num_lane + 1);
		addRailTo(next_road, num_lane + 1);
		pauseRailActionsOf(next_road);	// Because addRailTo function start actions of rail sprites,
	}									// you should pause the actions until process of attachLanes is over.
	else if (how_many == 2) {	// when you attach two lanes
		resizing_ratio = (float)num_lane / (num_lane + 2);
		addRailTo(next_road, num_lane + 2);
		pauseRailActionsOf(next_road);
	}*/
	resizing_ratio = (float)num_lane / (num_lane + how_many);
	addRailTo(next_road, num_lane + how_many);
	pauseRailActionsOf(next_road);	// Because addRailTo function start actions of rail sprites,
									// you should pause the actions until process of attachLanes is over.

	// set basic values for attaching Lane(s)
	if (to_where == 1) {
		cur_road->setAnchorPoint(Point(1.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMaxX(), 0.0));
	}
	else if (to_where == 2) {
		cur_road->setAnchorPoint(Point(0.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMinX(), 0.0));
	}
	else if (to_where == 3) {
		cur_road->setAnchorPoint(Point(0.5, 0.0));
		cur_road->setPosition(
				Point((next_road->getBoundingBox().getMinX() + next_road->getBoundingBox().getMaxX()) / 2.0, 0.0)
				);
	}
	float act2_moving_distance = (cur_road_height * (1 - resizing_ratio));
	float act2_moving_time = act2_moving_distance / moving_speed;

	// start actions
	//auto act1 = ScaleBy::create(act2_moving_time, resizing_ratio);
	auto act1 = ScaleBy::create(road_size_change_time, resizing_ratio);
	cur_road->runAction(act1);

	//auto act2 = MoveBy::create(act2_moving_time,
	//						Point(0.0, -act2_moving_distance));
	auto act2 = MoveBy::create(road_size_change_time,
								Point(0.0, -act2_moving_distance));
	auto act2_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::removeCurrentRoad_callback, this));
	auto act2_3 = Sequence::create(act2, act2_2, NULL);				// RoadController::removeCurrentRoad_callback
	next_road->runAction(act2_3);

	num_lane += how_many;
}

void RoadController::removeCurrentRoad_callback() {

	float moving_speed = getCurrentSpeed(ELAPSED_TIME);
	float cur_road_height = cur_road->getBoundingBox().getMaxY() - cur_road->getBoundingBox().getMinY();

	float act3_moving_distance = cur_road_height;
	float act3_moving_time = act3_moving_distance / moving_speed;

	auto act3 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	cur_road->runAction(act3);

	auto act4 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	auto act4_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::makeNewRoad_callback, this));
	auto act4_3 = Sequence::create(act4, act4_2, NULL);				// RoadController::makeNewRoad_callback
	next_road->runAction(act4_3);
}

void RoadController::__detachLane(int how_many, int from_where) {

	change_running = true;	// __attachLane & __detachLane function is locked
	pauseRailActionsOf(cur_road); 	// Actions of rail sprites on road sprite should be paused

	float next_road_height = next_road->getBoundingBox().getMaxY() - next_road->getBoundingBox().getMinY();
	float moving_speed = getCurrentSpeed(ELAPSED_TIME);
	float resizing_ratio = 1.0;

	resizing_ratio = (float)num_lane / (num_lane - how_many);
	addRailTo(next_road, num_lane - how_many);
	pauseRailActionsOf(next_road);

	if (from_where == 1) {
		next_road->setAnchorPoint(Point(1.0, 0.0));
		next_road->setPosition(
			Point(cur_road->getBoundingBox().getMaxX(), cur_road->getBoundingBox().getMaxY()));
	}
	else if (from_where == 2) {
		next_road->setAnchorPoint(Point(0.0, 0.0));
		next_road->setPosition(
			Point(cur_road->getBoundingBox().getMinX(), cur_road->getBoundingBox().getMaxY()));
	}
	else if (from_where == 3) {
		next_road->setAnchorPoint(Point(0.5, 0.0));
		next_road->setPosition(
				Point((cur_road->getBoundingBox().getMinX() + cur_road->getBoundingBox().getMaxX()) / 2.0,
						cur_road->getBoundingBox().getMaxY()));
	}
	next_road->setScale(1 / resizing_ratio);

	float act2_moving_distance = next_road_height * (1 / resizing_ratio);
	float act2_moving_time = act2_moving_distance / moving_speed;

	// start actions
	auto act1 = MoveBy::create(act2_moving_time,
							Point(0.0, -act2_moving_distance));
	next_road->runAction(act1);

	auto act2 = MoveBy::create(act2_moving_time,
							Point(0.0, -act2_moving_distance));
	auto act2_2 = CallFuncN::create(
			CC_CALLBACK_1(RoadController::removeCurrentRoad_callback_d, this, (void*)new float(resizing_ratio))
			);							// RoadController::removeCurrentRoad_callback_d(Ref *sender, void *d)
	auto act2_3 = Sequence::create(act2, act2_2, NULL);
	cur_road->runAction(act2_3);

	num_lane -= how_many;
}

void RoadController::removeCurrentRoad_callback_d(Ref *sender, void *d) {

	float moving_speed = getCurrentSpeed(ELAPSED_TIME);
	float resizing_ratio = *(float*)d;
	float next_road_height = next_road->getBoundingBox().getMaxY() - next_road->getBoundingBox().getMinY();
	float act2_moving_distance = next_road_height * resizing_ratio - next_road_height;
			//(next_road_height * (1 - (1 / resizing_ratio)));
	float act2_moving_time = act2_moving_distance / moving_speed;

	if (next_road->getAnchorPoint().x == 0.0) {
		next_road->setPosition(
			Point(next_road->getBoundingBox().getMinX(),
					next_road->getBoundingBox().getMaxY()));
	}
	else if (next_road->getAnchorPoint().x == 1.0) {
		next_road->setPosition(
			Point(next_road->getBoundingBox().getMaxX(),
					next_road->getBoundingBox().getMaxY()));
	}
	else if (next_road->getAnchorPoint().x == 0.5) {
		next_road->setPosition(
			Point((next_road->getBoundingBox().getMinX() + next_road->getBoundingBox().getMaxX()) / 2.0,
					next_road->getBoundingBox().getMaxY()));
	}
	else
		return;

	next_road->setAnchorPoint(Point(next_road->getAnchorPoint().x, 1.0));

	//auto act1 = ScaleBy::create(act2_moving_time, resizing_ratio);
	auto act1 = ScaleBy::create(road_size_change_time, resizing_ratio);
	next_road->runAction(act1);

	//auto act2 = MoveBy::create(act2_moving_time,
	//						Point(0.0, -act2_moving_distance));
	auto act2 = MoveBy::create(road_size_change_time,
								Point(0.0, -act2_moving_distance));
	auto act2_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::makeNewRoad_callback, this));
	auto act2_3 = Sequence::create(act2, act2_2, NULL);				// RoadController::removeCurrentRoad_callback
	cur_road->runAction(act2_3);
}

void RoadController::makeNewRoad_callback() {

	cur_road->removeFromParent();
	cur_road = next_road;
	resumeRailActionsOf(cur_road);

	next_road = cocos2d::Sprite::create("road.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, cur_road->getContentSize().height));
	road_layer->addChild(next_road);

	change_running = false;	// __attachLane & __detachLane function is unlocked
}

void RoadController::addRailTo(Sprite* road, int _num_lane) {

	String *img_file_name = new String("");
	float size_ratio = 1.0;

	switch (_num_lane) {
	case 2:
		img_file_name->append("rail_2.png");
		break;
	case 3:
		img_file_name->append("rail_3.png");
		size_ratio *= 2.0/3;
		break;
	case 4:
		img_file_name->append("rail_4.png");
		size_ratio *= 2.0/4;
		break;
	default:
		CCLOG("Variable _num_lane is invalid.");
		return;
	}

	float rail_height = Sprite::create("rail_2.png")->getContentSize().height;
	rail_height *= size_ratio;

	for (float height_sum = 0.0; height_sum < (GAME_SCENE_HEIGHT + rail_height); height_sum += rail_height) {
		Sprite *rail_spr = Sprite::create(img_file_name->getCString());
		rail_spr->setAnchorPoint(Point::ZERO);
		rail_spr->setPosition(Point(0.0, height_sum));
		rail_spr->setScale(size_ratio);
		road->addChild(rail_spr);
		railAction_callback(rail_spr);
	}
}

void RoadController::pauseRailActionsOf(Sprite* road) {

	Vector<Node*> rail_imgs = road->getChildren();
	for (std::vector<Node*>::iterator it = rail_imgs.begin(); it != rail_imgs.end(); ++it) {
		Sprite *rail_spr = (Sprite*)*it;
		rail_spr->pauseSchedulerAndActions();
		if (road == cur_road && rail_spr->getBoundingBox().getMinY() >= road->getBoundingBox().getMaxY()) {
			//rail_spr->setVisible(false);
			rail_spr->removeFromParent();
		}
		else if (road == cur_road &&
				rail_spr->getBoundingBox().getMinY() <= road->getBoundingBox().getMaxY() &&
				rail_spr->getBoundingBox().getMaxY() >= road->getBoundingBox().getMaxY()) {

			rail_spr->setTextureRect(
					Rect(0, 0,
							rail_spr->getContentSize().width,
							road->getBoundingBox().getMaxY() - rail_spr->getBoundingBox().getMinY()));

			//rail_spr->removeFromParent();
		}
	}
}

void RoadController::resumeRailActionsOf(Sprite* road) {

	Vector<Node*> rail_imgs = road->getChildren();
	for (std::vector<Node*>::iterator it = rail_imgs.begin(); it != rail_imgs.end(); ++it) {
		Sprite *rail_spr = (Sprite*)*it;
		rail_spr->resumeSchedulerAndActions();
	}
}

void RoadController::railAction_callback(Ref *_rail_spr) {

	Sprite *rail_spr = (Sprite*)_rail_spr;

	float rail_height = rail_spr->getBoundingBox().getMaxY() - rail_spr->getBoundingBox().getMinY();
	float moving_speed = getCurrentSpeed(ELAPSED_TIME);
	float moving_time = rail_height / moving_speed;

	if (rail_spr->getBoundingBox().getMaxY() <= 0.01) {
		int num_rail = ((GAME_SCENE_HEIGHT + rail_height) / rail_height) + 1;
		rail_spr->setPosition(Point(0.0, rail_height * (num_rail - 1)));
	}

	auto act1 = MoveBy::create(moving_time, Point(0.0, -rail_height));
	auto act2 = CallFuncN::create(CC_CALLBACK_1(RoadController::railAction_callback, this));
	auto act3 = Sequence::create(act1, act2, NULL);
	rail_spr->runAction(act3);
}

void RoadController::release() {

	this->~RoadController();
}

RoadController::~RoadController() {

}
