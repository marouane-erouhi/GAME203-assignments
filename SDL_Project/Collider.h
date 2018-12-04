#ifndef COLLIDER_H
#define COLLIDER_H
#include "Body.h"
#include "Vector.h"
//Careful of cyclical includes

class Collider
{
public:
	Collider();
	~Collider();
	
	bool detectCollision(Body& body1, Body& body2);

private:
	float xDiff;
	float yDiff;
	float collisionBuffer;

	void handleCollision(Body& body1, Body& body2);
	//Support Functions
	float absoluteValue(const float& value_);
	
	
};

#endif //Collider;
