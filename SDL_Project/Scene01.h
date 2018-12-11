#ifndef SCENE01_H
#define SCENE01_H

#include "Scene.h"
#include "Collider.h"
#include <memory>
#include <vector>
#include "VMath.h"
#include "UIManager.h"

#include "Player.h"

class Scene01 : public Scene
{
private:
	//Test Variables to control inputs
	float screenWidth;
	float screenHeight;
	float playerVelocity;
	bool isLaunched = false;//Checks if ball is launched(runs on DragBall() and HandleEvent())
	MATH::Vec3 ballInitialVelocity;

	SDL_Window * window;
	MATH::Matrix4 projectionMatrix;
	float elapsedTime;

	float resetTimer = 0.0f;

	MATH::Vec3 ballDirection;//this is the directiono of the ball when it spawns
	float defaultBallSpeed = 200;
	float ballSpeed;

	int lives = 3;
	int scoreValue = 0;

	//Player* player;

	//Game Objects
	//std::unique_ptr<Body> ball;//Body dedicated to ball
	std::unique_ptr<Body> pin;//Body dedicated to player

	std::vector<Body*> border;//Body array to store blocks that make up the border/frame
	std::vector<Body*> blocks;//Body array dedicated to destructable blocks

	std::vector<Body*> balls;


	SDL_Renderer* screenRenderer;

	//Support Function
	//void SubRender(SDL_Rect& imageRectangle_, SDL_Surface* screenSurface_, Body& body_);

public:
	Scene01(SDL_Window* sdlWindow_, const int screenWidth_, const int screenHeight_);
	~Scene01();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time_);
	void Render();
	void HandleEvents(const SDL_Event &event); //Button Event


	//game functions
	void spawnBall();
	void changeGameSpeed();
	void resetGameSpeed();
};

#endif
