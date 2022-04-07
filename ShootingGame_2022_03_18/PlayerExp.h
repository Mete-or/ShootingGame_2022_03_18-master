#pragma once
#include "Animation.h"
class PlayerExp : public Animation
{
private:


public:
	PlayerExp(float px, float py);
	~PlayerExp();

	void Start();
	void Update();

	void OnAnimationEnd();

};

