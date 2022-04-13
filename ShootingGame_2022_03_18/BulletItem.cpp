#include "ShootingGame.h"

BulletItem::BulletItem(float px, float py) : Sprite("총알아이템", "", true, px, py)
{
	this->state = State::moveDown;
	this->visible = true;

	this->blinkTimer = 0;
	this->blinkDelay = 0.1;

	this->speed = 150;
	this->moveTimeOut = 3;

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
	if (state == State::moveDown)
	{
		Translate(0, speed * Time::deltaTime);

		moveTimeOut -= Time::deltaTime;

		if (moveTimeOut < 0)
		{
			state = State::blink;
		}
	}
	else if (state == State::blink)
	{

		/// 깜빡임 서브스테이트 머신

		switch (visible)
		{
		case true:
		{
			blinkTimer += Time::deltaTime;

			if (blinkDelay <= blinkTimer)
			{

				enabled = false; //안보임 (스프라이트 개별기능)
				visible = false;  //안보임 상태 전이
				blinkTimer = 0;   //타이머 리셋
			}
		}
		break;

		case false:
		{
			blinkTimer += Time::deltaTime;

			if (blinkDelay <= blinkTimer)
			{
				enabled = true; //보임
				visible = true;  //보임 상태 전이
				blinkTimer = 0;  //타이머 리셋
			}
		}
		break;
		}
	}
}
