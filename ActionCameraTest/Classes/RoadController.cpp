#include "RoadController.h"

RoadController::RoadController() {

	road_layer = cocos2d::Layer::create();

	cur_road = cocos2d::Sprite::create("rail.png");
	cur_road->setAnchorPoint(Point(0.5, 0.0));
	cur_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, 0.0));
	road_layer->addChild(cur_road);

	next_road = cocos2d::Sprite::create("rail.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, cur_road->getContentSize().height));
	road_layer->addChild(next_road);

	Rect road_rect = cur_road->getBoundingBox();

	lane_cnt = 2;
	hor_range = Vec2(road_rect.getMinX(), road_rect.getMaxX());
	lane_width = (road_rect.getMaxX() - road_rect.getMinX()) / 2;
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

void RoadController::attachLane(int to_where) {

	try {
		switch (to_where) {
		case 1:		// 1: Attach lane to left side of road
		case 2:		// 2: Attach lane to right side of road
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
		return;
	}
}

bool RoadController::__attachLane(int to_where) {


	float cur_road_height = cur_road->getBoundingBox().getMaxY() - cur_road->getBoundingBox().getMinY();
	float resizing_ratio = (float)lane_cnt / (lane_cnt + 1);
	float moving_speed = CURRENT_SPEED_LEVEL * SPEED_CONSTANT;

	float act2_moving_distance = (cur_road_height * (1 - resizing_ratio));
	float act2_moving_time = act2_moving_distance / moving_speed;

	CCLOG("moving_speed %f", moving_speed);

	if (to_where == 1) {

		cur_road->setAnchorPoint(Point(1.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMaxX(), 0.0));

		auto act1 = ScaleBy::create(act2_moving_time, resizing_ratio);
		cur_road->runAction(act1);
		auto act2 = MoveBy::create(act2_moving_time,
								Point(0.0, -act2_moving_distance));
		next_road->runAction(act2);
	}
	else if (to_where == 2) {

		cur_road->setAnchorPoint(Point(0.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMinX(), 0.0));

		auto act1 = ScaleBy::create(act2_moving_time, resizing_ratio);
		cur_road->runAction(act1);
		auto act2 = MoveBy::create(act2_moving_time,
								Point(0.0, -act2_moving_distance));
		next_road->runAction(act2);
	}


	cur_road_height = cur_road_height * resizing_ratio;
	CCLOG("moving_speed %f", moving_speed);
	float act3_moving_distance = cur_road_height;
	float act3_moving_time = act3_moving_distance / moving_speed;
	auto act3 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	auto act3_2 = CallFunc::create(CC_CALLBACK_1(RoadController::removeCurrentRoad_callback, road_layer));
	auto act3_3 = Sequence::create(act3, act3_2, NULL);
	cur_road->runAction(act3_3);
	auto act4 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	auto act4_2 = CallFunc::create(CC_CALLBACK_1(RoadController::makeNewRoad_callback, this));
	auto act4_3 = Sequence::create(act4, act4_2, NULL);
	next_road->runAction(act4_3);

	return true;
}

void RoadController::removeCurrentRoad_callback(CCNode *spr_cur_road) {

	cur_road->removeFromParent();
	cur_road->release();
	cur_road = next_road;

	//lane_cnt++;
}

void RoadController::makeNewRoad_callback(CCNode *spr_cur_road) {

	next_road = cocos2d::Sprite::create("rail.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, cur_road->getContentSize().height));
	road_layer->addChild(next_road);
}

void RoadController::detachLane(int from_where) {

}

void RoadController::release() {

	this->~RoadController();
}

RoadController::~RoadController() {

}
