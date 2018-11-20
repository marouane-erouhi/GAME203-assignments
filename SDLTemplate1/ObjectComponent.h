#pragma once
#include "Vector.h"
#include "Matrix.h"

class GameObject;

class ObjectComponent {
protected:
	GameObject* parent;
	bool active;
public:
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Render(MATH::Matrix4 projectionMatrix) = 0;
	virtual void Update(float delta) = 0;

	virtual void setParent(GameObject* parent_) = 0;
	virtual void setActive(bool active_) = 0;
};