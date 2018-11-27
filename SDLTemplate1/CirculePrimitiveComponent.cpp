#include "CirculePrimitiveComponent.h"

CirculePrimitiveComponent::CirculePrimitiveComponent(GameObject * parent_, float radius_, SDL_Color color_, SDL_Renderer * renderer_) {
	parent = parent_;
	color = color_;
	radius = radius_;
	renderer = renderer_;
	active = true;
}

void CirculePrimitiveComponent::OnCreate() {
}

void CirculePrimitiveComponent::OnDestroy() {
}

void CirculePrimitiveComponent::Render(MATH::Matrix4 projectionMatrix) {
	if (!active)	return;
	screenCoords = projectionMatrix * parent->getPos();

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);//set shape color
	//draw
	std::cout << "render\n";
	float ax= screenCoords.x+radius, ay= screenCoords.y;//thse will store the last point
	for (float i = 0; i < 2*M_PI; i+=2*M_PI/radius) {
		float x = screenCoords.x + (radius * cos(i));
		float y = screenCoords.y + (radius * sin(i));
		SDL_RenderDrawLine(renderer, ax, ay, x, y);
		ax = x;	ay = y;
	}
	SDL_RenderDrawLine(renderer, ax, ay, screenCoords.x + radius, screenCoords.y);
}

void CirculePrimitiveComponent::Update(float delta) {
}

void CirculePrimitiveComponent::setParent(GameObject * parent_) {
	parent = parent_;
}

void CirculePrimitiveComponent::setActive(bool active_) {
	active = active_;
}

void CirculePrimitiveComponent::setColor(SDL_Color color_) {
	color = color_;
}

void CirculePrimitiveComponent::setRadius(float radius_) {
	radius = radius_;
}
