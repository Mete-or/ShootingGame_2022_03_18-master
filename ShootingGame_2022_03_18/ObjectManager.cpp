#include "framework.h"
#include "ShootingGame.h"

//오브젝트 STL vector (static 으로 공유됨)
vector<GameObject*> ObjectManager::gameObjects;

void ObjectManager::Instantiate(GameObject* obj)
{
	gameObjects.push_back(obj);
	obj->Start();
}

void ObjectManager::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}
void ObjectManager::CheckCollision()
{
	
	for (int j = 0; j < gameObjects.size(); j++)
	{
		
		//충돌 검사
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (i > j)
			{
				//충돌검사 객체 포인터 저장
				GameObject* obji = gameObjects[i];
				GameObject* objj = gameObjects[j];

				//객체의 충돌체 가져오기
				BoxCollider2D boxi = obji->GetCollider();
				BoxCollider2D boxj = objj->GetCollider();

				//충돌체의 사각형 좌표
				float xi, yi, widthi, heighti;
				float xj, yj, widthj, heightj;

				boxi.GetBox(xi, yi, widthi, heighti);
				boxj.GetBox(xj, yj, widthj, heightj);

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
				

				//cout << "(" << gameObjects[i]->GetTag() << ")" <<","<< "(" << gameObjects[j]->GetTag() << ")"<<endl;
			}
			
			
		}
		
	}


}

void ObjectManager::Draw()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();			  //객체 그리기
		gameObjects[i]->OnDrawGizmos();   //기즈모 그리기
	}
}

void ObjectManager::ClearDeadObjects()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		GameObject* obj = gameObjects[i];

		if (obj->GetDead() == true)
		{
			gameObjects.erase(gameObjects.begin() + i);
			delete obj;

			i--;

			cout << "삭제" << endl;

			
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
	//목록에 있는 객체..삭제하기//
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}

	//객체 포인터 저장 공간만..전체 삭제//
	gameObjects.clear(); //STL vector에 전체삭제..함수
}
