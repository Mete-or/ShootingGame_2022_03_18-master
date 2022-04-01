#include "ShootingGame.h"

Enemy::Enemy(float px, float py) : Animation("����", "", true, px, py)
{
	this->speed = 100;
	this->state = State::moveDown;

	this->fireTimer = 0;
	this->fireDelay = 0.5;

	this->hp = 100;

}
Enemy::~Enemy()
{

}
void Enemy::Start()
{

	//���ؾ��� ���� �̹���								�迭�� �ε���(AnimID)
	for (int i = 0; i < 2; i++)
	{
		AddSprite("Asset/����.bmp", 200 * i + 1, 281, 190, 137, 0);
	}
	//�߰����� ���� �̹�����
	for (int i = 0; i < 4; i++)
	{
		AddSprite("Asset/����.bmp", 200 * i + 1, 141, 190, 137, 1);

	}
	//�ִ����� ���� �̹�����
	for (int i = 0; i < 4; i++)
	{
		AddSprite("Asset/����.bmp", 200 * i + 1, 1, 190, 137, 2);
	}

	//�浹ü �߰��ϱ�
	AddBoxCollider2D(0, 0, 190, 137);
		
}
void Enemy::Update()
{
	Move();
	//Fire();

} 

void Enemy::Move()
{
	//���� �̵��ϱ� ������Ʈ �ӽ�//
	switch (state)
	{
	case State::moveDown:
	{
		Translate(0, speed * Time::deltaTime);

		if (GetPy() > 25)
		{
			state = State::moveLeft;
		}
	}
	break;
	case State::moveLeft:
	{
		Translate(-speed * Time::deltaTime, 0);

		if (GetPx() < 5)
		{
			state = State::moveRight;
		}
	}
	break;

	case State::moveRight:
	{
		Translate(speed * Time::deltaTime, 0);

		if (GetPx() > WIDTH - 185)
		{
			state = State::moveLeft;
		}
	}
	break;
	}
}

void Enemy::Fire()
{
	//�Ѿ� �߻�//
	float px = GetPx();
	float py = GetPy();

	fireTimer = fireTimer + Time::deltaTime;

	if (state == State::moveLeft || state == State::moveRight)
	{
		if (fireTimer >= fireDelay)
		{
			Instantiate(new EnemyBullet(px + 86, py + 110));

			fireTimer = 0;
		}
	}

}

void Enemy::OnTriggerStay2D(GameObject* other)
{
	string tag = other->GetTag();

	if (tag == "������")
	{
		hp = hp - 10; //���⿡ ���� ������ �����ϱ�
		printf("���� ü�� %f\n", hp);

		//������ ����ȿ��
		float px = other->GetPx();
		float py = other->GetPy();

		Instantiate(new LaserExp(px, py));

		Destroy(other); // ������ �����ϱ�

	}
	else if (tag == "�÷��̾�")
	{
		printf("---���⿡ �÷��̾ �浹��--- \n");
	}
}


