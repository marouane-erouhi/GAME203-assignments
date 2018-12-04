#ifndef Assignment2_H
#define Assignment2_H

#include "Scene.h"

#define NUM_BODIES 3 //For multiple bodies

class Assignment2 : public Scene {
private:
	SDL_Window* window;
	MATH::Matrix4 projectionMatrix;
	class BodyinSpace* bodies[NUM_BODIES]; //For multiple bodies
	float elapsedTime;

public:
	Assignment2(SDL_Window* sdlWindow_);
	~Assignment2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &event); //Button Event
};

#endif

