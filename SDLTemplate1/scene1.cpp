#include "scene1.h"
#include <SDL.h>
#include "JSONFileLoader.h"
scene1::scene1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;

}

scene1::~scene1() {}

bool scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	projectionMatrix = MATH::MMath::viewportNDC(w, h) *
		MATH::MMath::orthographic(-5.0f, 5.0f,
			-5.0f, 5.0f,
			0.0f, 1.0f);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	currentUI = new UIContainer();
	JSONFileLoader::loadUIFromFile(currentUI, renderer, "testui.json");

	return true;
}

void scene1::OnDestroy() {}

void scene1::Update(const float time) {

}


void scene1::Render() const {
	SDL_RenderClear(renderer);//clear screen
	/// Draw here

	currentUI->Render(projectionMatrix);
	SDL_RenderPresent(renderer);
}

void scene1::HandleEvents(SDL_Event event) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		std::cout << "mouse click" << std::endl;
		break;
	}
}