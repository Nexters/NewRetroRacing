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
        default:
            ship_name->append("rocket.png");
            break;
    }
    
    this->setObserverType(spaceship_type);
    
    num_lane = 2;
    cur_lane_num = 0;
    ratio = 1.0;
    distance = (ROAD_WIDTH - (RAIL_WIDTH * ratio * 2)) / num_lane;
    CCLOG("dis %f %d", distance, num_lane );
    
    ship = Sprite::create(ship_name->c_str());
    ship->setAnchorPoint(Point(0.5, 0.5));
    ship->setPosition(Point(getXPositionOfShip(cur_lane_num), INITIAL_Y));
}
Spaceship::~Spaceship() {
    
}

void Spaceship::attachShipTo(Layer* layer, int zOrder) {
    
    if (ship == NULL || layer == NULL) {
        return;
    }
    
    layer->addChild(ship, zOrder);
}

void Spaceship::onLaneIncrement(int how_many, int to_where) {
    
    relocateShip(how_many, to_where);
}
void Spaceship::onLaneDecrement(int how_many, int from_where) {
    
    relocateShip(-how_many, from_where);
}

void Spaceship::onVerticalRangeChange(Vec2 range) {
    
}

void Spaceship::relocateShip(int lane_change, int where) {
    
    // |   |   |   |   | <= Lanes
    //   0   1   2   3   <= Lane number
  
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
            next_lane_num += 1;
        }
    }
    else if (lane_change == -1 || lane_change == -2) {
    
        if (where == 3 && lane_change == -1)
            return ;
        
        if (where == 1 || where == 3) {
            next_lane_num -= 1;
        }
    }
    else {
        return ;
    }
    
    float x_pos = getXPositionOfShip(next_lane_num);
    
    auto act1 = MoveTo::create(RELOCATION_TIME, Point(x_pos, INITIAL_Y));
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



/*void Spaceship::setScheduler() {
    
    Director::getInstance()->getScheduler()->schedule(std::bind(&Spaceship::abc, this, std::placeholders::_1), this, 1.0, false, "a");
}
void Spaceship::abc(float delta) {
    
    CCLOG("AAA");
}
 */



/*

 #include "car.h"
 
 
 car::car(std::string name, std::string _carSpriteFileName)
 {
 carName = name;
 sCar = Sprite::create(_carSpriteFileName);
 sCar->setAnchorPoint(Vec2(0.5,0.5));
 carSize = sCar->getContentSize();
 
 actionCount = 0;
 
 }
 
 car::~car(void)
 {
 sCar->autorelease();
 }
 
 void car::addOnRoad(Node* road)
 {
 Size s = road->getContentSize();
 sCar->setPosition(245,180);
 road->addChild(sCar,3);
 moveLength = s.width/2;
 addFire();
 }
 
 void car::addFire()
 {
 Sprite* sFire = Sprite::create("fire_1.png");
 sFire->setTag(777);
 sFire->setPosition(Vec2(85,-20));
 
 SpriteFrameCache* cache = SpriteFrameCache::getInstance();
 cache->addSpriteFramesWithFile("fire.plist");
 Animation* animation = Animation::create();
 animation->setDelayPerUnit(0.2f);
 animation->addSpriteFrameWithFileName("fire_1.png");
 animation->addSpriteFrameWithFileName("fire_2.png");
 animation->addSpriteFrameWithFileName("fire_3.png");
 animation->addSpriteFrameWithFileName("fire_4.png");
 
 sFire->runAction(RepeatForever::create(Animate::create(animation)));
 sCar->addChild(sFire);
 }
 
 void car::moveRight()
 {
 MoveBy* act = MoveBy::create(0.05,Vec2(moveLength,0));
 sCar->runAction(act);
 }
 
 void car::moveLeft()
 {
 MoveBy* act = MoveBy::create(0.05,Vec2(-moveLength,0));
 sCar->runAction(act);
 }
 
 Vec2 car::getCarPosition()
 {
 return sCar->getPosition();
 }
 
 void car::setCarPosition(Vec2 pos)
 {
 sCar->setPosition(pos);
 }
 
 void car::setMoveLength(float _moveLength)
 {
 moveLength = _moveLength;
 }
 
 Sprite* car::getSpriteCar()
 {
 return this->sCar;
 }

 
*/