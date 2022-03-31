#include "ShootingGame.h"

EnemyBullet::EnemyBullet(float px , float py) : Sprite("","",true,px,py)
{
	this->speed = 300;


}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Start()
{
	SetSprite("Asset/ÃÑ¾Ë1.bmp");

	AddBoxCollider2D(0, 0, 15, 15);
}

void EnemyBullet::Update()
{
	Translate(0, speed * Time::deltaTime);
}
