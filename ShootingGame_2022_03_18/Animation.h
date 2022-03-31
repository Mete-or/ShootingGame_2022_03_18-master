#pragma once

#include <vector>
#include "GameObject.h"
#include "BMP.h"

using namespace std;



class Animation : public GameObject
{
private:
	vector<Image> sprite[3];
	int index;

	//애니메이션 타이머
	float animTimer;
	float animDelay;
	//애니메이션 아이디
	int animId;

public:
	Animation(string tag, string name, bool active, float px, float py);

	~Animation();

	//애니메이션 추가 함수
	void AddSprite(const char* fileName, int x, int y, int width, int height,int id);

	//애니메이션 출력 함수 
	void Play(int id);

	void Draw();

};

