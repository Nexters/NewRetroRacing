#include "RObjectController.h"
#include "Shared.h"

#include <random>
#include <ctime>
#include <functional>

#define SCHE_KEY "generate"
#define INIT_V_RANGE Vec2(100.0, 620.0)
#define INIT_Y_POS 1600

RObjectController::RObjectController(int _lane_cnt)
:lane_cnt(_lane_cnt) {

    this->setObserverType(robj_type);
    
    start_gen_flag = false;
    is_relocating = false;
    v_range = INIT_V_RANGE;
    robj_set_list = new vector<RObjectSet*>();
    srand(time(NULL));
    prev_rnum = rand();
}

void RObjectController::attachRObjectsTo(Layer *_layer, int _zOrder) {
    
    parent_layer = _layer;
    zOrder = _zOrder;
}

void RObjectController::startGeneratingRObjects() {
    
    if (start_gen_flag == true)
        return;
    
    start_gen_flag = true;
    
    sche_cnt = 0;
    float interval = GAME_SCENE_HEIGHT / Shared::getInstance()->getCurrentSpeed();
    Director::getInstance()->getScheduler()
    ->schedule(std::bind(&RObjectController::generateRObjects, this, std::placeholders::_1),
               this, interval, false, SCHE_KEY);
}
void RObjectController::stopGeneratingRObjects() {
    
    if (start_gen_flag == false)
        return;
    
    Director::getInstance()->getScheduler()->unschedule(SCHE_KEY, this);
    
    start_gen_flag = false;
}
void RObjectController::release() {

    this->~RObjectController();
}

void RObjectController::onLaneChange(int current, int next, int to_where) {
    
    is_relocating = true;
    if (!robj_set_list->empty())
        relocateRObects(next - current, to_where, &is_relocating);
    else
        is_relocating = false;
    lane_cnt = next;
}
void RObjectController::onVerticalRangeChange(Vec2 range) {
    
    v_range = range;
}

void RObjectController::generateRObjects(float dt) {
    
    if (parent_layer == NULL)
        return;
    if (is_relocating)
        return;
    
    sche_cnt++;
    
    bool box[MAX_LANE_CNT] = {false, };
    bool all_true = true;
    
    for (int i = 0; i < lane_cnt; i++) {
        int yn = generateRandomNumber(2);
        if (yn == 0) {
            box[i] = true;
        }
        else {
            all_true = false;
        }
    }
    
    if (all_true) {
        int rn = generateRandomNumber(lane_cnt);
        box[rn] = false;
    }
    for (int i = 0; i < lane_cnt; i++) {
        if (box[i] == true) {
            _generateRObjects(i);
        }
    }
    
    // 화면 밑으로 내려간 RObjectSet은 정리해준다.
    for (vector<RObjectSet*>::iterator it = robj_set_list->begin(); it != robj_set_list->end(); ) {
        RObjectSet* set = *it;
        if (set->getPosition().y < -500) {
            it = robj_set_list->erase(it);
            set->release();
        }
        else
            ++it;
	}

    if (sche_cnt > 10) {
        sche_cnt = 0;
        float interval = GAME_SCENE_HEIGHT / Shared::getInstance()->getCurrentSpeed();
        Director::getInstance()->getScheduler()->unschedule(SCHE_KEY, this);
        Director::getInstance()->getScheduler()
        ->schedule(std::bind(&RObjectController::generateRObjects, this, std::placeholders::_1),
                   this, interval, false, SCHE_KEY);
    }
}
void RObjectController::_generateRObjects(int lane_num) {

    float ratio = 2.0 / lane_cnt;
    float x_pos = Shared::getXPositionOfObject(lane_cnt, lane_num, ratio);
    if (x_pos < v_range.x || x_pos > v_range.y)
        return;
    
    RObjectSet *set = RObjectSet::generateRObjectSet(robj_set1);
    set->locateRObjectSet(Point(x_pos, INIT_Y_POS), ratio);
    set->attachToLayer(parent_layer, zOrder);
    set->moveDownRObjectSet();
    set->setLaneNumber(lane_num);
    robj_set_list->push_back(set);
}

void RObjectController::relocateRObects(int lane_change, int where, bool* _flag) {
    
    // |   |   |   |   | <= Lanes
    //   0   1   2   3   <= Lane number
    
    if (lane_cnt + lane_change < 2)
        return ;
    if (lane_cnt + lane_change > 4)
        return ;
    
    float ratio = 2.0 / (lane_cnt + lane_change);
    
    for (vector<RObjectSet*>::iterator it = robj_set_list->begin(); it != robj_set_list->end(); ++it) {
        
        RObjectSet* set = *it;
        int cur_lane_num = set->getLaneNumber();
        
        if (lane_change == 1 || lane_change == 2) {
            if (where == 3 && lane_change == 1) // 예외처리
                return ;
            if (where == 1 || where == 3) {
                // 왼쪽에 lane이 하나 추가되는 경우 or 양쪽에 lane이 하나씩 추가되는경우
                if(lane_change==2 && where == 1)
                    cur_lane_num += 2;
                else
                    cur_lane_num += 1;
            }
        }
        else if (lane_change == -1 || lane_change == -2) {
            if (where == 3 && lane_change == -1) // 예외처리
                return ;
            if (where == 1 || where == 3) {
                // 왼쪽에 lane이 하나 제거되는 경우 or 양쪽에 lane이 하나씩 제거되는 경우
                if(lane_change==-2 && where==1)
                    cur_lane_num -= 2;
                else
                    cur_lane_num -= 1;
            }
        }
        else {
            return ;
        }
        float old_x_pos = set->getPosition().x;
        float new_x_pos = Shared::getXPositionOfObject(lane_cnt + lane_change, cur_lane_num, ratio);
        float diff_x = 0.0;
        if (new_x_pos > old_x_pos)
            diff_x = new_x_pos - old_x_pos;
        else
            diff_x = old_x_pos - new_x_pos;
        float old_y_pos = set->getPosition().y;
        float new_y_pos = old_y_pos * ratio;
        
        if (it == robj_set_list->begin()) {
            set->relocateRObjectSet(Point(new_x_pos, new_y_pos), ratio, &is_relocating);
        }
        else
            set->relocateRObjectSet(Point(new_x_pos, new_y_pos), ratio, NULL);
        set->setLaneNumber(cur_lane_num);
	}
}

int RObjectController::generateRandomNumber(unsigned int max) {
    
    srand(time(NULL));
    unsigned int rnum = rand();
    if (rnum == prev_rnum) {
        rnum = rnum % 17;
        rnum += prev_rnum;
    }
    prev_rnum = rnum;
    
    int ret_val = rnum % max;
    
    return ret_val;
}

RObjectController::~RObjectController() {
    
    for (vector<RObjectSet*>::iterator it = robj_set_list->begin(); it != robj_set_list->end(); ) {
        RObjectSet* set = *it;
        it = robj_set_list->erase(it);
        set->release();
	}
}
