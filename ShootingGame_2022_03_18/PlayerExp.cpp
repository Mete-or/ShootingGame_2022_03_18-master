#include "ShootingGame.h"


PlayerExp::PlayerExp(float px, float py) : Animation("", "", true, px, py)
{

}
PlayerExp::~PlayerExp()
{

}

void PlayerExp::Start()
{

	AddSprite("Asset/����ȿ��.bmp", 0 + 0 * 225, 5553 + 0 * 321, 224, 320, 0);

	Speed(1);
}
void PlayerExp::Update()
{

}

void PlayerExp::OnAnimationEnd()
{
	Destroy(this);
}