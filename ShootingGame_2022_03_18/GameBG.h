#pragma once

#include "Sprite.h"

class GameBG : public Sprite
{
private:
public:
	GameBG(float px, float py);
	~GameBG();

	//가상함수 오버라이딩//
	void Start();
	void Update();
};