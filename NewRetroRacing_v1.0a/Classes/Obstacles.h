#ifndef OBSTACLES_H_
#define OBSTACLES_H_
#define TAG_SPRITE_COIN 1002
#include "cocos2d.h"

USING_NS_CC;

class Obstacles {
public:
	Obstacles();
	virtual ~Obstacles();

	void addObstacle(Layer *layer);
	void stopAnimation();
	Array* getObstacleArray() { return obs_array; }

	static float moving_time;


private:
	Array *obs_array;

private:

	void ObstacleActionCallBack(Ref *sender);
};

#endif /* OBSTACLES_H_ */
