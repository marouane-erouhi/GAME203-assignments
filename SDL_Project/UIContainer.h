#pragma once
#include <unordered_map>
#include "UIElement.h"
#include <SDL.h>

#include "TextUIElement.h"

class UIContainer {
private:
	//holds all UI Elements
	std::unordered_map<std::string, UIElement*> m_elements;
public:
	UIContainer();
	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);
	//add and get an element
	bool AddElement(UIElement * newEll);
	UIElement * getElement(const char* id);

	//block breaker ui factroty
	static UIContainer* BlockBreakerUIFactory(SDL_Renderer * renderer_);
};