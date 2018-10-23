#ifndef SCENE0_H
#define SCENE0_H
#include "MMath.h"

#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "UIManager.h"
class Scene0 : public Scene {
private:
	SDL_Window *window;
	MATH::Matrix4 projectionMatrix;
	SDL_Renderer * renderer;

	//text test
	TTF_Font* Sans;
	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;

	//UIContainer * currentUI;

	//scene data
	int overwatchUltValue = 0;

public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render() const;
	void HandleEvents(SDL_Event event);

	//ui specific functions
	void toggleShop();
	void enableUlt();
	void useUlt();

	//ui managment
	//TODO: make this independent from the scene
	//void changeUI(const char* uiName);

};

#endif

