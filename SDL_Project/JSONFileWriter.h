#pragma once
#include "json.hpp"

#include "Body.h"
#include <vector>
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;
using namespace MATH;

class JSONFileWriter {
public:
	static void SaveToJson(std::vector<Body*>& blocks_, const char* fileName_);
private:
	static json encodeVec3(Vec3 vec_);
	static json encodeColor(SDL_Color color_);
};