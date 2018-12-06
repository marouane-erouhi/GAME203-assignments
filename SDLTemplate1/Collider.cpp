#include "Collider.h"
#include "PhysicsComponent.h"

bool Collider::detectCollision(EmptyObject & body1, EmptyObject & body2) {
	collisionBuffer = 1.0f;
	//Keep in mind the ortho unit ratio to the screen pixel ratio
	MATH::Vec3 halfLength1 = body1.getDimentions() / 2;
	MATH::Vec3 halfLength2 = body2.getDimentions() / 2;
	MATH::Vec3 sumLength = halfLength1 + halfLength2;


	MATH::Vec3 center1 = body1.getDimentions() + halfLength1;
	MATH::Vec3 center2 = body2.getDimentions() + halfLength2;

	MATH::Vec3 dist;
	dist.x = absoluteValue(center1.x - center2.x);
	dist.y = absoluteValue(center1.y - center2.y);
	//std::cout << "Dist.y: " << dist.x << "sumwidth: " << sumLength <<std::endl;

	MATH::Vec3 diff = dist - sumLength;

	if (dist.x <= sumLength.x && dist.y <= sumLength.y) {
		handleCollision(body1, body2, diff);
		return true;
	}

	return false;
}

void Collider::handleCollision(EmptyObject & body1, EmptyObject & body2, MATH::Vec3 diff) {
	PhysicsComponent* body1PhyiscsComponent = (PhysicsComponent*) body1.GetComponent(ComponentType::Physics);
	MATH::Vec3 body1vel = body1PhyiscsComponent->getVelocity();

	auto body1Pos = body1.getPos();
	auto body2Pos = body2.getPos();

	if (diff.y > diff.x) {//block is above or below
		body1vel.y *= -1;

		if (body1Pos.y > body2Pos.y) {//block is below
			body1Pos.y += collisionBuffer;//Buffer to prevent collision trapped
		}
		else {//block is above
			body1Pos.y -= collisionBuffer;
		}
		body1.setPos(body1Pos);
	}

	if (diff.x > diff.y) {//block is below
		body1vel.x *= -1.0f;
		if (body1Pos.x > body2Pos.x) {//block is to the left
			body1Pos.x += collisionBuffer;//Buffer to prevent collision trapped
		}
		else {//block is to the right
			body1Pos.x -= collisionBuffer;
		}
		body1.setPos(body1Pos);
	}


}

float Collider::absoluteValue(const float & value_) {
	float result = value_;
	if (value_ < 0.0f) {
		result *= -1.0f;
	}
	return result;
}
