#pragma once
#include "UIContainer.h"
#include "json.hpp"
#include "Scene.h"

#include <vector>

#include "EmptyObject.h"
#include "ImageRenderer2dComponent.h"

using json = nlohmann::json;
class JSONFileLoader {

public:
	static void loadUIFromFile(UIContainer* ui, SDL_Renderer* renderer, const char* fileName);
	static void loadSceneFromFile(std::vector<GameObject*>& gameObjects, SDL_Renderer* renderer, const char* fileName);

	//helper functions
	static GameObject* parseGameObject(json& j, GameObject* parent_, SDL_Renderer* renderer_);
	static ObjectComponent* parseComponent(json& j, GameObject* parent_, SDL_Renderer* renderer_);
	static MATH::Vec3 parseVec3(json& j);
};