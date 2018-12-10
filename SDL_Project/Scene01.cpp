#include "Scene01.h"
#include "Body.h"
#include <iostream>
#include <algorithm>

using namespace MATH;

Scene01::Scene01(SDL_Window* sdlWindow_, const int screenWidth_, const int screenHeight_)
{
	window = sdlWindow_;
	elapsedTime = 0.0f;

	screenWidth = screenWidth_;
	screenHeight = screenHeight_;

	//Initialize Multiple Bodies
	player.reset(nullptr);

}

Scene01::~Scene01()
{
	OnDestroy();
}

bool Scene01::OnCreate() {
	int w, h;

	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	ballDirection = MATH::Vec3(1.0,1.0,0);//diangnol to the right
	ballSpeed = defaultBallSpeed;
	
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
	//ball.reset(new Body("images/SphereBlueS.bmp", ballPosition, 2));//Ball
	balls.push_back(new Body("images/SphereBlueS.bmp", ballPosition, 2));//default ball
	player.reset(new Body("images/player.png", playerPosition, 1));//Player block


	//Border initialize
	border.push_back(new Body("images/blockH.png", Vec3(-200.0f, 350.0f, 0.0f), 3));//Top Bound
	border.push_back(new Body("images/blockV.png", Vec3(-300.0f, 400.0f, 0.0f), 3));//Left Bound
	border.push_back(new Body("images/blockV.png", Vec3(200.0f, 400.0f, 0.0f), 3));//Right Bound

	//test scene
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			blocks.push_back(new Body("images/SphereBlueS.bmp", Vec3(-30 * i, -30*j, 0.0), 4));
		}
		for (int i = 0; i < 5; i++) {
			blocks.push_back(new Body("images/SphereBlueS.bmp", Vec3((30 * i) + 30, -30*j, 0.0), 4));
		}
	}

	//Multiple bodies check if null
	//if (ball == nullptr) return false;
	if (player == nullptr) return false;
	if (border.empty()) return false;

	return true;
}

void Scene01::OnDestroy() {

	if (border.size() > 0) {
		for (auto item : border) {
			if (item) delete item;
			item = nullptr;
		}
	}

	for (auto ball : balls) {
		delete ball;
	}
	
	border.clear();
	border.shrink_to_fit();

	blocks.clear();
	blocks.shrink_to_fit();

}

void Scene01::Update(const float time_) {
	elapsedTime += time_;

	if (isLaunched) {
		//increase ball speed by 20% every 10s
		resetTimer += time_;
		if (resetTimer >= 5.0f) {
			changeGameSpeed();
			std::cout << "game is faster now\n";
			resetTimer = 0.0f;
		}
	}



	if (balls.size() <= 0) {
		std::cout << "you lose\n";

		if (lives <= 0) {
			//switch to losing screen
			// TODO: add this functionality
		}
		else {//more lives
			resetGameSpeed();//reset game speed
			lives--;//decrement lives
			//spawn a new ball
			spawnBall();
			isLaunched = false;
		}
	}


	//update player and balls
	player->Update(time_);
	for (int i = 0; i < balls.size();i++) {
		//kill ball when it goes out of bounds
		if (!balls.at(i)->isAlive()) {
			balls.erase(balls.begin() + i);
			continue;
		}
		balls.at(i)->Update(time_);
	}
	
	//detect collision between balls and player
	for (auto ball : balls)	Collider::detectCollision(*ball, *player);

	//Updating border? This is primarily used to detect collision between player/ball with borders
	//detect collision between balls, player and borders
	for (int i = 0; i < border.size(); i++) {
		border.at(i)->Update(time_);
		for (auto ball : balls)	Collider::detectCollision(*ball, *border.at(i));
		Collider::detectCollision(*player, *border.at(i));
	}
	//update blocks
	for (int i = 0; i < blocks.size();i++) {
		//get rid of blocks that have been killed off
		if (!blocks.at(i)->isAlive()) {
			blocks.erase(blocks.begin()+i);
			continue;
		}
		blocks.at(i)->Update(time_);

		//check coll between each ball and block
		for (auto ball : balls)	Collider::detectCollision(*ball, *blocks.at(i));
	}

	//Quick functionality to drag the ball initially
	if (!isLaunched) {
		for (auto ball : balls) {
			ball->SetVelocity(Vec3(player->GetVelocity().x, 0.0f, 0.0f));
		}
		ballInitialVelocity.x = player->GetVelocity().x;
	}
}

void Scene01::Render() {
	SDL_Rect imageRectangle;

	auto color = SDL_Color();
	color.r = 255;	color.g = 255;	color.b = 255; color.a = 255;
	SDL_SetRenderDrawColor(screenRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(screenRenderer);//clear screen

	//Render ball & player
	for (auto ball : balls) {
		ball->Render(projectionMatrix, screenRenderer);
	}
	player->Render(projectionMatrix, screenRenderer);

	//Render blocks
	for (int i = 0; i < border.size(); i++) {
		border.at(i)->Render(projectionMatrix, screenRenderer);
	}
	for (auto block : blocks) {
		block->Render(projectionMatrix, screenRenderer);
	}

	//Go draw
	SDL_RenderPresent(screenRenderer);
}

//Support function to render bodies
//void Scene01::SubRender(SDL_Rect& imageRectangle_, SDL_Surface* screenSurface_, Body& body_) {
//	Vec3 screenCoords = projectionMatrix * body_.pos;
//
//	imageRectangle_.h = body_.getImage()->h;
//	imageRectangle_.w = body_.getImage()->w;
//	imageRectangle_.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning (int = float)
//	imageRectangle_.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
//
//	SDL_BlitSurface(body_.getImage(), nullptr, screenSurface_, &imageRectangle_);
//}

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
		{
			spawnBall();
			break;
		}
		case SDLK_DOWN://Arrow Down
			resetGameSpeed();
			break;

		case SDLK_SPACE:
			if (!isLaunched) {
				for (auto ball : balls) {
					ball->SetVelocity(Vec3(ballDirection * ballSpeed));
				}
				
				isLaunched = true;
			}
			changeGameSpeed();
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
			std::cout << "KEYUP" << std::endl;//For Debugging
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

void Scene01::spawnBall() {
	auto playerLocation = player->GetPos();

	auto t = new Body("images/SphereBlueS.bmp", MATH::Vec3(playerLocation.x+(player->GetLength()/2), -270.0f, 0.0f), 2);
	t->SetVelocity(ballDirection*ballSpeed);
	t->SetColor(220,60,150,255);
	balls.push_back(t);
}

void Scene01::changeGameSpeed() {
	ballSpeed *= 1.2f;//increase speed of all by 20%
	for (auto ball : balls) {
		auto t = ball->GetVelocity();
		if (t.x == 0.0 && t.y == 0.0f)	continue;
		t = VMath::normalize(t);
		t = t*ballSpeed;//get direction vector and multiply it by ballSpeed
		ball->SetVelocity(t);
	}
}

void Scene01::resetGameSpeed() {
	ballSpeed = defaultBallSpeed;
}
