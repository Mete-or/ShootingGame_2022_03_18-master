#include "ShootingGame.h"

BulletExp::BulletExp(float px, float py) : Animation("","",true,px,py)
{

}
BulletExp::~BulletExp()
{

}

void BulletExp::Start()
{
	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			AddSprite("Asset/�Ѿ�����.bmp", col * 40, row * 40, 40, 40, 0);
		}
	}
	for (int col = 0; col < 2; col++)
	{
		AddSprite("Asset/�Ѿ�����.bmp", col * 40, 2 * 40, 40, 40, 0);
	}

	Speed(1);
}
void BulletExp::Update()
{

}
void BulletExp::OnAnimationEnd()
{
	Destroy(this);
}
