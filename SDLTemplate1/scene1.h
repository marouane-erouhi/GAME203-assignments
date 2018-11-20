#ifndef SCENE1_H
#define SCENE1_H
#include "MMath.h"

#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "UIManager.h"

#include <unordered_map>

#include "EmptyObject.h"
#include "ImageRenderer2dComponent.h"

#include "JSONFileLoader.h"
class scene1 : public Scene {
private:
	SDL_Window *window;
	MATH::Matrix4 projectionMatrix;
	SDL_Renderer * renderer;

	UIContainer* currentUI;

	std::vector<GameObject*> gameObjects;
	
public:
	scene1(SDL_Window* sdlWindow);
	~scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render() const;
	void HandleEvents(SDL_Event event);

private:
	//helper functions
	/// Takes a gameobject and a component and links them up
	GameObject* AddComponent(GameObject* object, int componentCount, ...);
};

#endif