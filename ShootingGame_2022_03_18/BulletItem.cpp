#include "ShootingGame.h"

BulletItem::BulletItem(float px, float py) : Sprite("�Ѿ˾�����", "", true, px, py)
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
	SetSprite("Asset/�Ѿ˾�����.bmp");
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

		/// ������ ���꽺����Ʈ �ӽ�

		switch (visible)
		{
		case true:
		{
			blinkTimer += Time::deltaTime;

			if (blinkDelay <= blinkTimer)
			{

				enabled = false; //�Ⱥ��� (��������Ʈ �������)
				visible = false;  //�Ⱥ��� ���� ����
				blinkTimer = 0;   //Ÿ�̸� ����
			}
		}
		break;

		case false:
		{
			blinkTimer += Time::deltaTime;

			if (blinkDelay <= blinkTimer)
			{
				enabled = true; //����
				visible = true;  //���� ���� ����
				blinkTimer = 0;  //Ÿ�̸� ����
			}
		}
		break;
		}
	}
}
