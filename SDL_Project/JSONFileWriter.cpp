#include "JSONFileWriter.h"

void JSONFileWriter::SaveToJson(std::vector<Body*>& blocks_, const char* fileName_) {
	json j;
	j["blocks"] = json::array();
	json bl = j["blocks"];//for ease of use

	for (int i = 0; i < blocks_.size(); i++){
		j["blocks"][i]["pos"] = encodeVec3(blocks_.at(i)->GetPos());//pos
		j["blocks"][i]["dimentions"] = encodeVec3( Vec3(blocks_.at(i)->GetLength(), blocks_.at(i)->GetWidth(), 0.0f) );//dimentions
		j["blocks"][i]["color"] = encodeColor(blocks_.at(i)->GetColor());//color
	}

	//write to file
	ofstream myfile;
	myfile.open(fileName_);
	myfile << j;
	myfile.close();

	cout << "File saved as " << fileName_ << endl;
}

		

json JSONFileWriter::encodeVec3(Vec3 vec_) {
	json j;
	j["x"] = vec_.x;
	j["y"] = vec_.y;
	j["z"] = vec_.z;
	return j;
}

json JSONFileWriter::encodeColor(SDL_Color color_) {
	json j;
	j["r"] = color_.r;
	j["g"] = color_.g;
	j["b"] = color_.b;
	j["a"] = color_.a;
	return j;
}
