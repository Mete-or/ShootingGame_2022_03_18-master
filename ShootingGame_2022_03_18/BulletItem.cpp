#include "ShootingGame.h"

BulletItem::BulletItem(float px, float py) : Sprite("총알아이템", "", true, px, py)
{
	this->visible = true;
}
BulletItem::~BulletItem()
{

}

void BulletItem::Start()
{
	SetSprite("Asset/총알아이템.bmp");
	AddBoxCollider2D(0, 0, 23, 80);
}
void BulletItem::Update()
{
	switch (visible)
	{
		case true:
		{

		}
		break;

		case false:
		{

		}
		break;
	}
}
