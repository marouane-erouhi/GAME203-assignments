#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "SDL.h"

class Body {
public:
	float mass = 1.0f;
	float radius;
	float length;
	float width;
	MATH::Vec3 pos;
	MATH::Vec3 vel;

private:
	MATH::Vec3 accel;
	SDL_Surface *bodyImage;
	
public:
	Body(char* imageName_, MATH::Vec3 pos_);//Use the image dimension to set length/width
	Body(char* imageName_, float radius_, MATH::Vec3 pos_);//Circle
	Body(char* imageName_, float length_, float width_, MATH::Vec3 pos_);//Rectangle
	Body(char* imageName_, float mass_, MATH::Vec3 pos_, MATH::Vec3 vel_, MATH::Vec3 accel_);
	~Body();

	void SetImage(const char* imageName_);
	void SetPosition(MATH::Vec3 pos_);
	void SetVelocity(MATH::Vec3 vel_);
	void ApplyForce(MATH::Vec3 force);
	void Update(const float deltaTime);
	
	void OnDestroy();

	/// Just a little helper function
	SDL_Surface* getImage();
};


#endif
