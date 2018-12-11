#ifndef COLLIDER_H
#define COLLIDER_H
#include "Body.h"
#include "Vector.h"
//Careful of cyclical includes

class Collider
{
public:
	static bool detectCollision(Body& body1, Body& body2);
private:
	//Used to prevent collision trapping
	//(ball trapped inside blocks during collision)
	static float collisionBuffer;

	static void handleCollision(Body& body1, Body& body2, const MATH::Vec3& sumDiff_);
	//static bool
	//This one is to stop player if KEYUP doesn't work
	static void playerCollision(Body& player_);

	//Support Functions
	static float absoluteValue(const float& value_);
	
	
};

#endif //Collider;
