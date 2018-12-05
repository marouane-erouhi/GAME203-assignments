#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(GameObject * parent_) {
	parent = parent_;
	active = true;
}

PhysicsComponent::PhysicsComponent(GameObject * parent_, MATH::Vec3 vel_) {
	vel = vel_;
}

void PhysicsComponent::OnCreate() {
}

void PhysicsComponent::OnDestroy() {
}

void PhysicsComponent::Render(MATH::Matrix4 projectionMatrix) {

}

void PhysicsComponent::Update(float delta) {
	/*pos.x += (vel.x * deltaTime) + (0.5f * accel.x * (deltaTime * deltaTime));
	pos.y += (vel.y * deltaTime) + (0.5f * accel.y * (deltaTime * deltaTime));
	pos.z += (vel.z * deltaTime) + (0.5f * accel.z * (deltaTime * deltaTime));
	*/

	parent->setPos(
		parent->getPos() += vel * delta
	);
}

void PhysicsComponent::setParent(GameObject * parent_) {
	parent = parent_;
}

void PhysicsComponent::setActive(bool active_) {
	active = active_;
}
