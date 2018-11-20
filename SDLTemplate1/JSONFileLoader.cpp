#include "JSONFileLoader.h"
#include <iostream>
#include <fstream>

#include "ImageUIElement.h"
#include "TextUIElement.h"

using json = nlohmann::json;
using namespace std;
void JSONFileLoader::loadUIFromFile(UIContainer* ui, SDL_Renderer* renderer, const char * fileName) {
	// read a JSON file
	std::ifstream file(fileName);
	json j;
	file >> j;
	j = j["elements"];//reassign it to point to the elements array
	//std::cout << j.dump(4) << std::endl;//print the whole object - formated

	//clear the ui object
	ui->OnDestroy();

	int arraySize = j.size();

	//j[i] - each element object
	for (int i = 0; i < arraySize; i++) {
		if (j[i]["type"] == "ImageEllement") {
			string imageName = j[i]["imageName"].get<string>();
			string imageid = j[i]["id"].get<string>();

			ImageUIElement* temp = new ImageUIElement(
				imageid.c_str(),
				imageName.c_str(),
				renderer, 
				MATH::Vec3(
					j[i]["pos"]["x"].get<float>(),
					j[i]["pos"]["y"].get<float>(),
					j[i]["pos"]["z"].get<float>()
				));
			//temp->setEnable(j[i]["enabled"].get<bool>());
			ui->AddElement(temp);
			temp = nullptr;
		}
		else if (j[i]["type"] == "textEllement") {
			cout << "text" << endl;

			auto text = j[i]["text"].get<string>();
			auto id = j[i]["id"].get<string>();

			auto temp = new TextUIElement(
				id.c_str(),
				text.c_str(),
				renderer,
				MATH::Vec3(
					j[i]["pos"]["x"].get<float>(),
					j[i]["pos"]["y"].get<float>(),
					j[i]["pos"]["z"].get<float>()
				));
			temp->setSize(j[i]["size"].get<int>());
			temp->setEnable(j[i]["enabled"].get<bool>());
			ui->AddElement(temp);
		}
		else {
			cout << "unknown object found" << endl;
		}

	}

}

void JSONFileLoader::loadSceneFromFile(std::vector<GameObject*>& gameObjects, SDL_Renderer * renderer, const char * fileName) {
	// read a JSON file
	std::ifstream file(fileName);
	json j;
	file >> j;
	j = j["GameObjects"];//reassign it to point to the elements array


	//std::cout <<
	//clean up first
	/*for (auto a : gameObjects) {
		a->OnDestroy();
	}*/
	gameObjects.clear();

	int arraySize = j.size();

	//j[i] - each element object
	for (int i = 0; i < arraySize; i++) {

		gameObjects.push_back(parseGameObject(j[i], nullptr, renderer));

	}
}

GameObject * JSONFileLoader::parseGameObject(json & j, GameObject* parent_, SDL_Renderer* renderer_) {
	std::string name = j["name"].get<std::string>();//name parsed properly
	bool active = j["active"].get<bool>();//good

	GameObject* temp = new EmptyObject(parent_, name.c_str(),parseVec3(j["pos"]));
	//now the components
	int componentArraySize = j["components"].size();//good
	for (int i = 0; i < componentArraySize; ++i) {
		temp->AddComponent(parseComponent(j["components"][i], temp, renderer_));
	}

	//now the children
	int childrenArraySize = j["children"].size();
	for (int i = 0; i < childrenArraySize; ++i) {
		temp->AddChild(parseGameObject(j["children"][i], temp, renderer_));
	}

	return temp;
}

ObjectComponent * JSONFileLoader::parseComponent(json & j, GameObject* parent_, SDL_Renderer* renderer_) {
	std::string type = j["type"].get<std::string>();
	std::string imageName = j["imageName"].get<std::string>();
	bool active = j["active"].get<bool>();

	ObjectComponent* temp;

	auto t = imageName.c_str();
	if (type == "ImageRenderer2dComponent") {
		temp = new ImageRenderer2dComponent(parent_, t, renderer_);
		temp->setActive(active);
	}
	else {
		std::cout << "Component Parser -- don't know what dis is\n";
		temp = nullptr;
	}
	return temp;
}

MATH::Vec3 JSONFileLoader::parseVec3(json & j) {
	return MATH::Vec3(
		j["x"].get<float>(),
		j["y"].get<float>(),
		j["z"].get<float>()
	);
}
