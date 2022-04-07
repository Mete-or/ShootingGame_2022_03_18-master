#pragma once
#include "Sprite.h"

class EnemyBullet : public Sprite
{
private:
	float speed;
	float lifeTime;

public:
	EnemyBullet(float px , float py);

	~EnemyBullet();

	void Start();
	void Update();
};

