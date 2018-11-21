#include "RectPrimitiveComponent.h"

RectPrimitiveComponent::RectPrimitiveComponent(GameObject * parent_, float w_, float h_, SDL_Color color_, SDL_Renderer * renderer_)
: renderer(renderer_){
	active = true;
	parent = parent_;
	w = w_;
	h = h_;
	color = color_;
}

void RectPrimitiveComponent::OnCreate() {
}

void RectPrimitiveComponent::OnDestroy() {
}

void RectPrimitiveComponent::Render(MATH::Matrix4 projectionMatrix) {
	if (!active)	return;
	screenCoords = projectionMatrix * parent->getPos();


	SDL_Rect drawRect = SDL_Rect();
	drawRect.w = (int) w;
	drawRect.h = (int) h;
	drawRect.x = (int)(screenCoords.x - (drawRect.w / 2));
	drawRect.y = (int)(screenCoords.y - (drawRect.h / 2));

	//SDL_Color originalColor;//add this to the gamemanager to get the color eatch time I need to draw

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);//set shape color
	SDL_RenderFillRect(renderer, &drawRect);//draw
	//SDL_SetRenderDrawColor(renderer, 55, 155, 220, 255);//set to original color
}

void RectPrimitiveComponent::Update(float delta) {
}

void RectPrimitiveComponent::setParent(GameObject * parent_) {
	parent = parent_;
}

void RectPrimitiveComponent::setActive(bool active_) {
	active = active_;
}

void RectPrimitiveComponent::setColor(SDL_Color color_) {
	color = color_;
}

void RectPrimitiveComponent::setDimentions(float w_, float h_) {
	w = w_;
	h = h_;
}
