#include "ImageUIElement.h"
#include <iostream>

ImageUIElement::ImageUIElement(const char * id, const char * imageName, SDL_Renderer* renderer, MATH::Vec3 pos)
	: imageName(imageName), renderer(renderer)
{
	this->pos = pos;
	this->id = id;
	enabled = true;
}

void ImageUIElement::OnCreate() {
	texture = IMG_LoadTexture(renderer, imageName);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void ImageUIElement::OnDestroy() {
	SDL_DestroyTexture(texture);
}

void ImageUIElement::Render(MATH::Matrix4 projectionMatrix) {
	if (!enabled)	return;
	screenCoords = projectionMatrix * pos;

	SDL_Rect drawRect = SDL_Rect(); 
	drawRect.w = w;
	drawRect.h = h;
	drawRect.x = screenCoords.x - (drawRect.w / 2);	
	drawRect.y = screenCoords.y - (drawRect.h / 2);

	SDL_RenderCopy(renderer, texture, NULL, &drawRect);
}

void ImageUIElement::Update(float delta) {
}

//check if the point givent is inside this element
bool ImageUIElement::pointInside(MATH::Vec3 point) {
	/*
	boolean handelClick(float x, float y){
        if(x > this.x && x < this.x+this.w){
            if(y > this.y && y < this.y+this.h){
                return true;
            }
        }
        return false;
    }
	*/





	return false;
}
