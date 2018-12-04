#include "Assignment2.h"
#include "BodyinSpace.h"
#include <SDL_image.h>
#include  <iostream>

using namespace MATH;

Assignment2::Assignment2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;

	//Multiple Bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = nullptr;
	}
}

Assignment2::~Assignment2() {
	OnDestroy();
}
	//Set mass of bodies
	float massPlanet =  1.0f;
	float massStar1 = 100.0f;
	float massStar2 = 150.0f;
	float gConstant = 1.0f; //Gravitational constant
	float tmpRadius = 1.0f;

bool Assignment2::OnCreate() {
	int w, h;
	
	SDL_GetWindowSize(window, &w, &h);

	//IMG_Init(IMG_INIT_PNG); //Using SDL Image png

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-10.0f, 30.0f, -10.0f, 40.0f, 0.0f, 1.0f);
	//Position on the window, Initial Velocity, and Initial Acceleration
	bodies[0] = new BodyinSpace("SphereBlueS.bmp", massPlanet, tmpRadius, Vec3(10.0f, 20.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)); //Planet
	bodies[1] = new BodyinSpace("SphereYellowS.bmp", massStar1, tmpRadius, Vec3(5.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)); //Star 1
	bodies[2] = new BodyinSpace("SphereYellowS.bmp", massStar2, tmpRadius, Vec3(10.0f, 25.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)); //Star 2

	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment2::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		//IMG_Quit(); //Using SDL Image png
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}
///*
void Assignment2::Update(const float time) {
	elapsedTime += time;

	//Gravitation between planet and star 1
	//r = Star position - Planet position 
	float rX1 = bodies[1]->pos.x - bodies[0]->pos.x; //Vector X
 	float rY1 = bodies[1]->pos.y - bodies[0]->pos.y; //Vector Y

	float r1 = sqrt((rX1*rX1) + (rY1*rY1)); //Magnitude

	float rXnormalized1 = rX1 / r1; //Normalized X
	float rYnormalized1 = rY1 / r1; //Normalized Y

	float gravityForce1 = (gConstant * massPlanet * massStar1) / (r1*r1); //Law of Universal Gravitation

	float forceX1 = rXnormalized1 * gravityForce1; //Resulting gravitation in X
	float forceY1 = rYnormalized1 * gravityForce1; //Resulting gravitation in Y
	
	//Gravitation between planet and star 2
	float rX2 = bodies[2]->pos.x - bodies[0]->pos.x;
	float rY2 = bodies[2]->pos.y - bodies[0]->pos.y;
	float r2 = sqrt((rX2*rX2) + (rY2*rY2));

	float rXnormalized2 = rX2 / r2;
	float rYnormalized2 = rY2 / r2;

	float gravityForce2 = (gConstant * massPlanet * massStar2) / (r2*r2);

	float forceX2 = rXnormalized2 * gravityForce2;
	float forceY2 = rYnormalized2 * gravityForce2;

	//Total force
	float forceX = forceX1 + forceX2;
	float forceY = forceY1 + forceY2;

	if (elapsedTime < 0.5f) { //Initial force to throw planet into figure-8 orbit
		forceX += 12.5f;
		forceY += 2.75f;
	}
	
	//Apply total force 
	bodies[0]->ApplyForce(Vec3(forceX, forceY, 0.0f));

	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies

		if (bodies[i]) bodies[i]->Update(time);
	}
}
//*/

void Assignment2::Render() {
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

void Assignment2::HandleEvents(const SDL_Event& event) {
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT: //If right arrow key is pressed add force to the right
				bodies[i]->ApplyForce(Vec3(5000.0f, 0.0f, 0.0f));
				break;

			case SDLK_LEFT: //If left arrow key is pressed add force to the left
				bodies[i]->ApplyForce(Vec3(-5000.0f, 0.0f, 0.0f));
				break;
			case SDLK_UP: //If up arrow key is pressed add force to go up
				bodies[i]->ApplyForce(Vec3(0.0f, 5000.0f, 0.0f));
				break; 
			case SDLK_DOWN: //If down arrow key is pressed add force to go down
				bodies[i]->ApplyForce(Vec3(0.0f, -5000.0f, 0.0f));
				break;
			}
		}
	}
}