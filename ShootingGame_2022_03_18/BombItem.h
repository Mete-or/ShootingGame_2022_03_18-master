#pragma once
#include "Sprite.h"

class BombItem : public Sprite
{

	enum State { moveDown , blink };

private:
	State state;

	float speed;

	int moveTimeOut;

	bool visible;

	//깜빡임 시간 변수
	float blinkTimer;
	float blinkDelay;

	//블링크 타임아웃
	float blinkTimeOut;

public:
	BombItem(float px, float py);
	~BombItem();

	void Start();
	void Update();


	
};

