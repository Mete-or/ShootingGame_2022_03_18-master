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

	bool isBombExpCollided; //��ź
	bool isPlayerExpCollided;

	int downEndPos; //moveDown ���� ���� ������ġ

	bool dropBulletItem;
	bool dropBombItem;

public:

	Enemy(float px, float py);
	~Enemy();

	void Start();
	void Update();
	void Move();
	void Fire();
	
	void SetDropBulletItem(bool drop);
	void SetDropBombItem(bool drop);
	
	//�浹�̺�Ʈ ó���Լ� �������̵�//
	void OnTriggerStay2D(GameObject* other);

	//���� ���� �Լ� 

	void Explosion();
	
};

