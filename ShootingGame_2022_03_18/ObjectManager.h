#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;

#define MAX_LAYER 8

class ObjectManager
{
private:
	static vector<GameObject*> gameObjects[MAX_LAYER];
public:

	//���� Instance �߰� �� ���� //
	static void Instantiate(GameObject* obj , int layer = 0); // 0�� ����Ʈ �Ű�����
	static void Destroy(GameObject* obj);

	//���� ��� ������Ʈ �Լ�
	static void Update();

	//���� ��ü �浹�˻� �Լ�
	static void CheckCollision();
	static void CheckCollisionObjectsPair(GameObject* obji, GameObject* objj);
	

	//���� ��� �׸���
	static void Draw();

	//���� ��� ��� �����ϱ� �Լ�
	static void Clear();

	//���� ������� ǥ�õ� ��ü�� �����ϴ� �Լ�
	static void ClearDeadObjects();
	
};

