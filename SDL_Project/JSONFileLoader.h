#pragma once
#include "json.hpp"
#include <vector>
#include <fstream>
#include "Vector.h"
#include "Body.h"

using json = nlohmann::json;
using namespace std;
using namespace MATH;

class JSONFileLoader {
public:
	static void loadLevelFromFile(std::vector<Body*>& blocks, SDL_Renderer* renderer, const char* fileName);
private:
	static void ParseBlocks(std::vector<Body*>& blocks, SDL_Renderer * renderer, json& blocksData_);
	//static void ParsePlayer();
	static Body* ParseBlock(json& block_, SDL_Renderer * renderer_);
	static Vec3 parseVec2(json& j);
	static SDL_Color parseColor(json& j);
};