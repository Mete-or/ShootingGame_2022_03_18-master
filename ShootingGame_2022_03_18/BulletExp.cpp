#include "ShootingGame.h"

BulletExp::BulletExp(float px, float py) : Animation("","",true,px,py)
{

}
BulletExp::~BulletExp()
{

}

void BulletExp::Start()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			AddSprite("Asset/ÃÑ¾ËÆø¹ß.bmp", col * 40, row * 40, 40, 40, 0);
		}
	}

	Speed(10);
}
void BulletExp::Update()
{

}
void BulletExp::OnAnimationEnd()
{
	Destroy(this);
}
