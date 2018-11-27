#include "CirculePrimitiveComponent.h"

CirculePrimitiveComponent::CirculePrimitiveComponent(GameObject * parent_, float radius_, SDL_Color color_, SDL_Renderer * renderer_) {
	parent = parent_;
	color = color_;
	radius = radius_;
	renderer = renderer_;
}

void CirculePrimitiveComponent::OnCreate() {
}

void CirculePrimitiveComponent::OnDestroy() {
}

void CirculePrimitiveComponent::Render(MATH::Matrix4 projectionMatrix) {
	if (!active)	return;
	screenCoords = projectionMatrix * parent->getPos();

	std::cout << "circle render\n";

	//TODO: makes this better
	for (int i = 0; i < 360; i++) {
		float x = screenCoords.x + (radius * cos(i));
		float y = screenCoords.y + (radius * sin(i));
		SDL_RenderDrawPoint(renderer, x, y);
	}
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
