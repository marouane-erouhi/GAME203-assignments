#include "Collider.h"
#include <iostream>
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

	Vec3 center1;
	center1.x = body1.pos.x + halfLength1;
	center1.y = body1.pos.y - halfWidth1;

	Vec3 center2;
	center2.x = body2.pos.x + halfLength2;
	center2.y = body2.pos.y - halfWidth2;

	Vec3 dist;
	dist.x = absoluteValue(center1.x - center2.x);
	dist.y = absoluteValue(center1.y - center2.y);
	//std::cout << "Dist.y: " << dist.x << "sumwidth: " << sumLength <<std::endl;
	
	xDiff = dist.x - sumLength;
	yDiff = dist.y - sumWidth;

	if(dist.x <= sumLength && dist.y <= sumWidth){
		handleCollision(body1, body2);
		return true;
	}

	return false;
}



void Collider::handleCollision(Body& body1, Body& body2) {
	Vec3 vel = body1.vel;

	if (yDiff > xDiff) {//block is above or below
		body1.vel.y *= -1.0f;
		if (body1.pos.y > body2.pos.y) {//block is below
			body1.pos.y += collisionBuffer;//Buffer to prevent collision trapped
		}
		else {//block is above
			body1.pos.y -= collisionBuffer;
		}

	}
	if (xDiff > yDiff) {//block is below
		body1.vel.x *= -1.0f;
		if (body1.pos.x > body2.pos.x) {//block is to the left
			body1.pos.x += collisionBuffer;//Buffer to prevent collision trapped
		}
		else {//block is to the right
			body1.pos.x -= collisionBuffer;
		}
	}

}

float Collider::absoluteValue(const float& value_) {
	float result = value_;
	if (value_ < 0.0f) {
		result *= -1.0f;
	}
	return result;
}
