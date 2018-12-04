#include "Scene01.h"
#include "Body.h"
#include <iostream>

using namespace MATH;

Scene01::Scene01(SDL_Window* sdlWindow_)
{
	window = sdlWindow_;
	elapsedTime = 0.0f;

	//Initialize Multiple Bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		blocks[i] = nullptr;
	}
	ball = nullptr;
}

Scene01::~Scene01()
{
	OnDestroy();
}

bool Scene01::OnCreate() {
	int w, h;
	posX = -200.0f;
	posY = -300.0f;

	SDL_GetWindowSize(window, &w, &h);
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-400.0f, 400.0f, -400.0f, 400.0f, 0.0f, 1.0f);
	ball = new Body("images/SphereBlueS.bmp", Vec3(0.0f, -250.0f, 0.0f));
	blocks[0] = new Body("images/player.png", Vec3(posX, posY, 0.0f));//Player block
	blocks[1] = new Body("images/blockH.png", Vec3(-200.0f, 350.0f, 0.0f));//Top
	blocks[2] = new Body("images/blockV.png", Vec3(-300.0f, 400.0f, 0.0f));//Left
	blocks[3] = new Body("images/blockV.png", Vec3(200.0f, 400.0f, 0.0f));//Right

	//Multiple bodies check if null
	if (ball == nullptr) return false;

	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		if (blocks[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Scene01::OnDestroy() {
	//Delete ball ptr
	if (ball) {
		delete ball;
	}
	ball = nullptr;

	//Delete blocks[] ptr
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		if (blocks[i]) {
			delete blocks[i];
			blocks[i] = nullptr;
		}
	}

}

void Scene01::Update(const float time_) {
	ball->Update(time_);

	for (int i = 0; i < NUM_BODIES; i++) {
		blocks[i]->Update(time_);
		collider.detectCollision(*ball, *blocks[i]);
		  
		/*
		//For testing, delete later
		if (collider.detectCollision(*ball, *blocks[i])) {
			//std::cout << "Collided" << std::endl;
		}
		else {
			//std::cout << "No Collision" << std::endl;
		}
		*/
	}

}

void Scene01::Render() {
	SDL_Rect imageRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	//Clear the screen
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	
	//Render ball (write a subclass of render later...)
	Vec3 screenCoords = projectionMatrix * ball->pos;

	imageRectangle.h = ball->getImage()->h;
	imageRectangle.w = ball->getImage()->w;
	imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning (int = float)
	imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_BlitSurface(ball->getImage(), nullptr, screenSurface, &imageRectangle);

	//Render blocks
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies

		Vec3 screenCoords = projectionMatrix * blocks[i]->pos;

		imageRectangle.h = blocks[i]->getImage()->h;
		imageRectangle.w = blocks[i]->getImage()->w;
		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning (int = float)
		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

		SDL_BlitSurface(blocks[i]->getImage(), nullptr, screenSurface, &imageRectangle);
	}
	//Go draw
	SDL_UpdateWindowSurface(window);
}

void Scene01::HandleEvents(const SDL_Event &event) {
	
	//Button Event
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			//Move the Star
		case SDLK_RIGHT:
			posX+= 10.0f;
			blocks[0]->SetPosition(Vec3(posX, posY, 0.0f));
			break;

		case SDLK_LEFT:
			posX-= 10.0f;
			blocks[0]->SetPosition(Vec3(posX, posY, 0.0f));
			break;

		case SDLK_UP:
			posY += 10.f;
			blocks[0]->SetPosition(Vec3(posX, posY, 0.0f));
			break;

		case SDLK_DOWN:
			posY -= 10.f;
			blocks[0]->SetPosition(Vec3(posX, posY, 0.0f));
			break;

		case SDLK_SPACE:
			//Remember mass is not set for either bodies...so don't use applyforce
			velTest += 500.0f; 
			ball->SetVelocity(Vec3(100.0f, velTest, 0.0f));
			break;
		}
	}
	
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			//move = 0.0f;
			break;

		case SDLK_LEFT:
			//move = 0.0f;
			break;
		
		}
	}

}
