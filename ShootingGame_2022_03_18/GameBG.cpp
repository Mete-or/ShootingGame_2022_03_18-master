#include "GameBG.h"

GameBG::GameBG(float px, float py):Sprite("게임배경", "", true, px, py)
{
}

GameBG::~GameBG()
{}

void GameBG::Start()
{
	//이미지 로드//	
	SetSprite("Asset/게임배경.bmp");
}

void GameBG::Update()
{
	//이동 및 입력
}