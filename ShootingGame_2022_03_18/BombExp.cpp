#include "ShootingGame.h"

BombExp::BombExp(float px, float py) : Animation("气藕气惯", "", true, px, py)
{

}
BombExp::~BombExp()
{

}

void BombExp::Start()
{
	for (int r = 0; r < 2; r++) //row
	{
		for (int c = 0; c < 6; c++)
		{
			AddSprite("Asset/气藕气惯.bmp", c * 130, r * 130, 128, 128, 0);
		}
	}
	AddBoxCollider2D((128-90)/20, 0, 90, 90);
}
void BombExp::Update()
{

}
void BombExp::OnAnimationEnd()
{
	Destroy(this);
}

