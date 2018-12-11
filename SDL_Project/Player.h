#ifndef PLAYER_H
#define PLAYER_H
#include "Body.h"
#include "Collider.h"
#include "Vector.h"
#include <memory>

class Player {
public:
	Player();
	~Player();
	void Update(const float deltaTime);
	void UpdateCollision();
	void OnCreate();
	void OnDestroy();

	int GetMaxHealth();
	int GetCurrentLives();
	void AddLives(int point);
	void SubtractLives(int point);
	void ResetLives();
	void AddScores(int point);
	void SubtractScores(int point);
	void ResetScores();


	//There aren't connected to scene01 yet
	void SetBallVelocity(MATH::Vec3 v);
	MATH::Vec3 GetBallVelocity();
	void SetPinVelocity(MATH::Vec3 v);
	MATH::Vec3 GetPinVelocity();

private:
	int maxLives;
	int currentLives;
	int scores;
	MATH::Vec3 ballVelocity;
	MATH::Vec3 pinVelocity;

	void GetCollision();
};

#endif