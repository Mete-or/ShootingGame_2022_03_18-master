#include "ShootingGame.h"

LaserExp::LaserExp(float px, float py) : Animation("", "", true, px, py)
{

}
LaserExp::~LaserExp()
{

}
void LaserExp::Start()
{
	for (int y =2; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			AddSprite("Asset/레이저폭발.bmp", x * 36, y * 36, 36, 36, 0);
		}
	}
	
	//애니메이션 속도 조절
	Speed(10);
}
void LaserExp::Update()
{

}
void LaserExp::OnAnimationEnd()
{
	Destroy(this);
}
