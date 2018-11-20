#include "ResourceManager.h"
ResourceManager* ResourceManager::instance;

ResourceManager* ResourceManager::getInstance() {
	if (!instance)	instance = new ResourceManager();
	return instance;
}

SDL_Texture * ResourceManager::LoadImage(std::string imageName_, SDL_Renderer* renderer_) {
	SDL_Texture* image;

	//check if the image has already been loaded
	auto iterator = images.find(imageName_);


	if (iterator == images.end()) {
		//image not found
		image = IMG_LoadTexture(renderer_, imageName_.c_str());//load texture
		images.insert(std::pair <std::string, SDL_Texture*>(imageName_, image));//cache image
	}
	else {
		//image found in cache
		image = iterator->second;
	}

	return image;
}
