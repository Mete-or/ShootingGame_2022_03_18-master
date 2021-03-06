#pragma once
#include "GameObject.h"

class Player : public GameObject
{
	enum State { showUp = 0, control = 1 };

private:
	
	//이동속력//
	float speed;
	float showUpspeed;

	//발사시간 측정 변수//
	float fireTimer;
	float fireDelay;

	//스프라이트 이미지 구조체
	//직접 이미지를 로드
	Image sprite[7];
	
	//그림을 바꾸는 변수

	int index;

	//이미지변경(애니메이션) 시간변수
	float animTimer;
	float animDelay;

	//플레이어 체력
	float hp;

	State state;

	//총알(레이저) 발사 갯수
	int bulletCount;

	int bombCount;

	//총알(레이저) 아이템 충돌 확인
	bool isBulletItemCollided;
	bool isBombItemCollided;

public:
	Player(float px, float py);
	~Player();

	void Start();
	void Update();
	void Draw();

	//플레이어 기능 추가함수//
	void Move();
	void Fire();

	//충돌처리 함수 오버라이딩
	void OnTriggerStay2D(GameObject* other);
};

