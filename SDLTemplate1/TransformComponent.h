//#pragma once
//
//#include "ObjectComponent.h"
//
//class TransformComponent : public ObjectComponent {
//	MATH::Vec3 normalizedPos;
//	MATH::Vec3 screenPos;
//public:
//	TransformComponent(GameObject* parent_, MATH::Vec3 pos);
//
//	void OnCreate();
//	void OnDestroy();
//	void Render(MATH::Matrix4 projectionMatrix);
//	void Update(float delta);
//
//	void setParent(GameObject* parent_);
//	void setPos();
//};