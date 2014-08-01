#ifndef BACKGROUNDLAYER_H_
#define BACKGROUNDLAYER_H_

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer {

public:
	static cocos2d::Layer* createBGLayer();
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);
private:

};

#endif /* BACKGROUNDLAYER_H_ */
