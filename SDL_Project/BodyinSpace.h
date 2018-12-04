#ifndef BODYINSPACE_H
#define BODYINSPACE_H
#include "Vector.h"
#include "SDL.h"

class BodyinSpace {
public:
	MATH::Vec3 pos;
	MATH::Vec3 vel;
	float mass;
	float radius;

private:
	MATH::Vec3 accel;

	SDL_Surface *bodyImage;

public:
	BodyinSpace(char* imageName, float mass_, float radius_, MATH::Vec3 pos_, MATH::Vec3 vel_, MATH::Vec3 accel_);
	~BodyinSpace();
	void Update(const float deltaTime);
	void ApplyForce(MATH::Vec3 force);

	/// Just a little helper function
	SDL_Surface* getImage();
};


#endif
