#pragma once
#include "UIContainer.h"
#include <SDL.h>

class UIManager {
private:
	static UIManager * instance;
	UIContainer* currentUI;
	UIManager();
public:
	static UIManager* getInstance();

	UIContainer* getUI();
	bool setUI(const char * uiName, SDL_Renderer* renderer);
};

