#include "ShootingGame.h"

Laser::Laser(float px, float py) : Sprite("레이저","", true, px, py)
{
	this->speed = 300;
}

Laser::~Laser()
{}

void Laser::Start()
{
	SetSprite("Asset/레이저.bmp");
	AddBoxCollider2D(0, 0, 6, 33);
}

void Laser::Update()
{
	Translate(0, -speed * Time::deltaTime);
}
