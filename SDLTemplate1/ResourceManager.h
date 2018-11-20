#pragma once
/*
	This class will act as a simple cache for all loaded resources,
	it will also be responsible for loading all resources
*/
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

class ResourceManager {
private:
	ResourceManager() {}

	static ResourceManager* instance;

	std::unordered_map<std::string, SDL_Texture*> images; ///this holds all the images that have been loaded before
public:

	static ResourceManager* getInstance();

	SDL_Texture* LoadImage(std::string imageName_, SDL_Renderer* renderer_);


};