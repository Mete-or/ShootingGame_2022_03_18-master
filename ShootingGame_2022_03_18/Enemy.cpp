#include "ShootingGame.h"

Enemy::Enemy(float px, float py) : Animation("적기", "", true, px, py)
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

	//피해없는 적기 이미지								배열의 인덱스(AnimID)
	for (int i = 0; i < 2; i++)
	{
		AddSprite("Asset/적기.bmp", 200 * i + 1, 281, 190, 137, 0);
	}
	//중간피해 적기 이미지들
	for (int i = 0; i < 4; i++)
	{
		AddSprite("Asset/적기.bmp", 200 * i + 1, 141, 190, 137, 1);

	}
	//최대피해 적기 이미지들
	for (int i = 0; i < 4; i++)
	{
		AddSprite("Asset/적기.bmp", 200 * i + 1, 1, 190, 137, 2);
	}

	//충돌체 추가하기
	AddBoxCollider2D(0, 0, 190, 137);
		
}
void Enemy::Update()
{
	Move();
	//Fire();

}

void Enemy::Move()
{
	//적기 이동하기 스테이트 머신//
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
	//총알 발사//
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

	printf("---적기 클래스 충돌처리 함수 --- \n");
	printf("---충돌 상대 태그 %s\n", tag.data());
}


