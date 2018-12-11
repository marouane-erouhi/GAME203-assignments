#include "JSONFileLoader.h"

void JSONFileLoader::loadLevelFromFile(std::vector<Body*>& blocks_, SDL_Renderer * renderer_, const char * fileName_) {
	// read a JSON file
	std::ifstream file(fileName_);
	json j;
	file >> j;

	//json playerData = j["player"]; //TODO: implement a player

	json blocksData = j["blocks"];

	ParseBlocks(blocks_, renderer_, blocksData);


}

void JSONFileLoader::ParseBlocks(std::vector<Body*>& blocks, SDL_Renderer * renderer, json& blocksData_) {
	int blocks_size = blocksData_.size();

	//clear lvl
	blocks.clear();


	for (int i = 0; i < blocks_size; i++) {
		blocks.push_back(
			ParseBlock(blocksData_[i], renderer)
		);
	}
}

Body * JSONFileLoader::ParseBlock(json & block_, SDL_Renderer * renderer_) {
	Vec3 pos = parseVec2(block_["pos"]);
	Vec3 dimentions = parseVec2(block_["dimentions"]);
	SDL_Color color = parseColor(block_["color"]);

	return new Body(pos, BodyTypes::Breakable_Block,dimentions.x, dimentions.y,color);
}

Vec3 JSONFileLoader::parseVec2(json& j) {
	return MATH::Vec3(
		j["x"].get<float>(),
		j["y"].get<float>(),
		0.0f
	);
}

SDL_Color JSONFileLoader::parseColor(json & j) {
	auto c = SDL_Color();
	c.r = j["r"].get<int>();
	c.g = j["g"].get<int>();
	c.b = j["b"].get<int>();
	c.a = j["a"].get<int>();
	return c;
}
