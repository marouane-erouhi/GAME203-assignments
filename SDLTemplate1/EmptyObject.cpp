#include "EmptyObject.h"

EmptyObject::EmptyObject(GameObject* parent_, const char* name_, MATH::Vec3 pos_) {
	parent = parent_;
	name = name_;
	active = true;
	pos = pos_;

	children = std::vector<GameObject*>();
	components = std::vector<ObjectComponent*>();
}

void EmptyObject::OnCreate() {
	for (auto it : children) {
		it->OnCreate();
	}
	for (auto it : components) {
		it->OnCreate();
	}
}

void EmptyObject::OnDestroy() {
	for (auto it : children) {
		it->OnDestroy();
	}
	for (auto it : components) {
		it->OnDestroy();
	}
}

void EmptyObject::Render(MATH::Matrix4 projectionMatrix) {
	for (auto it : children) {
		it->Render(projectionMatrix);
	}
	for (auto it : components) {
		it->Render(projectionMatrix);
	}
}

void EmptyObject::Update(float delta) {
	for (auto it : children) {
		it->Update(delta);
	}
	for (auto it : components) {
		it->Update(delta);
	}
}

bool EmptyObject::AddChild(GameObject * child) {
	//if (GameObjectPresent(child->getName()))	return false;//return false on duplicates

	child->OnCreate();
	children.push_back(child);

	return true;
}

bool EmptyObject::RemoveChild(GameObject * child) {
	
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children.at(i) == child) {
			child->OnDestroy();
			children.erase(children.begin() + i);
			return true;
		}
	}

	return false;//if the object is not here
}

bool EmptyObject::AddComponent(ObjectComponent * newComponent) {
	//if (ComponentPresent(newComponent))	return false;
	//initialize and add it
	newComponent->OnCreate();
	components.push_back(newComponent);

	return true;
}

bool EmptyObject::GameObjectPresent(std::string name) {
	for (auto it : children) {
		if (it->getName() == name)	return true;
	}
	return false;
}

bool EmptyObject::ComponentPresent(ObjectComponent* newComponent) {
	for (auto it : components) {
		if (typeid(it) == typeid(newComponent)) {
			return true;// a component of the same type already exists
		}
	}
	return false;
}
