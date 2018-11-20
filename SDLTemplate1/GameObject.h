#pragma once
#include "Vector.h"
#include "Matrix.h"

#include <vector>
#include <iostream>

#include "ObjectComponent.h"

class GameObject {
protected:
	MATH::Vec3 pos;
	MATH::Vec3 scale;

	std::string name;
	bool active;

	//if null, this means that this object is a root object that exists directly on the scene
	GameObject* parent;

	std::vector<GameObject*> children;
	std::vector<ObjectComponent*> components;

public:
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Render(MATH::Matrix4 projectionMatrix) = 0;
	virtual void Update(float delta) = 0;

	virtual bool AddChild(GameObject* child) = 0;
	virtual bool RemoveChild(GameObject* child) = 0;

	virtual bool AddComponent(ObjectComponent* newComponent) = 0;

	//TODO: how can i find something based on it's type
	//virtual bool RemoveComponent() = 0;

	void print() {
		std::cout << "Gameobject -- name:" << name << 
			"\tchildren count:" << children.size() << 
			"\tcomponent count:" << components.size() << std::endl;
	}


	std::string getName() { return name; }

	MATH::Vec3 getPos() const { return pos; }
	void setPos(MATH::Vec3 newPos) {
		pos = MATH::Vec3(newPos);
	}

	void toggleActive() { active = !active; }
	bool Enabled() { return active; }
};