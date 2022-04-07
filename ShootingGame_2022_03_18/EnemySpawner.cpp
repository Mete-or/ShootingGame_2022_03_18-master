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
	//�ڱ� �ڽŰ�ü �����͸� spawner ������ ������
	if (spawner == nullptr)
	{
		spawner = this;
	}
	else
	{
		printf("�����������");
	}
}
void EnemySpawner::Update()
{
	if (spawnCount - destroyCount < 3)
	{
		//���� ���� Ÿ�� ����

		spawnTimer += Time::deltaTime;

		//���� ����

		float px, py;

		GetPosition(px, py);

		if (spawnTimer >= spawnDelay)
		{
			Instantiate(new Enemy(px - 95, py - 137));

			//Ÿ�̸� ����
			spawnTimer = 0;

			//���� ī��Ʈ ����
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

	//px , py �� �߽����� ũ�Ⱑ 50�� �������� �׸���
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

