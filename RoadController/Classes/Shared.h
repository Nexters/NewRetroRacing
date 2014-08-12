#ifndef SHARED_H_
#define SHARED_H_

//

#define GAME_SCENE_WIDTH 720
#define GAME_SCENE_HEIGHT 1280

#define SPEED_CONSTANT 10.0
#define BASIC_SPEED 300.0

class SHARED {
public:
	static float SCREEN_SIZE_RATIO;
	static float ELAPSED_TIME;

	static float getCurrentSpeed(int elapsed_time);
};

#endif /* CONSTANTS_H_ */
