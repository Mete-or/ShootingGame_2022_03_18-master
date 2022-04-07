#include "ShootingGame.h"

EnemyBullet::EnemyBullet(float px , float py) : Sprite("�����Ѿ�","",true,px,py)
{
	this->speed = 300;

	this->lifeTime = 5;

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Start()
{
	SetSprite("Asset/�Ѿ�1.bmp");

	AddBoxCollider2D(0, 0, 15, 15);
}

void EnemyBullet::Update()
{

	Translate(0, speed * Time::deltaTime);

	
	lifeTime -= Time::deltaTime;

	if (lifeTime <= 0)
	{
		//������ ��ü ����

		Destroy(this);
	}
}
