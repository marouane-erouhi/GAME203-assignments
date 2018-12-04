#include "Assignment3.h"
#include "BodyinSpace.h"
#include <SDL.h>
#include <iostream>

using namespace MATH;

//Current number of bodies is set to 30 (not including Star)
Assignment3::Assignment3(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;

	//Multiple Bodies set initial value to NULL
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = nullptr;
	}
}


Assignment3::~Assignment3() {
	OnDestroy();
}
//Pixel conversion 3.8/100 //Star is 60 x 58 pixels //Satellites are 20 x 19 pixels

//Star's variables
float massStar = 150.0f;
float radiusStar = 30.0f * (3.8f / 100.0f);
//Satellite's variables
float massBody;
float radiusSatellite = 10.0f * (3.8f / 100.0f);

bool Assignment3::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 30.0f, 0.0f, 1.0f);
	
	//Position on the window //Ratio: 100 pixels to 3.8f Window Units (3.8/100 conversion)
	//Instantiate and initialize the Star's variables //Star is 60 x 58 pixels //Satellites are 20 x 19 pixels
	bodies[0] = new BodyinSpace("SphereYellow.bmp", massStar, radiusStar, Vec3(14.0f, 16.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)); //14. 16
	
	//Instantiate and initialize the Satellites' variables
	for (int i = 1; i < NUM_BODIES; i++) {
		//Randomize Satellite's spawn position
		float xPosition = rand() % 25 + 2;
		float yPosition = rand() % 25 + 2;

		//To ensure that the Satellites doesn't spawn near the Star
		for (int i = 0; i < 1; i++) {
			if (xPosition > 14.0f && xPosition < 16.5f && yPosition > 15.0f && yPosition < 17.5f) {
				xPosition = rand() % 25 + 2;
				yPosition = rand() % 25 + 2;

				i = 0;
			}
		}
		
		//To ensure that the generated Satellites doesn't overlap each other
		prevBody += 1;
		for (int j = 0; j < prevBody; j++) {
			if (j > 1) {//Run if it's not the first Body/Star
				if (xPosition == bodies[j]->pos.x && yPosition == bodies[j]->pos.y) {
					xPosition = rand() % 28 + 1;
					yPosition = rand() % 28 + 1;
				}
			}
		}
		//Randomize Satellite's mass
		massBody = rand() % 50 + 10;

		bodies[i] = new BodyinSpace("SphereBlueS.bmp", massBody, radiusSatellite, Vec3(xPosition, yPosition, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}
	
	
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies set initial value to NULL
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment3::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies set value to NULL when destroyed
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}

void Assignment3::Update(const float time) {
	elapsedTime += time;
	
	detectCollision();
	
	if (elapsedTime < 0.1f) {
		initializeBodies();
	}
	else if (elapsedTime > 0.1f) {
		gravity();
	}
///*
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies

		if (bodies[i]) bodies[i]->Update(time);
	}
//*/
}
//Not used at the moment
float Assignment3::toRadian(float _degree) {
	return _degree * (M_PI/180.0f);
}
//Not used at the moment
float Assignment3::toDegree(float _radian) {
	return _radian * (180.0f / M_PI);
}

void Assignment3::initializeBodies() {
	//Initial Satellites' Velocity
	float initialVelX, initialVelY;
	//Adjust the magnitude of velocity in conjunction to distance from the Star
	float iVelXModifier = 10.0f;
	float iVelYModifier = 10.0f;

	for (int i = 1; i < NUM_BODIES; i++) {
		if (bodies[i]->pos.y > 16.0f) { //If Satellite is located to the North of the Star
			if (bodies[i]->pos.x > 14.0f) { //If Satellite is located to the North East of the Star
				initialVelY = iVelYModifier / (bodies[i]->pos.y - 16.0f);
				initialVelX = -1.0f * iVelXModifier / (bodies[i]->pos.x - 14.0f);
			}
			else if (bodies[i]->pos.x < 14.0f) { //If Satellite is located to the North West of the Star
				initialVelY = -1.0f * iVelYModifier / (bodies[i]->pos.y - 16.0f);
				initialVelX = -1.0f * iVelXModifier / (14.0f - bodies[i]->pos.x);
			}
		}
		else if (bodies[i]->pos.y < 16.0f) { //If Satellite is located to the South of the Star
			if (bodies[i]->pos.x > 14.0f) { //If Satellite is located to the South East of the Star
				initialVelY = iVelYModifier / (bodies[i]->pos.y - 16.0f);
				initialVelX = iVelXModifier / (bodies[i]->pos.x - 14.0f);
			}
			else if (bodies[i]->pos.x < 14.0f) { //If Satellite is located to the South West of the Star
				initialVelY = -1.0f * iVelYModifier / (bodies[i]->pos.y - 16.0f);
				initialVelX = iVelXModifier / (14.0f - bodies[i]->pos.x);
			}
		}
		//Limit the velocity of Satellites //Set initial max velocity
		float breakLimit = 20.0f;
		float speedLimit = 5.0f;
		if (initialVelY > breakLimit) {
			initialVelY = speedLimit;
		}
		else if (initialVelY < -1.0f * breakLimit) {
			initialVelY = -1.0f * speedLimit;
		}
		if (initialVelX > breakLimit) {
			initialVelX = speedLimit;
		}
		else if (initialVelX < -1.0f * breakLimit) {
			initialVelX = -1.0f * speedLimit;
		}
		bodies[i]->vel.y = initialVelY;
		bodies[i]->vel.x = initialVelX;
	}
}

