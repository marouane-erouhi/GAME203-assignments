#pragma once
#include "UIElement.h"

class ImageUIElement : public UIElement {
protected:
	const char * imageName;
	SDL_Texture * texture;
	int w, h;
	SDL_Renderer* renderer;
public:
	ImageUIElement(const char* id, const char* imageName, SDL_Renderer* renderer, MATH::Vec3 pos);
	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	bool pointInside(MATH::Vec3 point);
};
