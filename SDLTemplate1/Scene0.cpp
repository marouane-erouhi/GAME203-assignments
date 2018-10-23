#include "Scene0.h"
#include <SDL.h>
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	
}

Scene0::~Scene0(){}

bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	projectionMatrix = MATH::MMath::viewportNDC(w, h) *
		MATH::MMath::orthographic(-5.0f, 5.0f,
			-5.0f, 5.0f,
			0.0f, 1.0f);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	UIManager::getInstance()->setUI("dota2ui", renderer);

	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float time) {

}
	

void Scene0::Render() const {
	SDL_RenderClear(renderer);//clear screen
	/// Draw here
	//currentUI->Render(projectionMatrix);
	UIManager::getInstance()->getUI()->Render(projectionMatrix);
	SDL_RenderPresent(renderer);
}

void Scene0::HandleEvents(SDL_Event event) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		std::cout << "mouse click" << std::endl;
		//setScore(++clickNum);
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case 's':
			toggleShop();
			break;
		case 'e':
			useUlt();
			break;
		case SDLK_SPACE:
			if (overwatchUltValue == 75) {
				enableUlt();
			}
			else {
				overwatchUltValue += 25;
				auto a = (TextUIElement*)UIManager::getInstance()->getUI()->getElement("ult_counter");
				if(a != nullptr)	a->setText(std::to_string(overwatchUltValue )+ "%");
			}
			break;
		case SDLK_F1:
			UIManager::getInstance()->setUI("dota2ui", renderer);
			break;
		case SDLK_F2:
			UIManager::getInstance()->setUI("overwatchui", renderer);
			break;
		}
		break;
	}
}

void Scene0::toggleShop() {
	auto temp = (ImageUIElement*)UIManager::getInstance()->getUI()->getElement("shop");
	if (temp != nullptr) {
		if (temp->Enabled()) {
			temp->disable();
		}
		else {
			temp->enable();
		}
	}
}

void Scene0::enableUlt() {
	auto a = UIManager::getInstance()->getUI()->getElement("ult_counter");
	if (a != nullptr)	a->disable();//disable the text
	auto b = UIManager::getInstance()->getUI()->getElement("ult_full");
	if(b != nullptr)	b->enable();//disable the text
}

void Scene0::useUlt() {
	overwatchUltValue = 0;

	auto a = (TextUIElement*)UIManager::getInstance()->getUI()->getElement("ult_counter");
	if (a != nullptr) {
		a->setText(std::to_string(overwatchUltValue) + "%");
		a->enable();
	}

	auto b = UIManager::getInstance()->getUI()->getElement("ult_full");
	if (b != nullptr) {
		b->disable();//enable the full ult image
	}
}