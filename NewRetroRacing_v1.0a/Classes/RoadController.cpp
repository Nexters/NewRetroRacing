#include "RoadController.h"
#include "Shared.h"

#define RAIL_HEIGHT 250.0

RoadController::RoadController() {

	road_layer = cocos2d::Layer::create();

    num_lane = 2;		// 초기 lane 갯수는 2
    
	// current road sprite setting
	cur_road = cocos2d::Sprite::create("road_2560.png");
	cur_road->setAnchorPoint(Point(0.5, 0.0));
	cur_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, 0.0));
	road_layer->addChild(cur_road);
	addRailTo(cur_road, num_lane);	// add rail sprites to current road sprite

	// next road sprite setting
	next_road = cocos2d::Sprite::create("road_2560.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, GAME_SCENE_HEIGHT));
	road_layer->addChild(next_road);
    
	// calculate horizontal range & lane width
	Rect road_rect = cur_road->getBoundingBox();
    
	hori_rails = new Vector<Sprite*>();
    
    Shared *shared = Shared::getInstance();
    shared->setTheNumberOfLanes(num_lane);
    shared->setValidHorizontalRangeOfCar(Vec2(cur_road->getBoundingBox().getMinX(),
                                              cur_road->getBoundingBox().getMaxX()));
    shared->setValidHorizontalRangeOfObstacle(Vec2(cur_road->getBoundingBox().getMinX(),
                                                   cur_road->getBoundingBox().getMaxX()));
    
	change_running = false;
}

void RoadController::attachRoadLayerTo(Layer* _layer, int zOrder) {

	if (road_layer == NULL) {
		CCLOG("RoadController::attachRoadLayerTo(Layer* _layer): road_layer is NULL");
		return;
	}
	_layer->addChild(road_layer, zOrder);
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

	// calculate resizing ratio of current road sprite & add rail sprites to next road sprite.
	float resizing_ratio = (float)num_lane / (num_lane + how_many);
	addRailTo(next_road, num_lane + how_many);
	pauseRailActionsOfNextRoad(next_road);
                    // Because addRailTo function start actions of rail sprites,
	pauseRailActionsOfCurrentRoad(cur_road, resizing_ratio);
                    // you should pause the actions until process of attachLanes is over.

	// set basic values for attaching Lane(s)
	if (to_where == 1) {		// 좌측에 lane이 더해지는 경우
		cur_road->setAnchorPoint(Point(1.0, 0.0));	// Anchor point를 우측 하단에 잡는다.
		cur_road->setPosition(Point(next_road->getBoundingBox().getMaxX(), 0.0)); // 다음 생성될 road와 오른쪽 끝 라을 맞춘다.
		for (int i = 0; i < how_many; i++)
			addHorizontalRailTo(next_road, num_lane + how_many, i+1);
	}
	else if (to_where == 2) {
		cur_road->setAnchorPoint(Point(0.0, 0.0));
		cur_road->setPosition(Point(next_road->getBoundingBox().getMinX(), 0.0));
		for (int i = 0; i < how_many; i++)
			addHorizontalRailTo(next_road, num_lane + how_many, num_lane + how_many - i);
	}
	else if (to_where == 3) {
		cur_road->setAnchorPoint(Point(0.5, 0.0));
		cur_road->setPosition(
				Point(GAME_SCENE_WIDTH / 2.0, 0.0)
				);		// 다음 생성될 road의 가로 중간점.
		addHorizontalRailTo(next_road, num_lane + how_many, 1);
		addHorizontalRailTo(next_road, num_lane + how_many, num_lane + how_many);
	}
	else
		return;
    
    // >> 여기서 Spaceship의 relocation이 필요하다. (attach lanes)
//    ship->relocateShip(how_many, to_where);

	// start actions
	auto act1 = ScaleBy::create(RELOCATION_TIME, resizing_ratio);
	auto act1_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::removeCurrentRoad_callback, this));
	auto act1_3 = Sequence::create(act1, act1_2, NULL);
	cur_road->runAction(act1_3);								// current road의 scale을 축소

	num_lane += how_many;
}

void RoadController::removeCurrentRoad_callback() {
    
	Rect cur_road_rect = cur_road->getBoundingBox();
	if (cur_road_rect.size.height >= GAME_SCENE_HEIGHT) {
		float ratio = cur_road->getScale();
		Rect cur_road_visible_rect = Rect(0, cur_road_rect.size.height - next_road->getPositionY(),
											cur_road_rect.size.width / ratio, next_road->getPositionY() / ratio);
		cur_road->setTextureRect(cur_road_visible_rect);	// Rect의 이중 비율 변화...
	}
    
    // 작아진 길에서 Car가 움직일 수 있는 가로 범위 설정
    Shared *shared = Shared::getInstance();
    shared->setValidHorizontalRangeOfCar(Vec2(cur_road_rect.getMinX(), cur_road_rect.getMaxX()));

	float moving_speed = Shared::getInstance()->getCurrentSpeed();
	float act3_moving_distance = next_road->getPositionY();
	float act3_moving_time = act3_moving_distance / moving_speed;

	auto act3 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	cur_road->runAction(act3);

	auto act4 = MoveBy::create(act3_moving_time, Point(0.0, -act3_moving_distance));
	auto act4_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::makeNewRoad_callback, this));
	auto act4_3 = Sequence::create(act4, act4_2, NULL);			// RoadController::makeNewRoad_callback
	next_road->runAction(act4_3);
}

