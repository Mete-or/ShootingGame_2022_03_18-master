#pragma once
#include "GameObject.h"
class EnemySpawner : public GameObject
{
private:
	//���� Ÿ�� ����
	float spawnTimer;
	float spawnDelay;


	//���� ���� / ���� ī��Ʈ�ϱ�
	int spawnCount;
	int destroyCount;

	//�ڱ� ��ü �����͸� �����ϴ� ����ƽ����//
	static EnemySpawner* spawner;

	//�Ѿ� ������ ��� ���� �迭//

	bool dropBulletItem[20] = { false ,false ,true  ,false ,false ,
								true  ,false ,true  ,false ,false ,
								false ,true  ,false ,true  ,false ,
								true  ,false ,true  ,true  ,false };

	bool dropBombItem[20] = {   false ,false ,false ,false ,true ,
								false ,false ,false ,false ,true ,
								false ,false ,false ,false ,true ,
								true  ,false ,true  ,true  ,false };

public:
	EnemySpawner(float px, float py);
	~EnemySpawner();

	void Start();
	void Update();
	void Draw();

	//�Լ� �������̵�
	void OnDrawGizmos();

	//���� ���� ī��Ʈ �Լ�
	void AddDestroy();

	//��ü ������ ��������
	static EnemySpawner* Instance();


};

