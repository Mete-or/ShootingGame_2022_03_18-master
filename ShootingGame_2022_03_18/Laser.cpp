#include "ShootingGame.h"

Laser::Laser(float px, float py) : Sprite("레이저","", true, px, py)
{
	this->speed = 300;
	this->lifeTime = 5;
}

Laser::~Laser()
{

}

void Laser::Start()
{
	SetSprite("Asset/레이저.bmp");
	AddBoxCollider2D(0, 0, 6, 33);
}

void Laser::Update()
{
	Translate(0, -speed * Time::deltaTime);

	//라이프타임 측정//
	lifeTime = lifeTime - Time::deltaTime;

	if (lifeTime <= 0)
	{
		//레이저 객체 삭제

		Destroy(this);
	}

}




 