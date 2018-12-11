#include "Player.h"
#include <iostream>
#include <string>


Player::Player() {

}

void Player::OnCreate() {
	maxLives = 5;
	currentLives = maxLives;
	scores = 0;
	SetBallVelocity(500.0f);
	SetPinVelocity(300.0f);
}

void Player::Update(const float deltaTime) {
	GetCollision();
}

void Player::UpdateCollision() {
	GetCollision();
}

int Player::GetMaxHealth() {
	return maxLives;
}

int Player::GetCurrentLives() {
	return currentLives;
}

void Player::AddLives(int point) {
	currentLives += point;
}

void Player::SubtractLives(int point) {
	currentLives -= point;
}

void Player::ResetLives() {
	currentLives = maxLives;
}

void Player::AddScores(int point) {
	scores += point;
}

void Player::SubtractScores(int point) {
	scores -= point;
}

void Player::ResetScores() {
	scores = 0;
}

void Player::SetBallVelocity(MATH::Vec3 v) {
	ballVelocity = v;
}

MATH::Vec3 Player::GetBallVelocity() {
	return ballVelocity;
}

void Player::SetPinVelocity(MATH::Vec3 v) {
	pinVelocity = v;
}

MATH::Vec3 Player::GetPinVelocity() {
	return pinVelocity;
}


void Player::OnDestroy() {

}

//TODO: add this back once done with integration
void Player::GetCollision() {
	//tags = 0; null
	//tags = 1; player//pin
	//tags = 2; ball
	//tags = 3; frame blocks (bounding border)
	//tags = 4; regular blocks
	//etc...
	//if (Collider::tag1 == 0 && Collider::tag2 == 0) {
	//	//No Collision
	//}

	////If ball collided with...?
	//if (Collider::tag1 == 2) {//On Scene01, ball is always body1 arguement thus tag1
	//	switch (Collider::tag2) {
	//	case 1://Pin, the spring board
	//		break;
	//	case 2://Another ball
	//		break;
	//	case 3://Border
	//		break;
	//	case 4://Breakable blocks
	//		//Example
	//		AddScores(100);
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

Player::~Player() {
	OnDestroy();
}