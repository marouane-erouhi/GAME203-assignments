#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene01.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, function, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;

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
	
	currentScene = new Scene01(ptr->GetSDL_Window(), screenWidth, screenHeight);
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

	SDL_Event event;

	timer->Start();
	while (isRunning) {
	///*
		if (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			//Close SDL window with and ESC key
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			
			//Closes the current window and open a new Assignment
			if (event.key.keysym.sym == SDLK_F1) {
				//Erase the content of the current scene
				currentScene->OnDestroy();
				delete currentScene;
				currentScene = nullptr;

				//Assign the currentScene to new Scene
				currentScene = new Scene01(ptr->GetSDL_Window(), screenWidth, screenHeight);
				currentScene->OnCreate();
			}
			
			currentScene->HandleEvents(event); 
			
			break;
			}
		}

		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}