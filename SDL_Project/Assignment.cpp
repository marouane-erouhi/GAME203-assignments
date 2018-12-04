#include "Assignment.h"
#include "Body.h"
#include <iostream>

using namespace MATH;

Assignment::Assignment(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	elapsedTime = 0.0f;
	
	//Multiple Bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = nullptr;
	}
}

Assignment::~Assignment(){
	OnDestroy();
}

bool Assignment::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	projectionMatrix = MMath::viewportNDC(w,h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f) ;
	//Position on the window
	bodies[0] = new Body("jetskiSmall.bmp", 1.0f, Vec3(0.0f, 11.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[1] = new Body("jetskiSmall.bmp", 1000.0f, Vec3(10.0f, 15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[2] = new Body("jetskiSmall.bmp", 1000.0f, Vec3(10.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}
///*
void Assignment::Update(const float time) {
	if (elapsedTime  < 5.0f) {
		bodies[0]->ApplyForce(Vec3(10.199f, -9.8f, 0.0f));
	}
	elapsedTime += time;
	
	//*
	if (elapsedTime < 3.0f) {
		/// Accelerate for three seconds
		std::cout << elapsedTime << "," << bodies[0]->pos.x << "," << bodies[0]->pos.y << std::endl;
	}
	if (bodies[0]->pos.y < 1.0f){//Ground
		bodies[0]->pos.y = 1.0f;
		bodies[0]->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
	}

	//*/
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		
		if (bodies[i]) bodies[i]->Update(time);
	}
}
//*/

void Assignment::Render() {
	SDL_Rect imageRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	//Clear the screen
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		
		Vec3 screenCoords = projectionMatrix * bodies[i]->pos;

		imageRectangle.h = bodies[i]->getImage()->h;
		imageRectangle.w = bodies[i]->getImage()->w;
		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

		SDL_BlitSurface(bodies[i]->getImage(), nullptr, screenSurface, &imageRectangle);
	}
	//Go draw
	SDL_UpdateWindowSurface(window);
}

void Assignment::HandleEvents(const SDL_Event& event) {
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT:
				bodies[i]->ApplyForce(Vec3(5000.0f, 0.0f, 0.0f));
				break;
			
			case SDLK_LEFT:
				bodies[i]->ApplyForce(Vec3(-5000.0f, 0.0f, 0.0f));
				break;
			
			 }
		}
	}
}