#pragma once

#include "Sprite.h"

class Laser : public Sprite
{
private:
	float speed;
	float lifeTime;
public:
	Laser(float px, float py);
	~Laser();

	void Start();
	void Update();

	
};

