#ifndef COLLIDER_H
#define COLLIDER_H
#include "EmptyObject.h"

class Collider {
public:
	static bool detectCollision(EmptyObject & body1, EmptyObject & body2);

private:
	static void handleCollision(EmptyObject & body1, EmptyObject & body2, MATH::Vec3 diff);

	static float absoluteValue(const float& value_);

	static float collisionBuffer;
};

#endif // !COLLIDER_H