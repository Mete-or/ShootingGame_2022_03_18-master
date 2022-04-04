#pragma once
#include "Animation.h"

class EnemyExp : public Animation
{
private:

public:
	EnemyExp(float px, float py);
	~EnemyExp();

	void Start();
	void Update();
	void OnAnimationEnd();
};

