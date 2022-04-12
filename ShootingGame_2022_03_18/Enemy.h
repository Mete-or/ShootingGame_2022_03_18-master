#pragma once

#include "Animation.h"

class Enemy : public Animation
{
	enum State { moveDown = 0, moveLeft = 1, moveRight = 2 , fall = 3};

private:

	float speed;
	float fallspeed;
	State state;


	float fireTimer;
	float fireDelay;
	
	float fallTimeOut;

	float hp;

	bool isBombExpCollided; //폭탄
	bool isPlayerExpCollided;

	int downEndPos; //moveDown 상태 종료 랜덤위치

public:

	Enemy(float px, float py);
	~Enemy();

	void Start();
	void Update();
	void Move();
	void Fire();
	
	//충돌이벤트 처리함수 오버라이딩//
	void OnTriggerStay2D(GameObject* other);
};

