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

	if (tag == "레이저")
	{
		hp = hp - 10; //적기에 피해 데미지 적용하기
		printf("적기 체력 %f\n", hp);

		//레이저 폭발효과
		float px = other->GetPx();
		float py = other->GetPy();

		Instantiate(new LaserExp(px, py));

		Destroy(other); // 데이터 삭제하기

	}
	else if (tag == "플레이어")
	{
		printf("---적기에 플레이어가 충돌함--- \n");
	}
}


