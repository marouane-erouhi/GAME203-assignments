#include "Collider.h"
#include <iostream> //For Debugging
using namespace MATH;

Collider::Collider()
{
	collisionBuffer = 1.0f;
}

Collider::~Collider()
{
}

bool Collider::detectCollision(Body& body1, Body& body2) {
	//Keep in mind the ortho unit ratio to the screen pixel ratio
	int halfLength1 = body1.length / 2; //Pixels
	int halfLength2 = body2.length / 2;
	int sumLength = halfLength1 + halfLength2;

	int halfWidth1 = body1.width / 2;
	int halfWidth2 = body2.width / 2;
	int sumWidth = halfWidth1 + halfWidth2;

	//Find the center coordinates of both objects
	Vec3 center1;
	center1.x = body1.pos.x + halfLength1;
	center1.y = body1.pos.y - halfWidth1;

	Vec3 center2;
	center2.x = body2.pos.x + halfLength2;
	center2.y = body2.pos.y - halfWidth2;

	//Find the distance between the center of each object
	Vec3 dist;
	dist.x = absoluteValue(center1.x - center2.x);
	dist.y = absoluteValue(center1.y - center2.y);
	//std::cout << "Dist.y: " << dist.x << "sumwidth: " << sumLength <<std::endl;
	
	//To find out the direction of the approaching object/ball
	Vec3 sumDiff;
	sumDiff.x = dist.x - sumLength;
	sumDiff.y = dist.y - sumWidth;

	//If the 2 objects overlap = they've collided
	if(dist.x <= sumLength && dist.y <= sumWidth){
		if (body1.tags == 1 && body2.tags == 3) {
			playerCollision(body1);
		}

		handleCollision(body1, body2, sumDiff);
		return true;
	}

	return false;//May not need to return bool//For Debugging
}

void Collider::handleCollision(Body& body1, Body& body2, const Vec3& sumDiff_) {
	Vec3 vel = body1.vel;

	if (sumDiff_.y > sumDiff_.x) {//block is above or below
		body1.vel.y *= -1.0f;
		if (body1.pos.y > body2.pos.y) {//block is below
			body1.pos.y += collisionBuffer;//Buffer to prevent collision trap
		}
		else {//block is above
			body1.pos.y -= collisionBuffer;
		}

	}
	if (sumDiff_.x > sumDiff_.y) {//block is below
		body1.vel.x *= -1.0f;
		if (body1.pos.x > body2.pos.x) {//block is to the left
			body1.pos.x += collisionBuffer;//Buffer to prevent collision trap
		}
		else {//block is to the right
			body1.pos.x -= collisionBuffer;
		}
	}

}

void Collider::playerCollision(Body& player_){
	player_.SetVelocity(Vec3(0.0f, 0.0f, 0.0f));
}

//Simple support function to find absolute values of float
float Collider::absoluteValue(const float& value_) {
	float result = value_;
	if (value_ < 0.0f) {
		result *= -1.0f;
	}
	return result;
}
