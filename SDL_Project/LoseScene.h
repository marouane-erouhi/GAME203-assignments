//#pragma once
//#include "Scene.h"
//#include "Collider.h"
//#include <memory>
//#include <vector>
//#include "VMath.h"
//class LoseScene : public Scene {
//private:
//	//Test Variables to control inputs
//	float screenWidth;
//	float screenHeight;
//
//	SDL_Window * window;
//	MATH::Matrix4 projectionMatrix;
//	float elapsedTime;
//
//	//Support Function
//	void SubRender(SDL_Rect& imageRectangle_, SDL_Surface* screenSurface_, Body& body_);
//
//public:
//	LoseScene(SDL_Window* sdlWindow_, const int screenWidth_, const int screenHeight_);
//	~LoseScene();
//	bool OnCreate();
//	void OnDestroy();
//	void Update(const float time_);
//	void Render();
//	void HandleEvents(const SDL_Event &event); //Button Event
//};