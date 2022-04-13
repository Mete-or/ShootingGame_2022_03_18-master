#pragma once
#include "GameObject.h"
#include "BMP.h"

class Sprite : public GameObject
{
private:
	Image sprite;
public:

	bool enabled; //스프라이트 사용가능 지정변수

	Sprite(string tag, string name, bool active, float px, float py);
	~Sprite();

	void SetSprite(const char* fileName);
	void Draw();
};

