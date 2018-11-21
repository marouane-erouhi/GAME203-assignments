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
		MATH::MMath::orthographic(-10.0f, 10.0f,
			-10.0f, 10.0f,
			0.0f, 1.0f);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//default color
	color = SDL_Color();
	color.r = 255;	color.g = 255;	color.b = 255; color.a = 255;
	

	/*currentUI = new UIContainer();
	JSONFileLoader::loadUIFromFile(currentUI, renderer, "overwatchui.json");*/

	

	//JSONFileLoader::loadSceneFromFile(gameObjects, renderer, "scene2.json");


	//stress test the ResourceManager
	/*for (int i = 0; i < 100000; i++) {
		gameObjects.push_back(
			AddComponent(
				new EmptyObject(nullptr, "testImage1"+i, MATH::Vec3(2.0f+(i*0.01f))), 1,
				new ImageRenderer2dComponent(nullptr, "images/ball.png", renderer)
			));
	}*/

	SDL_Color c = SDL_Color();
	c.r = 255;	c.g = 0; c.b = 0; c.a = 0;

	gameObjects.push_back(
		AddComponent(
			new EmptyObject(nullptr, "testImage1", MATH::Vec3(2.0f + (0.01f))), 2,
			new ImageRenderer2dComponent(nullptr, "images/ball.png", renderer),
			new RectPrimitiveComponent(nullptr,200,200,c,renderer)
		));

	// Once setup is done, OnCreate all the things
	for (auto it : gameObjects) {
		it->OnCreate();
		it->print();
	}
	return true;
}

void scene1::OnDestroy() {
	for (auto it : gameObjects) {
		it->OnDestroy();
	}
}

void scene1::Update(const float time) {
	for (auto it : gameObjects) {
		it->Update(time);
	}
}


void scene1::Render() const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);//clear screen


	for (auto it : gameObjects) {
		it->Render(projectionMatrix);
	}

	SDL_Rect rect = SDL_Rect();

	rect.w = 500.0f;
	rect.h = 500.0f;
	rect.x = 100.0f;
	rect.y = 100.0f;

	//SDL_SetRenderDrawColor(renderer, 55, 155, 220, 255);
	//SDL_RenderFillRect(renderer,&rect);
	//SDL_SetRenderDrawColor(renderer, 0,0,0, 255);

	//currentUI->Render(projectionMatrix);
	SDL_RenderPresent(renderer);
}

void scene1::HandleEvents(SDL_Event event) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		//std::cout << "mouse click" << std::endl;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_F1:
			//JSONFileLoader::loadUIFromFile(currentUI, renderer, "dota2ui.json");
			JSONFileLoader::loadSceneFromFile(gameObjects, renderer, "testScene.json");
			break;
		case SDLK_F2:
			//JSONFileLoader::loadUIFromFile(currentUI, renderer, "overwatchui.json");
			JSONFileLoader::loadSceneFromFile(gameObjects, renderer, "scene2.json");
			break;
		}
	}
}

GameObject* scene1::AddComponent(GameObject * object, int componentCount, ...) {
	ObjectComponent* temp;

	va_list args;
	va_start(args, componentCount);

	for (int i = 0; i < componentCount; ++i) {
		std::cout << "i=" << i << "\t \n";
		temp = va_arg(args, ObjectComponent*);//get the curent component
		temp->setParent(object);//link up the parent
		object->AddComponent(temp);//add the component to the GameObject
		
	}

	return object;//return object for outside use
}
