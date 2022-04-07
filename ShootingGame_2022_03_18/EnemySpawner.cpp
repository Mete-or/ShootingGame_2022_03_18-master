#include "ShootingGame.h"

EnemySpawner* EnemySpawner::spawner = nullptr;

EnemySpawner::EnemySpawner(float px, float py) : GameObject("","",true,px,py)
{
	this->spawnTimer   = 0;
	this->spawnDelay   = 2;

	this->spawnCount   = 0;
	this->destroyCount = 0;
}
EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::Start()
{
	//자기 자신객체 포인터를 spawner 변수에 저장함
	if (spawner == nullptr)
	{
		spawner = this;
	}
	else
	{
		printf("파일저장실패");
	}
}
void EnemySpawner::Update()
{
	if (spawnCount - destroyCount < 3)
	{
		//적기 스폰 타임 설정

		spawnTimer += Time::deltaTime;

		//적기 스폰

		float px, py;

		GetPosition(px, py);

		if (spawnTimer >= spawnDelay)
		{
			Instantiate(new Enemy(px - 95, py - 137));

			//타이머 리셋
			spawnTimer = 0;

			//스폰 카운트 증가
			spawnCount++;
		}
		else if (spawnCount >= destroyCount)
		{

		}
	}
	 
}
void EnemySpawner::Draw()
{

}
void EnemySpawner::OnDrawGizmos()
{
	float px, py;

	GetPosition(px, py);

	//px , py 를 중심으로 크기가 50인 수평직선 그리기
	DrawLine(px - 50, py, px + 50, py, 255, 0, 0);
	DrawLine(px, py + 50, px, py - 50, 255, 0, 0);
	
}
void EnemySpawner::AddDestroy()
{
	destroyCount++;
}
EnemySpawner* EnemySpawner::Instance()
{
	return spawner;
}

