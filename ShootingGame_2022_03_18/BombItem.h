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

	//������ �ð� ����
	float blinkTimer;
	float blinkDelay;

	//��ũ Ÿ�Ӿƿ�
	float blinkTimeOut;

public:
	BombItem(float px, float py);
	~BombItem();

	void Start();
	void Update();


	
};

