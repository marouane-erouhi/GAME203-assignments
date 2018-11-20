#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "ObjectComponent.h"

#include "Vector.h"
#include "Matrix.h"


#include "GameObject.h"

class ImageRenderer2dComponent : public ObjectComponent{
protected:
	//properties
	std::string imageName;
	int w, h;

	//SDL dependencies
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	//rendering
	MATH::Vec3 screenCoords;

public:
	ImageRenderer2dComponent(GameObject* parent_, std::string imageName_, SDL_Renderer* renderer_);

	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	void setParent(GameObject* parent_);
	void setActive(bool active_);
};