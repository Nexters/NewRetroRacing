#include "RoadController.h"

#define RAIL_SPR_1 21
#define RAIL_SPR_2 22

RoadController::RoadController() {

	road_layer = cocos2d::Layer::create();

	lane_cnt = 2;

	cur_road = cocos2d::Sprite::create("road.png");
	cur_road->setAnchorPoint(Point(0.5, 0.0));
	cur_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, 0.0));
	road_layer->addChild(cur_road);
	addRailTo(cur_road);

	next_road = cocos2d::Sprite::create("road.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, cur_road->getContentSize().height));
	road_layer->addChild(next_road);

	Rect road_rect = cur_road->getBoundingBox();

	hor_range = Vec2(road_rect.getMinX(), road_rect.getMaxX());
	lane_width = (road_rect.getMaxX() - road_rect.getMinX()) / 2;

	act_is_running = false;
}

void RoadController::attachRoadLayerTo(Layer* _layer) {

	try {
		if (road_layer == NULL) {
			throw 1;
		}
		_layer->addChild(road_layer);
	}
	catch (int e) {
		CCLOG("RoadController::attachRoadLayerTo(Layer* _layer) Exception: %d", e);
		return;
	}
}

bool RoadController::attachLane(int to_where) {

	try {
		switch (to_where) {
		case 1:		// 1: Attach lane to left side of road
		case 2:		// 2: Attach lane to right side of road
			if (act_is_running)
				throw -1;
			if (!__attachLane(to_where))
				throw to_where;
			break;
		default :
			throw 2;
			break;
		}
	}
	catch (int exc) {
		CCLOG("RoadController::attachLane(int to_where) Exception: %d", exc);
		return false;
	}
	return true;
}

bool RoadController::detachLane(int from_where) {

	try {
		switch (from_where) {
		case 1:		// 1: Detach lane from left side of road
		case 2:		// 2: Detach lane from right side of road
			if (act_is_running)
				throw -1;
			if (!__detachLane(from_where))
				throw from_where;
			break;
		default :
			throw 2;
			break;
		}
	}
	catch (int exc) {
		CCLOG("RoadController::detachLane(int from_where) Exception: %d", exc);
		return false;
	}
	return true;
}

bool RoadController::__attachLane(int to_where) {

	act_is_running = true;	// __attachLane & __detachLane function is locked

	if (lane_cnt > 4)
		return false;

	float cur_road_height = cur_road->getBoundingBox().getMaxY() - cur_road->getBoundingBox().getMinY();
	float resizing_ratio = (float)lane_cnt / (lane_cnt + 1);
	float moving_speed = CURRENT_SPEED_LEVEL * SPEED_CONSTANT;

	float act2_moving_distance = (cur_road_height * (1 - resizing_ratio));
	float act2_moving_time = act2_moving_distance / moving_speed;

	if (to_where == 1) {
		cur_road->setAnchorPoint(Point(1.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMaxX(), 0.0));
	}
	else if (to_where == 2) {
		cur_road->setAnchorPoint(Point(0.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMinX(), 0.0));
	}
	else
		return false;

	auto act1 = ScaleBy::create(act2_moving_time, resizing_ratio);
	cur_road->runAction(act1);
	stopRailActionOf(cur_road);

	cur_road->getChildByTag(RAIL_SPR_2)->stopAllActions();

	auto act2 = MoveBy::create(act2_moving_time,
							Point(0.0, -act2_moving_distance));
	auto act2_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::removeCurrentRoad_callback, this));
	auto act2_3 = Sequence::create(act2, act2_2, NULL);
	next_road->runAction(act2_3);

	return true;
}

void RoadController::removeCurrentRoad_callback() {

	float moving_speed = CURRENT_SPEED_LEVEL * SPEED_CONSTANT;
	float cur_road_height = cur_road->getBoundingBox().getMaxY() - cur_road->getBoundingBox().getMinY();

	float act3_moving_distance = cur_road_height;
	float act3_moving_time = act3_moving_distance / moving_speed;

	auto act3 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	cur_road->runAction(act3);

	auto act4 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	auto act4_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::makeNewRoad_callback, this));
	auto act4_3 = Sequence::create(act4, act4_2, NULL);
	next_road->runAction(act4_3);
}

void RoadController::makeNewRoad_callback() {

	cur_road->removeFromParent();
	cur_road = next_road;

	lane_cnt++;

	// lane_cnt에 따라서!
	next_road = cocos2d::Sprite::create("road.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, cur_road->getContentSize().height));
	road_layer->addChild(next_road);

	act_is_running = false;	// __attachLane & __detachLane function is unlocked
}

bool RoadController::__detachLane(int from_where) {

	return true;
}

void RoadController::addRailTo(Sprite* road) {

	Sprite *rail_spr1;
	Sprite *rail_spr2;

	switch (lane_cnt) {
	case 1:
		rail_spr1 = Sprite::create("rail1.png");
		rail_spr2 = Sprite::create("rail1.png");
		break;
	case 2:
		rail_spr1 = Sprite::create("rail2.png");
		rail_spr2 = Sprite::create("rail2.png");
		break;
	case 3:
		rail_spr1 = Sprite::create("rail3.png");
		rail_spr2 = Sprite::create("rail3.png");
		break;
	case 4:
		rail_spr1 = Sprite::create("rail4.png");
		rail_spr2 = Sprite::create("rail4.png");
		break;
	case 5:
		rail_spr1 = Sprite::create("rail5.png");
		rail_spr2 = Sprite::create("rail5.png");
		break;
	default:
		CCLOG("Variable lane_cnt is invalid.");
		return;
	}
	rail_spr1->setTag(RAIL_SPR_1);
	rail_spr2->setTag(RAIL_SPR_2);

	rail_spr1->setAnchorPoint(Point::ZERO);
	rail_spr1->setPosition(Point::ZERO);
	road->addChild(rail_spr1);
	rail_spr2->setAnchorPoint(Point::ZERO);
	rail_spr2->setPosition(Point(0.0, rail_spr1->getBoundingBox().getMaxY()));
	road->addChild(rail_spr2);

	float moving_distance = rail_spr1->getBoundingBox().getMaxY() - rail_spr1->getBoundingBox().getMinY();
	float moving_speed = CURRENT_SPEED_LEVEL * SPEED_CONSTANT;
	float moving_time = moving_distance / moving_speed;

	auto act1 = MoveBy::create(moving_time, Point(0.0, -moving_distance));
	auto act1_2 = CallFuncN::create(CC_CALLBACK_1(RoadController::addRail_callback, this));
	auto act1_3 = Sequence::create(act1, act1_2, NULL);
	auto act1_4 = RepeatForever::create(act1_3);
	rail_spr1->runAction(act1_4);
	auto act2 = MoveBy::create(moving_time, Point(0.0, -moving_distance));
	auto act2_2 = CallFuncN::create(CC_CALLBACK_1(RoadController::addRail_callback, this));
	auto act2_3 = Sequence::create(act2, act2_2, NULL);
	auto act2_4 = RepeatForever::create(act2_3);
	rail_spr2->runAction(act2_4);
}

void RoadController::addRail_callback(Ref *spr) {

	Sprite *rail_spr = (Sprite*)spr;

	if (rail_spr->getBoundingBox().getMaxY() <= 0.0) {
		rail_spr->setPosition(Point(0.0, rail_spr->getContentSize().height));
	}
	else {
		rail_spr->setPosition(Point(0.0, 0.0));
	}
}

void RoadController::stopRailActionOf(Sprite* road) {

}

void RoadController::release() {

	this->~RoadController();
}

RoadController::~RoadController() {

}
