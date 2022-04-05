#pragma once
#include "Animation.h"
class BulletExp : public Animation
{
private:

public:
	BulletExp(float px, float py);
	~BulletExp();

	void Start();
	void Update();
	void OnAnimationEnd();

};

