//#pragma once
//#include "Vector.h"
//#include "Matrix.h"
//
//#include <SDL.h>
//#include <SDL_image.h>
//
//#include <iostream>
//class UIElement {
//protected:
//	const char * id;
//	MATH::Vec3 pos;
//	bool enabled = true;
//	MATH::Vec3 screenCoords;
//public:
//	virtual void OnCreate() = 0;
//	virtual void OnDestroy() = 0;
//	virtual void Render(MATH::Matrix4 projectionMatrix) = 0;
//	virtual void Update(float delta) = 0;
//
//	virtual bool pointInside(MATH::Vec3 point) = 0;
//
//	const char * getId() {
//		return this->id;
//	}
//
//	MATH::Vec3 getPos() {
//		return this->pos;
//	}
//
//	MATH::Vec3 getScreenCoords() {
//		return this->screenCoords;
//	}
//	void setPos(MATH::Vec3 newPos){
//		pos = newPos;
//	}
//
//	void setEnable(bool e) { enabled = e; }
//	bool Enabled() { return enabled; }
//};