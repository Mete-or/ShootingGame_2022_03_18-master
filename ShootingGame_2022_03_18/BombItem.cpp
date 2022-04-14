#include "ShootingGame.h"

BombItem::BombItem(float px, float py) : Sprite("��ź������","",true,px,py)
{
	this->speed = 80;
	this->moveTimeOut = 3;


	this->visible = true;


	this->blinkTimer = 0;
	this->blinkDelay = 0.1;
	this->blinkTimeOut = 10;

}
BombItem::~BombItem()

{

}

void BombItem::Start()
{
	SetSprite("Asset/��ź������.bmp");
	AddBoxCollider2D(0, 0, 22, 40);
}
void BombItem::Update()
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

		blinkTimeOut -= Time::deltaTime;

		if (blinkTimeOut < 0)
		{
			Destroy(this);

			blinkTimeOut = 10;
		}
	}

	//ȭ�� �ϴܿ��� �����ϱ�//
	if (GetPy() >= HEIGHT)
	{
		Destroy(this);
	}
}