void Assignment3::detectCollision() {//Detects collision between bodies and keep them from overlapping
	for (int i = 0; i < (NUM_BODIES - 1); i++) {
		for (int j = (i + 1); j < NUM_BODIES; j++) {
			
			//Adjusting the center of the origin of the image
			float posXBody1_Col = bodies[i]->pos.x + bodies[i]->radius;
			float posYBody1_Col = bodies[i]->pos.y - bodies[i]->radius;
			float posXBody2_Col = bodies[j]->pos.x + bodies[j]->radius;
			float posYBody2_Col = bodies[j]->pos.y - bodies[j]->radius;

			//COLLISION BETWEEN BODIES
			//Find the normal vector between the Bodies
			//Add or Subtract the radii to adjust for the center of the image (since normally the origin of the image is at the top right corner)
			float rX1Collide = posXBody1_Col - posXBody2_Col; //Vector X normal between Bodies
			float rY1Collide = posYBody1_Col - posYBody2_Col; //Vector Y normal between Bodies
			
			float rX2Collide = posXBody2_Col - posXBody1_Col; //Vector X normal between Bodies
			float rY2Collide = posYBody2_Col - posYBody1_Col; //Vector Y normal between Bodies

			//Normalize the normal vector
			//Magnitude will always return positive value (so only need one from either body)
			float magCollision = sqrt((rX1Collide * rX1Collide) + (rY1Collide * rY1Collide)); //This is the displacement magnitude (via pythagorean theory)	
			//Body 1
			rX1NormCollision = rX1Collide / magCollision;
			rY1NormCollision = rY1Collide / magCollision;
			//Body 2
			rX2NormCollision = rX2Collide / magCollision;
			rY2NormCollision = rY2Collide / magCollision;

			//*Combined Radius
			totalRadii = bodies[i]->radius + bodies[j]->radius;

			if (magCollision < totalRadii) {//If distance is less than radius = collision
				//*
				//Turn the displacement between bodies into positive values
				if (rX1Collide < 0.0f) {
					rX1Collide *= -1.0f;
				}
				if (rY1Collide < 0.0f) {
					rY1Collide *= -1.0f;
				}
				if (rX2Collide < 0.0f) {
					rX2Collide *= -1.0f;
				}
				if (rY2Collide < 0.0f) {
					rY2Collide *= -1.0f;
				}
				
				//*/
				float overlap = totalRadii - magCollision; //Find the overlap between bodies
				float angleCol = atan(rY2Collide / rX2Collide); //Find the angle between the 2 bodies (only need to do one since x & y has all been converted to positive)
				
				//Apply the displacement to push the bodies to outside of overlap
				float pushVelX1, pushVelY1, pushVelX2, pushVelY2;
				pushVelX1 = pushVelX2 = cos(angleCol) * overlap; //Push the body on the X-axis
				pushVelY1 = pushVelY2 = sin(angleCol) * overlap; //Push the body on the Y-axis

				//Readjust the direction of the push 
				if (posXBody2_Col < posXBody1_Col) {
					pushVelX2 *= -1.0f;
				}
				if (posYBody2_Col < posYBody1_Col) {
					pushVelY2 *= -1.0f;
				}
				if (posXBody1_Col < posXBody2_Col) {
					pushVelX1 *= -1.0f;
				}
				if (posYBody1_Col < posYBody2_Col) {
					pushVelY1 *= -1.0f;
				}

				//Push away overlap
				if (i != 0) {//If not the star
				bodies[i]->pos.x += pushVelX1;
				bodies[i]->pos.y += pushVelY1;
				}
				bodies[j]->pos.x += pushVelX2;
				bodies[j]->pos.y += pushVelY2;
				
				bodyCollided1 = i, bodyCollided2 = j; //Take this values and run them by calculateCollision()
				calculateCollision(); //Run collision here//Only activates if there is a collision
			}
			
		}
		
	}
	
	//*/

}
///*
void Assignment3::calculateCollision() {
	const float coeffRestitution = 1.0f; //Coefficient of restitution 
	
	//Takes the bodies' masses into variables
	float massBody1 = bodies[bodyCollided1]->mass;
	float massBody2 = bodies[bodyCollided2]->mass;

	//Find the projection in the direction of normal
	//Body 1
	float xi1VelNormal = bodies[bodyCollided1]->vel.x * rX1NormCollision; //Normalized initial velocity of the first body
	float yi1VelNormal = bodies[bodyCollided1]->vel.y * rY1NormCollision;
	//Body 2
	float xi2VelNormal = bodies[bodyCollided2]->vel.x * rX2NormCollision; //Normalized initial velocity of the second body
	float yi2VelNormal = bodies[bodyCollided2]->vel.y * rY2NormCollision;

	//Find the outgoing velocity (Combination equations of Conservation of Momentum & Velocity due to Coefficient of Restitution)
	//Body 1
	float xfVelBody1 = ((massBody1 - (coeffRestitution * massBody2)) * xi1VelNormal + (1.0f + coeffRestitution) * massBody2 * xi2VelNormal) / (massBody1 + massBody2);
	float yfVelBody1 = ((massBody1 - (coeffRestitution * massBody2)) * yi1VelNormal + (1.0f + coeffRestitution) * massBody2 * yi2VelNormal) / (massBody1 + massBody2);
	//Body 2
	float xfVelBody2 = ((massBody2 - (coeffRestitution * massBody1)) * xi2VelNormal + (1.0f + coeffRestitution) * massBody1 * xi1VelNormal) / (massBody1 + massBody2);
	float yfVelBody2 = ((massBody2 - (coeffRestitution * massBody1)) * yi2VelNormal + (1.0f + coeffRestitution) * massBody1 * yi1VelNormal) / (massBody1 + massBody2);
	//Body 1
	float xVelBody1 = bodies[bodyCollided1]->vel.x + (xfVelBody1 - xi1VelNormal) * rX1NormCollision;
	float yVelBody1 = bodies[bodyCollided1]->vel.y + (yfVelBody1 - yi1VelNormal) * rY1NormCollision;
	//Body 2
	float xVelBody2 = bodies[bodyCollided2]->vel.x + (xfVelBody2 - xi2VelNormal) * rX2NormCollision;
	float yVelBody2 = bodies[bodyCollided2]->vel.y + (yfVelBody2 - yi2VelNormal) * rY2NormCollision;
		
	//Assign collision Velocity
	if (bodyCollided1 != 0){//If not the Star
		//Body1
		bodies[bodyCollided1]->vel.x = xVelBody1;
		bodies[bodyCollided1]->vel.y = yVelBody1;
	}
		//Body2
		bodies[bodyCollided2]->vel.x = xVelBody2;
		bodies[bodyCollided2]->vel.y = yVelBody2;
}
//*/

