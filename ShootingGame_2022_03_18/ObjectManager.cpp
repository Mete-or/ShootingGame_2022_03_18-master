#include "framework.h"
#include "ShootingGame.h"

//오브젝트 STL vector (static 으로 공유됨)
vector<GameObject*> ObjectManager::gameObjects[MAX_LAYER];

void ObjectManager::Instantiate(GameObject* obj , int layer)
{
	gameObjects[layer].push_back(obj);
	obj->Start();
}

void ObjectManager::Update()
{
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < gameObjects[layer].size(); i++)
		{
			gameObjects[layer][i]->Update();
		}
	}
}
void ObjectManager::CheckCollisionObjectsPair(GameObject* obji  , GameObject *objj)
{
	//충돌검사 객체 포인터 저장
	//GameObject* obji = gameObjects[layerI][i];
	//GameObject* objj = gameObjects[layerJ][j];

	//객체의 충돌체 가져오기
	vector<BoxCollider2D> boxi = obji->GetCollider();
	vector<BoxCollider2D> boxj = objj->GetCollider();

	for (int ii = 0; ii < boxi.size(); ii++)
	{
		for (int jj = 0; jj < boxj.size(); jj++)
		{


			//충돌체의 사각형 좌표
			float xi, yi, widthi, heighti;
			float xj, yj, widthj, heightj;

			boxi[ii].GetBox(xi, yi, widthi, heighti);
			boxj[jj].GetBox(xj, yj, widthj, heightj);

			//i 인덱스 객체 박스 좌표//
			float a0 = xi, b0 = yi, a1 = a0 + widthi, b1 = b0 + heighti;

			//j 인덱스 객체 박스 좌표//
			float x0 = xj, y0 = yj, x1 = x0 + widthj, y1 = y0 + heightj;


			if (y0 < b1 && y1 > b0 && x1 > a0 && x0 < a1)
			{
				//충돌 이벤트
				obji->OnTriggerStay2D(objj);
				objj->OnTriggerStay2D(obji);

			}
		}
	}


}
void ObjectManager::CheckCollision()
{
	for (int layerI = 0; layerI < MAX_LAYER; layerI++)
	{
		for (int layerJ = 0; layerJ < MAX_LAYER; layerJ++)
		{
			if (layerI >= layerJ) //동일 레이어의 객체들간의 충돌검사
			{
				///////////////////////////////////////////////////
				for (int i = 0; i < gameObjects[layerI].size(); i++)
				{

					//충돌 검사
					for (int j = 0; j < gameObjects[layerJ].size(); j++)
					{
						
						/// //////////////////////////////////////////////////////
						
						if (i > j)
						{
							CheckCollisionObjectsPair(gameObjects[layerI][i], gameObjects[layerJ][j]);	
						}

						////////////////////////////////////////////////////////끝

					}

				}
				//////////////////////////////////////////////////////////////////
			}
			else if (layerI < layerJ) //다른 레이어들의 객체들간 충돌 검사
			{
				///////////////////////////////////////////////////////////
				for (int i = 0; i < gameObjects[layerI].size(); i++)
				{

					//충돌 검사
					for (int j = 0; j < gameObjects[layerJ].size(); j++)
					{
					
						CheckCollisionObjectsPair(gameObjects[layerI][i], gameObjects[layerJ][j]);

					}

				}
				///////////////////////////////////////////////////////////
			}
		}
	}
	
	
}

void ObjectManager::Draw()
{
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < gameObjects[layer].size(); i++)
		{
			if (gameObjects[layer][i]->GetActive() == true)
			{
				gameObjects[layer][i]->Draw();			  //객체 그리기
				gameObjects[layer][i]->OnDrawGizmos();   //기즈모 그리기
			}
		}
	}
}

void ObjectManager::ClearDeadObjects()
{
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{

		for (int i = 0; i < gameObjects[layer].size(); i++)
		{
			GameObject* obj = gameObjects[layer][i];

			if (obj->GetDead() == true)
			{
				gameObjects[layer].erase(gameObjects[layer].begin() + i);
				delete obj;

				i--;

				cout << "삭제" << endl;


			}
		}
	}
}

void ObjectManager::Destroy(GameObject* obj)
{

	obj->SetDead(true);

	/*
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == obj)
		{
			gameObjects.erase(gameObjects.begin() + i); //포인터공간만 삭제, 객체 delete는 안함

			//객체 delete 하기
			delete obj;

			//원하는 객체를 삭제하고..반복문 종료
			break;
		}
	}
	*/
}

void ObjectManager::Clear()
{
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		//목록에 있는 객체..삭제하기//
		for (int i = 0; i < gameObjects[layer].size(); i++)
		{
			delete gameObjects[layer][i];
		}

		//객체 포인터 저장 공간만..전체 삭제//
		gameObjects[layer].clear(); //STL vector에 전체삭제..함수
	}
}
