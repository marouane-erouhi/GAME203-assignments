#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "UIElement.h"

class TextUIElement : public UIElement {
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	std::string text;
	int pointSize = 32;
	const char* fontName = "OpenSans-Regular.ttf";

public:
	TextUIElement(const char* id,const char* text, SDL_Renderer* renderer, MATH::Vec3 pos);
	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	bool pointInside(MATH::Vec3 point) { return false; }

	void setText(std::string newText);
	void setFontSize(int x);
	void setColor(SDL_Color newColor);
	void setSize(int newSize);
};