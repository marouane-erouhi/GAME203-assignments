#include "Scene01.h"
#include "Body.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include "JSONFileLoader.h"
#include "JSONFileWriter.h"

using namespace std;
using namespace MATH;

Scene01::Scene01(SDL_Window* sdlWindow_, const int screenWidth_, const int screenHeight_)
{
	window = sdlWindow_;
	elapsedTime = 0.0f;

	screenWidth = screenWidth_;
	screenHeight = screenHeight_;

	//Initialize Multiple Bodies
	pin.reset(nullptr);

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
	//TODO: ball is rendering as a rect
	balls.push_back(new Body(ballPosition, BodyTypes::Ball, 15, {0,0,200,150}));//default ball
	//pin.reset(new Body("images/pin.png", playerPosition, 1));//Player block
	pin.reset(
		new Body(playerPosition, BodyTypes::Player, 150, 30, {100,0,100,255})
	);//Player block


	//Border initialize
	border.push_back(new Body(Vec3(-400, 350, 0), BodyTypes::Border, 800, 50, {100,100,55,255}));//Top Bound
	border.push_back(new Body(Vec3(-400, 350, 0), BodyTypes::Border, 50, 800, { 100,100,55,255 }));//Left Bound
	border.push_back(new Body(Vec3(350, 350, 0), BodyTypes::Border, 50, 800, { 100,100,55,255 }));//Right Bound

	//test scene
	/*for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			blocks.push_back(new Body(Vec3(-30 * i, -30 * j, 0.0), BodyTypes::Breakable_Block, 20, 20, {10,150,200,255}));
		}
		for (int i = 0; i < 5; i++) {
			blocks.push_back(new Body(Vec3((30 * i) + 30, -30 * j, 0.0), BodyTypes::Breakable_Block, 20, 20, { 150,10,200,255 }));
		}
	}*/

	//use file loader to load lvl
	JSONFileLoader::loadLevelFromFile(blocks, screenRenderer, "levels/testBlockLevel.json");


	//init ui
	UIManager::getInstance()->setUI("blockBreakerUI", screenRenderer);

	//Multiple bodies check if null
	//if (ball == nullptr) return false;
	if (pin == nullptr) return false;
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
		std::cout << "You died, ty again...\n";

		if (lives <= 0) {
			std::cout << "you lose\n";
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


	//update pin and balls
	pin->Update(time_);
	for (int i = 0; i < balls.size();i++) {
		//kill ball when it goes out of bounds
		if (!balls.at(i)->isAlive()) {
			balls.erase(balls.begin() + i);
			continue;
		}
		balls.at(i)->Update(time_);
	}
	
	//detect collision between balls and pin
	for (auto ball : balls)	Collider::detectCollision(*ball, *pin);

	//detect collision between balls
	for (auto ball : balls) {
		for (auto ball1 : balls) {
			Collider::detectCollision(*ball, *ball1);
		}
	}

	//Updating border? This is primarily used to detect collision between pin/ball with borders
	//detect collision between balls, pin and borders
	for (int i = 0; i < border.size(); i++) {
		border.at(i)->Update(time_);
		for (auto ball : balls)	Collider::detectCollision(*ball, *border.at(i));
		Collider::detectCollision(*pin, *border.at(i));
	}
	//update blocks
	for (int i = 0; i < blocks.size();i++) {
		//get rid of blocks that have been killed off
		if (!blocks.at(i)->isAlive()) {
			blocks.erase(blocks.begin()+i);
			scoreValue += 100;
			continue;
		}
		blocks.at(i)->Update(time_);

		//check coll between each ball and block
		for (auto ball : balls)	Collider::detectCollision(*ball, *blocks.at(i));
	}

	//update ui ****************************************
	std::string scoreText = "Score: ";
	scoreText += std::to_string(scoreValue);

	std::string livesText = "Lives: ";
	livesText += std::to_string(lives);

	//set ui data
	((TextUIElement*)(UIManager::getInstance()->getUI()->getElement("scoreText")))->setText(scoreText);
	((TextUIElement*)(UIManager::getInstance()->getUI()->getElement("livesText")))->setText(livesText);


	//Quick functionality to drag the ball initially
	if (!isLaunched) {
		for (auto ball : balls) {
			ball->SetVelocity(Vec3(pin->GetVelocity().x, 0.0f, 0.0f));
			//ball->SetVelocity();
		}
		ballInitialVelocity.x = pin->GetVelocity().x;
	}
}

void Scene01::Render() {
	SDL_Rect imageRectangle;

	auto color = SDL_Color();
	color.r = 255;	color.g = 255;	color.b = 255; color.a = 255;
	SDL_SetRenderDrawColor(screenRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(screenRenderer);//clear screen

	//Render ball & pin
	for (auto ball : balls) {
		ball->Render(projectionMatrix, screenRenderer);
	}
	pin->Render(projectionMatrix, screenRenderer);

	//Render blocks
	for (int i = 0; i < border.size(); i++) {
		border.at(i)->Render(projectionMatrix, screenRenderer);
	}
	for (auto block : blocks) {
		block->Render(projectionMatrix, screenRenderer);
	}

	//draw ui
	UIManager::getInstance()->getUI()->Render(projectionMatrix);

	//Go draw
	SDL_RenderPresent(screenRenderer);
}

//Handle pin inputs here
void Scene01::HandleEvents(const SDL_Event &event) {
	//Button Event
	if (event.type == SDL_KEYDOWN) {//If Key is pressed

		switch (event.key.keysym.sym) {
		case SDLK_RIGHT://Arrow Right
			pin->SetVelocity(Vec3(playerVelocity, 0.0f, 0.0f));
			break;

		case SDLK_LEFT://Arrow Left
			pin->SetVelocity(Vec3(-playerVelocity, 0.0f, 0.0f));
			break;

		case SDLK_UP://Arrow Up
		{
			spawnBall();
			break;
		}
		case SDLK_DOWN://Arrow Down
			resetGameSpeed();
			//safe current game
			JSONFileWriter::SaveToJson(blocks, "testLevel1.json");
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
	
	//KEYUP Event is not working for me so for now I opted for Collider to stop pin
	if (event.type == SDL_KEYUP) {//If key is released
		switch (event.key.keysym.sym) {
			std::cout << "KEYUP" << std::endl;//For Debugging
		case SDLK_RIGHT://Arrow Right
			playerVelocity = 0.0f;
			pin->SetVelocity(Vec3(playerVelocity, 0.0f, 0.0f));
			std::cout << "KEYUP" << std::endl;//For Debugging
			break;

		case SDLK_LEFT://Arrow Left
			playerVelocity = 0.0f;
			pin->SetVelocity(Vec3(playerVelocity, 0.0f, 0.0f));
			break;
		default:
			//std::cout << "DEFAULT" << std::endl;
			break;
		}
	}

}

void Scene01::spawnBall() {
	auto playerLocation = pin->GetPos();

	auto a = new Body(MATH::Vec3(playerLocation.x + (pin->GetLength() / 2), -270.0f, 0.0f), BodyTypes::Ball, 15, { 0,0,200,150 });
	a->SetVelocity(ballDirection*ballSpeed);
	a->SetColor(220, 60, 150, 255);
	balls.push_back(a);
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
