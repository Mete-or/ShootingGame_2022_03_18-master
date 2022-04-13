#include "ShootingGame.h"

Enemy::Enemy(float px, float py) : Animation("적기", "", true, px, py)
{
	this->state = State::moveDown;
	this->speed       = 100;
	this->fallspeed   = 300;
	this->fallTimeOut = 3;



	this->fireTimer = 0;
	this->fireDelay = 0.5;

	this->hp = 100;

	this->isBombExpCollided   = false;
	this->isPlayerExpCollided = false;

	this->dropBulletItem      = false;
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
	AddBoxCollider2D(0, 80, 190, 25); //가운데 날개
	AddBoxCollider2D(65, 10, 62, 16); //꼬리 날개
	AddBoxCollider2D(88, 26,14, 112); //가운데 몸통

	//moveDown 상태 종료 위치 랜덤만들기
	downEndPos = Random::Range(20, 150);

}
void Enemy::Update()
{
	Move();
	Fire();

	//중복 충돌 판단 변수 리셋
	isBombExpCollided = false; 
	isPlayerExpCollided = false;

} 
void Enemy::SetDropBulletItem(bool drop)
{
	dropBulletItem = drop;
}

void Enemy::Move()
{
	//적기 이동하기 스테이트 머신//
	switch (state)
	{
	case State::moveDown:
	{
		Translate(0, speed * Time::deltaTime);

		if (GetPy() > downEndPos)
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

	case State::fall:
	{
		//추락 이동하기
		Translate(0, fallspeed * Time::deltaTime);

		//타임아웃 
		fallTimeOut -= Time::deltaTime;
		if (fallTimeOut < 0)
		{
			Destroy(this);

			EnemySpawner* spawner = EnemySpawner::Instance();
			
			spawner->AddDestroy();
			
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
		if (isPlayerExpCollided == false)
		{
			isPlayerExpCollided = true;

			hp = hp - 10; //적기에 피해 데미지 적용하기
			printf("적기 체력 %f\n", hp);

			//레이저 폭발효과
			float px = other->GetPx();
			float py = other->GetPy();

			Instantiate(new LaserExp(px - 14, py));

			Destroy(other); // 데이터 삭제하기

			if (80 <= hp && hp <= 100)
			{
				Play(0);
			}
			else if (50 <= hp && hp < 80)
			{
				Play(1);
			}
			else if (0 <= hp && hp < 50)
			{
				Play(2);
				state = State::fall; //적기 추락상태로 전이(transition)
			}
			else if (hp <= 0)
			{
				//적기 폭발
				px = this->GetPx();
				py = this->GetPy();
				Instantiate(new EnemyExp(px - 18, py - 90));
				//적기 제거
				Destroy(this);

				//적기 제거 카운트하기
				EnemySpawner* spawner = EnemySpawner::Instance();
				spawner->AddDestroy();

				int p = Random::Range(0, 10000);
				/*랜덤방식
				if (p < 1000)
				{
					
					//총알아이템 드롭 (레이저)
					Instantiate(new BulletItem(px + 80, py + 40));
				}
				*/
				
				if (dropBulletItem == true)
				{
					Instantiate(new BulletItem(px + 80, py + 40));
				}
				


			}

		}
	}
	else if (tag == "플레이어")
	{
		printf("---적기에 플레이어가 충돌함--- \n");
	}
	else if (tag == "폭탄폭발")
	{
		if (isBombExpCollided == false) // 이전에 충돌처리가 안되었을때만 
		{
			isBombExpCollided = true; //충돌처리 했음을 표시

			//적기 폭발효과
			float px = this->GetPx();
			float py = this->GetPy();
			Instantiate(new EnemyExp(px - 18, py - 90),1);


			//적기 제거 
			Destroy(this);

			//적기 제거 카운트하기
			EnemySpawner* spawner = EnemySpawner::Instance();
			spawner->AddDestroy();

			//총알아이템 드롭 (레이저)
			Instantiate(new BulletItem(px + 80, py + 40));
		}
	}
}


