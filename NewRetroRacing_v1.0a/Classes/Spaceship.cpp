#include "Spaceship.h"
#include "Shared.h"
#include <string>

using namespace std;

Spaceship::Spaceship(int ship_num) {
    
    string *ship_name = new string("");
    
    switch (ship_num) {
        case 0:
            ship_name->append("rocket.png");
            break;
		case 1:
            ship_name->append("rocket2.png");
            break;
		case 2:
            ship_name->append("rocket3.png");
            break;
        default:
            ship_name->append("rocket.png");
            break;
    }
    
    this->setObserverType(spaceship_type);
    
    num_lane = 2;
    cur_lane_num = 0;
    ratio = 1.0;
    distance = (ROAD_WIDTH - (RAIL_WIDTH * ratio * 2)) / num_lane;
    
    ship = Sprite::create(ship_name->c_str());
    ship->setAnchorPoint(Point(0.5, 0.5));
    ship->setPosition(Point(getXPositionOfShip(cur_lane_num), INITIAL_Y));
	
	body = PhysicsBody::createCircle(100.0,PhysicsMaterial(0,1,0));
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(true);
	body->setDynamic(false);
	ship->setPhysicsBody(body);
	
	roadRange.x = 100+distance;
	roadRange.y = 620-distance;
	addFire();
}

void Spaceship::addFire()
{
	Sprite* sFire = Sprite::create("fire_1.png");
	sFire->setTag(777);
	sFire->setPosition(Vec2(85,-20));

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrameWithFileName("fire_1.png");
	animation->addSpriteFrameWithFileName("fire_2.png");
	animation->addSpriteFrameWithFileName("fire_3.png");
	animation->addSpriteFrameWithFileName("fire_4.png");

	sFire->runAction(RepeatForever::create(Animate::create(animation)));
	ship->addChild(sFire);
}

void Spaceship::attachShipTo(Layer* layer, int zOrder) {
    
    if (ship == NULL || layer == NULL) {
        return;
    }
    layer->addChild(ship, zOrder);
}

void Spaceship::onLaneChange(int current, int next, int to_where) {
    
    relocateShip(next - current, to_where);
}

void Spaceship::onVerticalRangeChange(Vec2 range) {
	roadRange.x = range.x+distance;
	roadRange.y = range.y-distance;
}

void Spaceship::relocateShip(int lane_change, int where) {
    
    // |   |   |   |   | <= Lanes
    //   0   1   2   3   <= Lane number
  
	if(cur_lane_num<0)
		cur_lane_num=0;
	if(cur_lane_num>4)
		cur_lane_num=4;

    if (num_lane + lane_change < 2)
        return ;
    if (num_lane + lane_change > 4)
        return ;
    
    ratio = 2.0 / (num_lane + lane_change);
    int next_lane_num = cur_lane_num;
    
    distance = (ROAD_WIDTH - (RAIL_WIDTH * ratio * 2)) / (num_lane + lane_change);
    
    if (lane_change == 1 || lane_change == 2) {
        
        if (where == 3 && lane_change == 1)
            return ;
        
        if (where == 1 || where == 3) {     // 왼쪽에 lane이 하나 추가되는 경우 or 양쪽에 lane이 하나씩 추가되는경우
			if(lane_change==2 && where == 1)
				next_lane_num += 2;
			else
				next_lane_num += 1;
        }
    }
    else if (lane_change == -1 || lane_change == -2) {
    
        if (where == 3 && lane_change == -1)
            return ;
        
        if (where == 1 || where == 3) {
			if(lane_change==-2 && where==1)
				next_lane_num -= 2;
			else
				next_lane_num -= 1;
        }
    }
    else {
        return ;
    }
    
    float x_pos = getXPositionOfShip(next_lane_num);
    
    auto act1 = MoveTo::create(RELOCATION_TIME, Point(x_pos, INITIAL_Y * ratio));
    auto act1_2 = ScaleTo::create(RELOCATION_TIME, ratio);
    auto act1_3 = Spawn::create(act1, act1_2, NULL);
    ship->runAction(act1_3);
    
    num_lane += lane_change;
    cur_lane_num = next_lane_num;
}
float Spaceship::getXPositionOfShip(int lane_num) {
    
    float x_pos = LEFT_MARGIN + (RAIL_WIDTH * ratio) + (distance / 2);
    for (int i = 0; i < lane_num; i++) {
        x_pos += distance;
    }
    return x_pos;
}
Vec2 Spaceship::getMoveRange()
{
	return roadRange;
}

Vec2 Spaceship::getSpaceShipPos()
{
	return ship->getPosition();
}

Sprite* Spaceship::getSpriteSpaceShip()
{
	return ship;
}

PhysicsBody* Spaceship::getSpacePhysicsBody()
{
	return body;
}

void Spaceship::moveRight()
{
	cur_lane_num++;
	auto act = MoveBy::create(0.01*SPEEDVAL,Vec2(distance,0));
	ship->runAction(act);
}

void Spaceship::moveLeft()
{
	cur_lane_num--;
	auto act = MoveBy::create(0.01*SPEEDVAL,Vec2(-distance,0));
	ship->runAction(act);
}

//피버모드에 들어설때 부르는 함수
void Spaceship::resetting()
{//resetting spaceship, sprite, physicsBody
	if(Shared::getInstance()->isFeverMode())
	{//

	}
	else
	{}
}

void Spaceship::releaseSpaceship() {
    
    releaseObject(ship);
    this->~Spaceship();
}

Spaceship::~Spaceship() {
    
}
