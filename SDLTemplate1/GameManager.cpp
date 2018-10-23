#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "scene1.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;

/// In this OnCreate() method, fuction, subroutine, whatever the word you wish.
/// Its purpose is to act somewhat like a constructor except that it return a bool 
/// If it cannot create the required resources it cleans up after its self and returns
/// a false - Gameover
bool GameManager::OnCreate() {
	
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ptr == nullptr) {
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	//currentScene = new scene1(ptr->GetSDL_Window());
	currentScene = new Scene0(ptr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	timer->Start();
	while (isRunning) {
		timer->UpdateFrameTicks();
		HandleEvents();

		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(FPS)); ///Usually around 60 frames per sec
	}
}

void GameManager::HandleEvents() {
	//do game events here

	while (SDL_PollEvent(&currentEvent)) {
		switch (currentEvent.type) {
		case SDL_QUIT://X window button
			this->isRunning = false;
			break;
		case SDL_KEYDOWN:
			/*switch (currentEvent.key.keysym.sym) {

			}*/
			break;
		}
		currentScene->HandleEvents(currentEvent);//handle scene events last
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}