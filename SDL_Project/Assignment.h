#ifndef Assignment_H
#define Assignment_H

#include "Scene.h"

#define NUM_BODIES 3 //For multiple bodies

class Assignment : public Scene {
private:
	SDL_Window* window;
	MATH::Matrix4 projectionMatrix;
	class Body* bodies[NUM_BODIES]; //For multiple bodies
	float elapsedTime;

public:
	Assignment(SDL_Window* sdlWindow_);
	~Assignment();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &event); //Button Event
};

#endif

