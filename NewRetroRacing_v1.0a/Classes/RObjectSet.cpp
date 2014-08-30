#include "RObjectSet.h"
#include "Shared.h"
#include <string>

#define BASIC_POSITION Point(0, -500)
#define DESTRUCTION_POINT_Y -300

using namespace std;

/* ***** ***** ***** ***** ***** ***** ***** ***** ***** *****
                            RObject
   ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */

RObject* RObject::createRObject(RObjectType _type, RObjectImage _image) {
    
    RObject* new_robj = new (std::nothrow) RObject();
    
    new_robj->next_robj = NULL;
    
    switch (_type) {
        case robj_obstacle:
        case robj_coin:
        case robj_item:
            new_robj->robj_type = _type;
            break;
        default:
            new_robj->robj_type = robj_notype;
            // exception
            break;
    }
    
    string *file_name = new string("");

    switch (_image) {
        case img_alien:
            file_name->append("robj_alien.png");
            break;
        case img_android:
            file_name->append("robj_android.png");
            break;
        case img_coin:
            file_name->append("robj_coin.png");
            break;
        case img_meteor:
            file_name->append("robj_meteor.png");
            break;
        case img_moon:
            file_name->append("robj_moon.png");
            break;
        case img_planet:
            file_name->append("robj_planet.png");
            break;
        case img_satellite:
            file_name->append("robj_satellite.png");
            break;
        default:
            // exception
            break;
    }
    
    if (new_robj && new_robj->initWithFile(file_name->c_str()))
    {
        new_robj->autorelease();
        free(file_name);
        return new_robj;
    }
    
    free(file_name);
    CC_SAFE_DELETE(new_robj);
    return nullptr;
}

/* ***** ***** ***** ***** ***** ***** ***** ***** ***** *****
                            RObjectSet
   ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */

RObjectSet::RObjectSet() {
    
}
RObjectSet::~RObjectSet() {
    
}

RObjectSet* RObjectSet::generateRObjectSet(RObjectSetType _type) {
    
    RObjectSet *new_set = new RObjectSet();
    new_set->robj_list = new std::vector<RObject*>();
    new_set->_generateRObjectSet(_type);
    
    return new_set;
}
void RObjectSet::locateRObjectSet(Vec2 _point, float scale_ratio) {
    
    robj_bg->setScale(scale_ratio);
    robj_bg->setPosition(_point);
}
void RObjectSet::attachToLayer(Layer* _layer, int zOrder) {

    _layer->addChild(robj_bg, zOrder);
}
void RObjectSet::moveDownRObjectSet() {

    //float moving_distance = robj_bg->getPositionY() - DESTRUCTION_POINT_Y;
    
    if (robj_bg->getPositionY() < DESTRUCTION_POINT_Y)
        return;
    
    float ratio = robj_bg->getScale();
    float moving_distance = ROAD_HEIGHT * ratio * 2;
    if (moving_distance < 0)
        return ;
    float moving_time = moving_distance / Shared::getInstance()->getCurrentSpeed();
    
    auto act1 = MoveBy::create(moving_time, Point(0, -moving_distance));
    auto act1_2 = CallFunc::create(CC_CALLBACK_0(RObjectSet::moveDownRObjectSet, this));
    auto act1_3 = Sequence::create(act1, act1_2, NULL);
    robj_bg->runAction(act1_3);
}
void RObjectSet::release() {
    
    robj_bg->stopAllActions();
    robj_bg->removeAllChildren();
    robj_bg->removeFromParent();
    
    this->~RObjectSet();
}
void RObjectSet::relocateRObjectSet(Vec2 _point, float scale_ratio, bool* _flag) {
    
    robj_bg->stopAllActions();
    
    auto act1 = MoveTo::create(RELOCATION_TIME, _point);
    auto act1_2 = ScaleTo::create(RELOCATION_TIME, scale_ratio);
    auto act1_3 = Spawn::create(act1, act1_2, NULL);
    auto act1_4 = CallFuncN::create(CC_CALLBACK_1(RObjectSet::_relocateRObjectSet_callback, this, (void*)_flag));
    auto act1_5 = Sequence::create(act1_3, act1_4, NULL);
    robj_bg->runAction(act1_5);
}

void RObjectSet::removeRObject(RObject* robj) {
    
    for (std::vector<RObject*>::iterator it = robj_list->begin(); it != robj_list->end(); ++it) {
        if ((RObject*)*it == robj) {
            if (robj->getParent() != NULL)
                robj->removeFromParent();
            else
                robj->release();
            robj_list->erase(it);
            
            return;
        }
    }
}

void RObjectSet::_generateRObjectSet(RObjectSetType _type) {
    
    switch (_type) {
        case robj_set1:
            _generate_setType1();
            break;
        default:
            break;
    }
}
void RObjectSet::_generate_setType1() {
    
    srand(time(NULL));
    int rnum = rand() % OBS_CNT;
    
    RObjectImage obs_img;
    
    switch (rnum) {
        case 0:
            obs_img = img_alien;
            break;
        case 1:
            obs_img = img_android;
            break;
        case 2:
            obs_img = img_meteor;
            break;
        case 3:
            obs_img = img_moon;
            break;
        case 4:
            obs_img = img_planet;
            break;
        case 5:
            obs_img = img_satellite;
            break;
        default:
            return;
            break;
    }

    const int coin_cnt = 3;
    
    robj_bg = Sprite::create("robj_bg.png");
    robj_bg->setAnchorPoint(Point(0.5, 0.5));
    robj_bg->setPosition(BASIC_POSITION);

    RObject* obs = RObject::createRObject(robj_obstacle, obs_img);
    obs->setAnchorPoint(Point(0.5, 0.5));
    obs->setPosition(
         Point(robj_bg->getBoundingBox().size.width/2, robj_bg->getBoundingBox().size.height/2));
    robj_bg->addChild(obs);
    robj_list->push_back(obs);

    RObject *prev_robj = obs;
    for (int i = 0; i < coin_cnt; i++) {
        RObject *coin = RObject::createRObject(robj_coin, img_coin);
        coin->setAnchorPoint(Point(0.5, 0.5));
        if (i == 0) {
            coin->setPosition(obs->getPositionX(),
                             obs->getPositionY()
                             - obs->getBoundingBox().size.height/2
                             - coin->getBoundingBox().size.height/2 - 50);
        }
        else {
            coin->setPosition(obs->getPositionX(),
                              prev_robj->getPositionY() - coin->getBoundingBox().size.height - 50);
        }
        robj_bg->addChild(coin);
        robj_list->push_back(coin);
        prev_robj = coin;
    }
}

void RObjectSet::_relocateRObjectSet_callback(Ref* _robj, void* _flag) {

    if (_flag != NULL) {
        bool* __flag = (bool*)_flag;
        *__flag = false;
    }
    moveDownRObjectSet();
}