void RoadController::__detachLane(int how_many, int from_where) {

	change_running = true;	// __attachLane & __detachLane function is locked

	float resizing_ratio = (float)num_lane / (num_lane - how_many);
	addRailTo(next_road, num_lane - how_many);
	pauseRailActionsOfNextRoad(next_road);
	pauseRailActionsOfCurrentRoad(cur_road, resizing_ratio);

	if (from_where == 1) {
		next_road->setAnchorPoint(Point(1.0, 0.0));
		next_road->setPosition(
			Point(cur_road->getBoundingBox().getMaxX(), next_road->getPositionY()));
		for (int i = 0; i < how_many; i++)
			addHorizontalRailTo(cur_road, num_lane, i+1);
	}
	else if (from_where == 2) {
		next_road->setAnchorPoint(Point(0.0, 0.0));
		next_road->setPosition(
			Point(cur_road->getBoundingBox().getMinX(), next_road->getPositionY()));
		for (int i = 0; i < how_many; i++)
			addHorizontalRailTo(cur_road, num_lane, num_lane-i);
	}
	else if (from_where == 3) {
		next_road->setAnchorPoint(Point(0.5, 0.0));
		next_road->setPosition(
				Point((cur_road->getBoundingBox().getMinX() + cur_road->getBoundingBox().getMaxX()) / 2.0,
						next_road->getPositionY()));
		addHorizontalRailTo(cur_road, num_lane, 1);
		addHorizontalRailTo(cur_road, num_lane, num_lane);
	}
	next_road->setScale(1 / resizing_ratio);

	Rect cur_road_rect = cur_road->getBoundingBox();
	Rect cur_road_visible_rect = Rect(0, cur_road_rect.size.height - next_road->getPositionY(),
										cur_road_rect.size.width, next_road->getPositionY());
	cur_road->setTextureRect(cur_road_visible_rect);

	float moving_speed = Shared::getInstance()->getCurrentSpeed();
	float act2_moving_distance = next_road->getPositionY();
	float act2_moving_time = act2_moving_distance / moving_speed;

	// start actions
	auto act1 = MoveBy::create(act2_moving_time,
							Point(0.0, -act2_moving_distance));
	next_road->runAction(act1);

	auto act2 = MoveBy::create(act2_moving_time,
							Point(0.0, -act2_moving_distance));
	auto act2_2 = CallFuncN::create(
			CC_CALLBACK_1(RoadController::removeCurrentRoad_callback_d, this, (void*)new float(resizing_ratio))
			);			// RoadController::removeCurrentRoad_callback_d(Ref *sender, void *d)
	auto act2_3 = Sequence::create(act2, act2_2, NULL);
	cur_road->runAction(act2_3);

	num_lane -= how_many;
}

void RoadController::removeCurrentRoad_callback_d(Ref *sender, void *d) {

	float resizing_ratio = *(float*)d;

    if (!hori_rails->empty())
        removeHorizontalRail();
    
    // >> 여기서 Spaceship의 relocation이 필요하다. (detach lanes)
//    ship->relocateShip(-lc, w);
    
	auto act1 = ScaleBy::create(RELOCATION_TIME, resizing_ratio);
	auto act1_2 = CallFuncN::create(CC_CALLBACK_0(RoadController::makeNewRoad_callback, this));
	auto act1_3 = Sequence::create(act1, act1_2, NULL);		// RoadController::makeNewRoad_callback
	next_road->runAction(act1_3);
}

void RoadController::makeNewRoad_callback() {

    if (!hori_rails->empty())
        removeHorizontalRail();
    
	cur_road->removeFromParent();
	cur_road = next_road;
	resumeRailActionsOf(cur_road);
    
    // 새로운 길에서 Car가 움직일 수 있는 가로 범위 설정
    Rect cur_road_rect = cur_road->getBoundingBox();
    Shared *shared = Shared::getInstance();
    shared->setValidHorizontalRangeOfCar(Vec2(cur_road_rect.getMinX(), cur_road_rect.getMaxX()));

	next_road = cocos2d::Sprite::create("road_2560.png");
	next_road->setAnchorPoint(Point(0.5, 0.0));
	next_road->setPosition(Point(GAME_SCENE_WIDTH / 2.0, GAME_SCENE_HEIGHT));
	road_layer->addChild(next_road);

	change_running = false;	// __attachLane & __detachLane function is unlocked
}

