#pragma once
#include "Animation.h"

class LaserExp : public Animation
{
private:

public:
	LaserExp(float px , float py);
	~LaserExp();

	void Start();
	void Update();
	void OnAnimationEnd();

};

