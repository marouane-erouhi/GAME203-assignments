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