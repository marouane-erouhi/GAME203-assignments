#pragma once
#include <unordered_map>
#include "UIElement.h"
#include <SDL.h>

#include "ImageUIElement.h"
#include "TextUIElement.h"

class UIContainer {
private:
	std::unordered_map<std::string, UIElement*> m_elements;
public:
	UIContainer();
	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	bool AddElement(UIElement * newEll);

	UIElement * getElement(const char* id);
	void HandleEvents(SDL_Event event);

	//factories
	static UIContainer* Dota2UIFactory(SDL_Renderer* renderer);
	static UIContainer* OverwatchUIFactory(SDL_Renderer* renderer);
};