void Assignment3::gravity() {//Calculate gravity between all Satellites to the Star

	float gravityConstant = 1.0f;

	//*
	for (int i = 1; i < NUM_BODIES; i++) {
		//r = Star position - Planet position 
		//Add or Subtract the radius to adjust for the image's center origin
		float rX1gravity = (bodies[0]->pos.x + radiusStar) - (bodies[i]->pos.x + radiusSatellite); //Vector X normal or displacement between Satellite and the Star
		float rY1gravity = (bodies[0]->pos.y - radiusStar) - (bodies[i]->pos.y - radiusSatellite); //Vector Y normal or displacement between Satellite and the Star

		float magnitudeGravity = sqrt((rX1gravity * rX1gravity) + (rY1gravity * rY1gravity)); //Magnitude

		float rX1NormalizedGravity = rX1gravity / magnitudeGravity; //Normalized X
		float rY1NormalizedGravity = rY1gravity / magnitudeGravity; //Normalized Y
		
		//Gravitation between Satellite and the Star 
		float gravityForceStar = (gravityConstant * bodies[i]->mass * massStar) / (magnitudeGravity * magnitudeGravity); //Law of Universal Gravitation

		float gravitationForceX1 = rX1NormalizedGravity * gravityForceStar + radiusStar; //Resulting gravitation in X
		float gravitationForceY1 = rY1NormalizedGravity * gravityForceStar - radiusStar; //Resulting gravitation in Y

		//Apply gravitation force
		
		//bodies[i]->ApplyForce(Vec3(gravitationForceX1, gravitationForceY1, 0.0f)); //No Limiter
		
		//With Limiter
		float gLimit = 500.0f;
		if (gravitationForceX1 < gLimit && gravitationForceX1 > -gLimit) {	
			if (gravitationForceY1 < gLimit && gravitationForceY1 > -gLimit) {
				bodies[i]->ApplyForce(Vec3(gravitationForceX1, gravitationForceY1, 0.0f));
			}
		}
	}
	//*/
	/*	
	for (int i = 0; i < NUM_BODIES; i++){
		for (int j = 0; j < NUM_BODIES; j++){
		//Add or Subtract the radius to adjust for the image's center origin
			
			//Body 1
			float rX1gravity = (bodies[i]->pos.x + bodies[i]->radius) - (bodies[j]->pos.x + bodies[j]->radius); //Vector X normal or displacement between Satellite and the Star
			float rY1gravity = (bodies[i]->pos.y - bodies[i]->radius) - (bodies[j]->pos.y - bodies[j]->radius); //Vector Y normal or displacement between Satellite and the Star

			float magnitudeGravity = sqrt((rX1gravity * rX1gravity) + (rY1gravity * rY1gravity)); //Magnitude

			float rX1NormalizedGravity = rX1gravity / magnitudeGravity; //Normalized X
			float rY1NormalizedGravity = rY1gravity / magnitudeGravity; //Normalized Y
		
			//Gravitation between Satellites
			float gravityForceStar1 = (gravityConstant * bodies[j]->mass * bodies[i]->mass) / (magnitudeGravity * magnitudeGravity); //Law of Universal Gravitation

			float gravitationForceX1 = rX1NormalizedGravity * gravityForceStar1 + bodies[i]->radius; //Resulting gravitation in X
			float gravitationForceY1 = rY1NormalizedGravity * gravityForceStar1 - bodies[i]->radius; //Resulting gravitation in Y

			//Apply gravitation force
		
			bodies[i]->ApplyForce(Vec3(gravitationForceX1, gravitationForceY1, 0.0f)); //No Limiter

			//Body 2
			float rX2gravity = (bodies[j]->pos.x + bodies[j]->radius) - (bodies[i]->pos.x + bodies[i]->radius); //Vector X normal or displacement between Satellite and the Star
			float rY2gravity = (bodies[j]->pos.y - bodies[j]->radius) - (bodies[i]->pos.y - bodies[i]->radius); //Vector Y normal or displacement between Satellite and the Star

			//float magnitudeGravity = sqrt((rX2gravity * rX2gravity) + (rY2gravity * rY2gravity)); //Magnitude (only need one since both are equal positive numbers)

			float rX2NormalizedGravity = rX2gravity / magnitudeGravity; //Normalized X
			float rY2NormalizedGravity = rY2gravity / magnitudeGravity; //Normalized Y

			//Gravitation between Satellites
			float gravityForceStar = (gravityConstant * bodies[i]->mass * bodies[j]->mass) / (magnitudeGravity * magnitudeGravity); //Law of Universal Gravitation

			float gravitationForceX2 = rX2NormalizedGravity * gravityForceStar + bodies[j]->radius; //Resulting gravitation in X
			float gravitationForceY2 = rY2NormalizedGravity * gravityForceStar - bodies[j]->radius; //Resulting gravitation in Y

			//Apply gravitation force

			bodies[j]->ApplyForce(Vec3(gravitationForceX2, gravitationForceY2, 0.0f)); //No Limiter
		
			//With Limiter
			float gLimit = 500.0f;
			if (gravitationForceX1 < gLimit && gravitationForceX1 > -gLimit) {	
				if (gravitationForceY1 < gLimit && gravitationForceY1 > -gLimit) {
					bodies[i]->ApplyForce(Vec3(gravitationForceX1, gravitationForceY1, 0.0f));
				}
			}
		}
	}
	//*/
	
}

void Assignment3::Render() {
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

void Assignment3::HandleEvents(const SDL_Event& event) {
	for (int i = 0; i < NUM_BODIES; i++) {//Multiple bodies
		//Experimental stuff
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			//Move the Star
			case SDLK_RIGHT:
				bodies[0]->ApplyForce(Vec3(5000.0f, 0.0f, 0.0f));
				break;

			case SDLK_LEFT:
				bodies[0]->ApplyForce(Vec3(-5000.0f, 0.0f, 0.0f));
				break;

			case SDLK_UP:
				bodies[0]->ApplyForce(Vec3(0.0f, 5000.0f, 0.0f));
				break;

			case SDLK_DOWN:
				bodies[0]->ApplyForce(Vec3(0.0f, -5000.0f, 0.0f));
				break;
			}
		}
	}
}