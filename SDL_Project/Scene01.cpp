#include "Scene01.h"
#include "Body.h"
#include <iostream>

using namespace MATH;

Scene01::Scene01(SDL_Window* sdlWindow_, const int screenWidth_, const int screenHeight_)
{
	window = sdlWindow_;
	elapsedTime = 0.0f;

	screenWidth = screenWidth_;
	screenHeight = screenHeight_;

	//Initialize Multiple Bodies
	ball.reset(nullptr);
	player.reset(nullptr);

}

Scene01::~Scene01()
{
	OnDestroy();
}

bool Scene01::OnCreate() {
	int w, h;
	
	//Variables to set screen grid and adjust units for calculations
	//In this case I set the SCREEN resolution to 800 x 800 so the grid goes from -400.0f to 400.0f
	const float gridX = screenWidth / 2; //Implicit int to float conversion
	const float gridY = screenHeight / 2; 
	
	//Variables to control inputs
	Vec3 playerPosition(-65.0f, -300.0f, 0.0f);
	Vec3 ballPosition(0.0f, -270.0f, 0.0f);
	playerVelocity = 300.0f;
	ballInitialVelocity.y = 500.0f;

	SDL_GetWindowSize(window, &w, &h);
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-gridX, gridX, -gridY, gridY, 0.0f, 1.0f);//Grid Units
	
	//Ball & Player initialize
	ball.reset(new Body("images/SphereBlueS.bmp", ballPosition, 2));//Ball
	player.reset(new Body("images/player.png", playerPosition, 1));//Player block
	
	//Border initialize
	border.push_back(new Body("images/blockH.png", Vec3(-200.0f, 350.0f, 0.0f), 3));//Top Bound
	border.push_back(new Body("images/blockV.png", Vec3(-300.0f, 400.0f, 0.0f), 3));//Left Bound
	border.push_back(new Body("images/blockV.png", Vec3(200.0f, 400.0f, 0.0f), 3));//Right Bound

	//Multiple bodies check if null
	if (ball == nullptr) return false;
	if (player == nullptr) return false;
	if (border.empty()) return false;

	return true;
}

void Scene01::OnDestroy() {

	//Delete std::vector<blocks*> 
	if (border.size() > 0) {
		for (auto item : border) {
			if (item) delete item;
			item = nullptr;
		}
	}
	
	border.clear();
	border.shrink_to_fit();

}

void Scene01::Update(const float time_) {
	
	ball->Update(time_);
	player->Update(time_);
	
	collider.detectCollision(*ball, *player);

	//Updating border? This is primarily used to detect collision between player/ball with borders
	for (int i = 0; i < border.size(); i++) {
		border.at(i)->Update(time_);
		collider.detectCollision(*ball, *border.at(i));
		collider.detectCollision(*player, *border.at(i));
	}

	//Quick functionality to drag the ball initially
	if (!isLaunched) {
		ball->SetVelocity(Vec3(player->GetVelocity().x, 0.0f, 0.0f));
		ballInitialVelocity.x = player->GetVelocity().x;
	}
}

void Scene01::Render() {
	SDL_Rect imageRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	
	//Clear the screen
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	
	//Render ball & player
	SubRender(imageRectangle, screenSurface, *ball);
	SubRender(imageRectangle, screenSurface, *player);

	//Render blocks
	for (int i = 0; i < border.size(); i++) {//Multiple bodies
		SubRender(imageRectangle, screenSurface, *border.at(i));
	}

	//Go draw
	SDL_UpdateWindowSurface(window);
}

//Support function to render bodies
void Scene01::SubRender(SDL_Rect& imageRectangle_, SDL_Surface* screenSurface_, Body& body_) {
	Vec3 screenCoords = projectionMatrix * body_.pos;

	imageRectangle_.h = body_.getImage()->h;
	imageRectangle_.w = body_.getImage()->w;
	imageRectangle_.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning (int = float)
	imageRectangle_.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_BlitSurface(body_.getImage(), nullptr, screenSurface_, &imageRectangle_);
}

//Handle player inputs here
void Scene01::HandleEvents(const SDL_Event &event) {
	//Button Event
	if (event.type == SDL_KEYDOWN) {//If Key is pressed

		switch (event.key.keysym.sym) {
		case SDLK_RIGHT://Arrow Right
			player->SetVelocity(Vec3(playerVelocity, 0.0f, 0.0f));
			break;

		case SDLK_LEFT://Arrow Left
			player->SetVelocity(Vec3(-playerVelocity, 0.0f, 0.0f));
			break;

		case SDLK_UP://Arrow Up
			break;

		case SDLK_DOWN://Arrow Down
			break;

		case SDLK_SPACE:
			if (!isLaunched) {
				ball->SetVelocity(Vec3(ballInitialVelocity.x, ballInitialVelocity.y, 0.0f));
				
				isLaunched = true;
			}
			break;
		}
	}
	//If mass is not set for either bodies, ApplyForce() won't work correctly
	//Acceleration is not really needed in Brick Break game//Unless power ups 
	
	//KEYUP Event is not working for me so for now I opted for Collider to stop player
	if (event.type == SDL_KEYUP) {//If key is released
		switch (event.key.keysym.sym) {
			std::cout << "KEYUP" << std::endl;//For Debugging
		case SDLK_RIGHT://Arrow Right
			playerVelocity = 0.0f;
			player->SetVelocity(Vec3(playerVelocity, 0.0f, 0.0f));
			break;

		case SDLK_LEFT://Arrow Left
			playerVelocity = 0.0f;
			player->SetVelocity(Vec3(playerVelocity, 0.0f, 0.0f));
			break;
		default:
			//std::cout << "DEFAULT" << std::endl;
			break;
		}
	}

}
