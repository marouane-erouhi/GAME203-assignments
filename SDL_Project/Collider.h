#ifndef COLLIDER_H
#define COLLIDER_H
#include "Body.h"
#include "Vector.h"
#include "Player.h"
//Careful of cyclical includes

class Collider
{
public:
	Collider();
	~Collider();
	
	static bool detectCollision(Body& body1, Body& body2);
	
	//Send the id of the collided objects to player
	static int tag1;
	static int tag2;
	//static bool isCollided;
	static void ClearTags();

private:
	//Used to prevent collision trapping
	//(ball trapped inside blocks during collision)
	static float collisionBuffer;

	static void handleCollision(Body& body1, Body& body2, const MATH::Vec3& sumDiff_);
	
	//This one is to stop player if KEYUP doesn't work
	static void playerCollision(Body& player_);

	//Support Functions
	static float absoluteValue(const float& value_);
	
	//Find out which 2 objects collided
	static void GetTags(const int body1, const int body2);
};

#endif //Collider;
