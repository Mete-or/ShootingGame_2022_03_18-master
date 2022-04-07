#pragma once
#include "GameObject.h"
class EnemySpawner : public GameObject
{
private:
	//���� Ÿ�� ����
	float spawnTimer;
	float spawnDelay;

	//�ڱ� ��ü �����͸� �����ϴ� ����ƽ����//
	static EnemySpawner* spawner;

	//���� ���� / ���� ī��Ʈ�ϱ�
	int spawnCount;
	int destroyCount;



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

