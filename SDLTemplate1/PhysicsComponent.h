#pragma once

#include "GameObject.h"
#include "ObjectComponent.h"
#include "Vector.h"

class PhysicsComponent : ObjectComponent {
private:
	float mass;
	float radius;
	MATH::Vec3 vel;
	MATH::Vec3 dimentions;

public:
	PhysicsComponent(GameObject * parent_);
	PhysicsComponent(GameObject * parent_, MATH::Vec3 vel_);

	void OnCreate();
	void OnDestroy();
	void Render(MATH::Matrix4 projectionMatrix);
	void Update(float delta);

	MATH::Vec3 getVelocity();
	void setVelocity(MATH::Vec3 vel_);

	void setParent(GameObject* parent_);
	void setActive(bool active_);
};