#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	
	//�̵��ӷ�//
	float speed;

	//�߻�ð� ���� ����//
	float fireTimer;
	float fireDelay;

	//��������Ʈ �̹��� ����ü
	//���� �̹����� �ε�
	Image sprite[7];
	
	//�׸��� �ٲٴ� ����

	int index;

	//�̹�������(�ִϸ��̼�) �ð�����
	float animTimer;
	float animDelay;

	//�÷��̾� ü��
	float hp;

public:
	Player(float px, float py);
	~Player();

	void Start();
	void Update();
	void Draw();

	//�÷��̾� ��� �߰��Լ�//
	void Move();
	void Fire();

	//�浹ó�� �Լ� �������̵�
	void OnTriggerStay2D(GameObject* other);
};

