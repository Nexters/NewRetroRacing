#ifndef OBSTACLES_H_
#define OBSTACLES_H_

#include "cocos2d.h"

USING_NS_CC;

class Obstacles {
public:
	Obstacles();
	virtual ~Obstacles();

	void addObstacle(Layer *layer);
	void stopAnimation();
	Array* getObstacleArray() { return obs_array; }

private:
	Array *obs_array;

private:

	void ObstacleActionCallBack(Ref *sender);
};

#endif /* OBSTACLES_H_ */
