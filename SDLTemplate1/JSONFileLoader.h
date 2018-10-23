#pragma once
#include "UIContainer.h"
#include "json.hpp"
#include "Scene.h"

class JSONFileLoader {

public:
	static void loadUIFromFile(UIContainer* ui, SDL_Renderer* renderer, const char* fileName);
};