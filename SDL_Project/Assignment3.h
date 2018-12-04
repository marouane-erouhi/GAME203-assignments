#pragma once
#ifndef Assignment3_H
#define Assignment3_H

#include "Scene.h"

#define NUM_BODIES 21 //For multiple bodies

class Assignment3 : public Scene {
private:
	SDL_Window* window;
	MATH::Matrix4 projectionMatrix;
	class BodyinSpace* bodies[NUM_BODIES]; //For multiple bodies

	float elapsedTime;

	//Variables for colliding bodies
	float rX1NormCollision, rY1NormCollision, rX2NormCollision, rY2NormCollision; //Required by detectCollision() and calculateCollision()
	float totalRadii;
	int bodyCollided1, bodyCollided2; //Pass to calculateCollision()

public:
	Assignment3(SDL_Window* sdlWindow_);
	~Assignment3();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &event); //Button Event

	float toRadian(float _degree); //Incase angles needs to be converted
	float toDegree(float _radian); //Incase angles needs to be converted
	void initializeBodies(); //Initialize/Randomize initial position & velocity
	void detectCollision(); //Detects Collision between bodies
	void calculateCollision(); //If bodies collided then calculate their bounce velocity
	void gravity(); //Adds and calculate gravity between each objects
	
	int prevBody = 0; //Counter for Bodies' spawn positioning
	bool enableGravity;
};

#endif

