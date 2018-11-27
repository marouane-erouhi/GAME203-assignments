#pragma once

#include "ObjectComponent.h"
#include "GameObject.h"
#include <SDL.h>
class CirculePrimitiveComponent : public ObjectComponent{
private:
	float radius;
	SDL_Color color;

	SDL_Renderer* renderer;
	MATH::Vec3 screenCoords;
public:

	CirculePrimitiveComponent(GameObject * parent_, float radius_, SDL_Color color_, SDL_Renderer* renderer_);

	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	void setParent(GameObject* parent_);
	void setActive(bool active_);

	void setColor(SDL_Color color_);
	void setRadius(float radius_);
};