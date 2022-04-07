#pragma once
#include "GameObject.h"
class EnemySpawner : public GameObject
{
private:
	//스폰 타임 변수
	float spawnTimer;
	float spawnDelay;

	//자기 객체 포인터를 저장하는 스태틱변수//
	static EnemySpawner* spawner;

	//적기 스폰 / 제거 카운트하기
	int spawnCount;
	int destroyCount;



public:
	EnemySpawner(float px, float py);
	~EnemySpawner();

	void Start();
	void Update();
	void Draw();

	//함수 오버라이딩
	void OnDrawGizmos();

	//적기 제거 카운트 함수
	void AddDestroy();

	//객체 포인터 가져오기
	static EnemySpawner* Instance();


};

