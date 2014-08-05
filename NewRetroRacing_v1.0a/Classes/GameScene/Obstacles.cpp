#include "Obstacles.h"
#include "time.h"

float Obstacles::moving_time = 1.5;

Obstacles::Obstacles() {
	// TODO Auto-generated constructor stub
	obs_array = Array::create();
	obs_array->retain();

	moving_time = 1.5;

}

void Obstacles::addObstacle(Layer *layer) {

	Sprite *obs = NULL;
	srand(time(NULL));
	int ran_num = rand() % 3;

	switch(ran_num) {
	case 0:
		obs = Sprite::create("obstacle_1.png");
		break;
	case 1:
		obs = Sprite::create("obstacle_2.png");
		break;
	case 2:
		obs = Sprite::create("obstacle_3.png");
		break;
	}

	if (obs == NULL)
		return ;

	obs->setAnchorPoint(Point(0.5, 0.5));
	srand(time(NULL));
	ran_num = rand() % 4;
	switch(ran_num) {
	case 0:
	case 3:
		obs->setPosition(245, 1500);
		break;
	case 1:
	case 2:
		obs->setPosition(245+230, 1500);
		break;
	}


	auto obs_act1 = MoveTo::create(1.3, Point(obs->getPositionX(), -300));

	auto obs_act2 = CallFuncN::create(CC_CALLBACK_1(Obstacles::ObstacleActionCallBack, this));
	auto obs_act3 = Sequence::create(obs_act1, obs_act2, NULL);
	obs->runAction(obs_act3);

	obs_array->addObject(obs);
	layer->addChild(obs);
}

void Obstacles::stopAnimation() {

}

void Obstacles::ObstacleActionCallBack(Ref *sender) {
	CCLOG("CALLBACK!");
	Sprite *spr = (Sprite*)sender;
	spr->removeFromParent();
	obs_array->removeObject(sender, true);
}

Obstacles::~Obstacles() {
	// TODO Auto-generated destructor stub
	obs_array->removeAllObjects();
	obs_array->release();
}

