#ifndef NUM_BODIES
#define NUM_BODIES 4 //Number of blocks
#endif

#ifndef SCENE01_H
#define SCENE01_H

#include "Scene.h"
#include "Collider.h"


class Scene01 : public Scene
{
private:
	float posX;
	float posY;
	float velX;
	float velY;
	float velTest;

	SDL_Window * window;
	MATH::Matrix4 projectionMatrix;
	class Body* ball;
	class Body* blocks[NUM_BODIES]; //For multiple bodies
	float elapsedTime;

	Collider collider;

public:
	Scene01(SDL_Window* sdlWindow_);
	~Scene01();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time_);
	void Render();
	void HandleEvents(const SDL_Event &event); //Button Event

};

#endif