void RoadController::addRailTo(Sprite* road, int _num_lane) {

    std::string *img_file_name = new std::string("");
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

	float rail_height = RAIL_HEIGHT;
	rail_height *= size_ratio;

	for (float height_sum = 0.0;
			height_sum <= (road->getContentSize().height + 2 * rail_height);
			height_sum += rail_height) {

		Sprite *rail_spr = Sprite::create(img_file_name->c_str());
		rail_spr->setAnchorPoint(Point(0.5, 0.0));
		rail_spr->setPosition(Point(road->boundingBox().size.width / 2.0, height_sum));
		rail_spr->setScale(size_ratio);
		road->addChild(rail_spr);
		railAction_callback(rail_spr, road);
	}
}

void RoadController::railAction_callback(Ref *_rail_spr, Ref* _road) {

	Sprite *rail_spr = (Sprite*)_rail_spr;
	Sprite *road = (Sprite*)_road;

	float rail_height = rail_spr->getBoundingBox().size.height;
	float moving_speed = Shared::getInstance()->getCurrentSpeed();
	float moving_time = rail_height / moving_speed;

	if (rail_spr->getBoundingBox().getMaxY() <= 0.1) {
		int num_rail = ((GAME_SCENE_HEIGHT * 2 + rail_height) / rail_height) + 2;
		rail_spr->setPosition(Point(road->getBoundingBox().size.width / 2.0, rail_height * (num_rail - 1)));
	}

	auto act1 = MoveBy::create(moving_time, Point(0.0, -rail_height));
	auto act2 = CallFuncN::create(CC_CALLBACK_1(RoadController::railAction_callback, this, road));
	auto act3 = Sequence::create(act1, act2, NULL);
	rail_spr->runAction(act3);
}

void RoadController::pauseRailActionsOfNextRoad(Sprite* road) {
 
    Vector<Node*> rail_imgs = road->getChildren();
    
	for (std::vector<Node*>::iterator it = rail_imgs.begin(); it != rail_imgs.end(); ++it) {
        
		Sprite *rail_spr = (Sprite*)*it;
        rail_spr->pause();
		Rect rail_spr_rect = rail_spr->getBoundingBox();
		Rect road_spr_rect = road->getBoundingBox();
	}
}

void RoadController::pauseRailActionsOfCurrentRoad(Sprite* road, float resizing_ratio) {

	Vector<Node*> rail_imgs = road->getChildren();
	float new_next_position_y = GAME_SCENE_HEIGHT + RAIL_HEIGHT + 10;

	for (std::vector<Node*>::iterator it = rail_imgs.begin(); it != rail_imgs.end(); ++it) {

		Sprite *rail_spr = (Sprite*)*it;
        rail_spr->pause();
		Rect rail_spr_rect = rail_spr->getBoundingBox();
		Rect road_spr_rect = road->getBoundingBox();

		if (resizing_ratio < 1.0 &&
			rail_spr_rect.getMinY() * resizing_ratio >= GAME_SCENE_HEIGHT) {
			if (rail_spr_rect.getMinY() * resizing_ratio < new_next_position_y)
				new_next_position_y = rail_spr_rect.getMinY() * resizing_ratio;
			rail_spr->setVisible(false);
		}
		else if (resizing_ratio >= 1.0 && rail_spr_rect.getMinY() >= GAME_SCENE_HEIGHT) {
			if (rail_spr_rect.getMinY() < new_next_position_y)
				new_next_position_y = rail_spr_rect.getMinY();
			rail_spr->setVisible(false);
		}
		else {

		}
	}
    next_road->setPositionY(new_next_position_y);
}

void RoadController::resumeRailActionsOf(Sprite* road) {

	Vector<Node*> rail_imgs = road->getChildren();
	for (std::vector<Node*>::iterator it = rail_imgs.begin(); it != rail_imgs.end(); ++it) {
		Sprite *rail_spr = (Sprite*)*it;
        rail_spr->resume();
		rail_spr->setVisible(true);
	}
}

void RoadController::addHorizontalRailTo(Sprite* road, int _num_lane, int lane_num) {

	float ratio = 2.0 / _num_lane;
	auto hori_rail = Sprite::create("horizontal_rail.png");
	hori_rail->setAnchorPoint(Point(0.5, 0.0));

	float x = (135.0 + (255 * (lane_num - 1))) * ratio;
	float y = -10.0 * ratio;
	if (road == cur_road) {
		y = next_road->getPositionY() - (15 * ratio);
	}
	hori_rail->setPosition(Point(x, y));
	hori_rail->setScale(ratio);
	road->addChild(hori_rail);
	hori_rails->pushBack(hori_rail);
}

void RoadController::removeHorizontalRail() {

	for (std::vector<Sprite*>::iterator it = hori_rails->begin(); it != hori_rails->end(); ++it) {
		Sprite *hori_rail = (Sprite*)*it;
		hori_rail->removeFromParent();
	}
}

void RoadController::release() {

	this->~RoadController();
}

RoadController::~RoadController() {

	if (cur_road != NULL)
		cur_road->removeFromParent();
	if (next_road != NULL)
		cur_road->removeFromParent();
	if (road_layer != NULL)
		road_layer->removeFromParent();
}
