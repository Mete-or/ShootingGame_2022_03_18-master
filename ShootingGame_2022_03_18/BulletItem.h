#pragma once
#include "Sprite.h"
class BulletItem : public Sprite
{

	enum State { moveDown, blink };
	
private:

	State state;  //이동 깜빡 인상태 변수

	bool visible; //true false 깜빡이는 효과 만들기

	//깜빡임 시간 변수
	float blinkTimer;
	float blinkDelay;

	//이동 속력(speed) [참고]속도는(velocity)
	float speed;

	//이동 타임아웃
	float moveTimeOut;

	//블링크 타임아웃
	float blinkTimeOut;

public:
	BulletItem(float px, float py);
	~BulletItem();

	void Start();
	void Update();
};

