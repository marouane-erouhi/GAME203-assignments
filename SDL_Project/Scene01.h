#ifndef SCENE01_H
#define SCENE01_H

#include "Scene.h"
#include "Collider.h"
#include "Player.h"
#include <memory>
#include <vector>

class Scene01 : public Scene
{
private:
	//Test Variables to control inputs
	float screenWidth;
	float screenHeight;
	float playerVelocity;
	Player* player;
	
	bool isLaunched = false;//Checks if ball is launched(runs on DragBall() and HandleEvent())
	MATH::Vec3 ballInitialVelocity;

	SDL_Window * window;
	MATH::Matrix4 projectionMatrix;
	float elapsedTime;
	
	//Game Objects
	std::unique_ptr<Body> ball;//Body dedicated to ball
	std::unique_ptr<Body> pin;//Body dedicated to player
	std::vector<Body*> border;//Body array to store blocks that make up the border/frame
	//std::vector<Body*> blocks;//Body array dedicated to destructable blocks

	//Support Function
	void SubRender(SDL_Rect& imageRectangle_, SDL_Surface* screenSurface_, Body& body_);

public:
	Scene01(SDL_Window* sdlWindow_, const int screenWidth_, const int screenHeight_);
	~Scene01();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time_);
	void Render();
	void HandleEvents(const SDL_Event &event); //Button Event

};

#endif
