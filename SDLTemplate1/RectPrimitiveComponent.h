#pragma once

#include "ObjectComponent.h"
#include <SDL.h>
#include "GameObject.h"

class RectPrimitiveComponent : public ObjectComponent{
private:
	float w, h;
	SDL_Color color;

	SDL_Renderer* renderer;
	MATH::Vec3 screenCoords;
public:

	RectPrimitiveComponent(GameObject * parent_, float w_, float h_, SDL_Color color_, SDL_Renderer* renderer_);

	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	void setParent(GameObject* parent_);
	void setActive(bool active_);

	void setColor(SDL_Color color_);
	void setDimentions(float w_, float h_);
};