#include "ShootingGame.h"

Animation::Animation(string tag, string name, bool active, float px, float py)
		: GameObject(tag,name,active,px,py)
{
	this->index = 0;
	this->animTimer = 0;
	this->animDelay = 0.07;
	this->animId = 0;
}
void Animation::AddSprite(const char* fileName, int x, int y, int width, int height,int id)
{
	Image img;
	Bitmap::ReadBMP(fileName, x, y, width, height, &img);
	sprite[id].push_back(img);
}

Animation::~Animation()
{}

//애니메이션 기능 테스트 추가 함수
/*
void Animation::Start()
{
	Image img;
	Bitmap::ReadBMP("Asset/적기.bmp", 200 * 0 + 1, 281, 190, 137, &img);
	sprite.push_back(img);
	Bitmap::ReadBMP("Asset/적기.bmp", 200 * 1 + 1, 281, 190, 137, &img);
	sprite.push_back(img);
	


	****************************중간 피해 애니메이션******************
	Image img;

	Bitmap::ReadBMP("Asset/적기.bmp", 200 * 0 + 1, 141, 190, 137, &img);
	sprite.push_back(img);
	Bitmap::ReadBMP("Asset/적기.bmp", 200 * 1 + 1, 141, 190, 137, &img);
	sprite.push_back(img);
	Bitmap::ReadBMP("Asset/적기.bmp", 200 * 2 + 1, 141, 190, 137, &img);
	sprite.push_back(img);
	Bitmap::ReadBMP("Asset/적기.bmp", 200 * 3 + 1, 141, 190, 137, &img);
	sprite.push_back(img);
	

	//이미지 슬라이스 테스트
	//Bitmap::ReadBMP("Asset/적기.bmp", 401, 141, 190, 137, &sprite);

	for (int i = 0; i < 4; i++)
	{
		Bitmap::ReadBMP("Asset/적기.bmp", 200 * i + 1, 141, 190, 137, &sprite[i]);
	}
	

*/

void Animation::Play(int id)
{
	this->animId = id;
}

void Animation::Draw()
{

	animTimer = animTimer + Time::deltaTime;

	float px = GetPx();
	float py = GetPy();

	Bitmap::DrawBMP(px, py, &sprite[animId][index]);//% 4 로 나누어서도 가능

	if (animTimer >= animDelay)
	{
		
		index++;

		if (index >= sprite[animId].size())
		{
			index = 0;
		}

		animTimer = 0;

	}

}
