#pragma once

#include "GameObject.h"

#include <typeinfo>

class EmptyObject : public GameObject {
public:
	EmptyObject(GameObject* parent_, const char* name_, MATH::Vec3 pos_);

	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	bool AddChild(GameObject* child);
	bool RemoveChild(GameObject* child);

	bool AddComponent(ObjectComponent* newComponent);

private:
	/// Check if a GameObject with the same name is already a child
	bool GameObjectPresent(std::string name);
	/// Check if the component already axists
	bool ComponentPresent(ObjectComponent* newComponent);
};