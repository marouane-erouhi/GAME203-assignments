#include "ImageRenderer2dComponent.h"
#include <iostream>

#include "ResourceManager.h"

ImageRenderer2dComponent::ImageRenderer2dComponent(GameObject * parent_, std::string imageName_, SDL_Renderer * renderer_) 
: imageName(imageName_), renderer(renderer_) {
	parent = parent_;
	active = true;
	type = ComponentType::Image;
}

void ImageRenderer2dComponent::OnCreate() {

	texture = ResourceManager::getInstance()->LoadImage(imageName, renderer);

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void ImageRenderer2dComponent::OnDestroy() {
	SDL_DestroyTexture(texture);
}

void ImageRenderer2dComponent::Render(MATH::Matrix4 projectionMatrix) {
	if (!active)	return;
	screenCoords = projectionMatrix * parent->getPos();


	SDL_Rect drawRect = SDL_Rect();
	drawRect.w = w;
	drawRect.h = h;
	drawRect.x = (int) (screenCoords.x - (drawRect.w / 2));
	drawRect.y = (int) (screenCoords.y - (drawRect.h / 2));
	SDL_RenderCopy(renderer, texture, NULL, &drawRect);
}

void ImageRenderer2dComponent::Update(float delta) {
	if (parent == nullptr)	std::cout << "ERR -- parent cannot be nullptr!\n";

}

void ImageRenderer2dComponent::setParent(GameObject* parent_) {
	parent = parent_;
}

void ImageRenderer2dComponent::setActive(bool active_) {
	active = active_;
}
