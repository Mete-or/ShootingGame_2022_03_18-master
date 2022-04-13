#include "ShootingGame.h"

Enemy::Enemy(float px, float py) : Animation("����", "", true, px, py)
{
	this->state = State::moveDown;
	this->speed       = 100;
	this->fallspeed   = 300;
	this->fallTimeOut = 3;



	this->fireTimer = 0;
	this->fireDelay = 0.5;

	this->hp = 100;

	this->isBombExpCollided   = false;
	this->isPlayerExpCollided = false;

	this->dropBulletItem      = false;
}
Enemy::~Enemy()
{

}
void Enemy::Start()
{

	//���ؾ��� ���� �̹���								�迭�� �ε���(AnimID)

		for (int i = 0; i < 2; i++)
		{
			AddSprite("Asset/����.bmp", 200 * i + 1, 281, 190, 137, 0);
		}
	
	//�߰����� ���� �̹�����

		for (int i = 0; i < 4; i++)
		{
			AddSprite("Asset/����.bmp", 200 * i + 1, 141, 190, 137, 1);

		}
	
	//�ִ����� ���� �̹�����

		for (int i = 0; i < 4; i++)
		{
			AddSprite("Asset/����.bmp", 200 * i + 1, 1, 190, 137, 2);
		}
	

	//�浹ü �߰��ϱ�
	AddBoxCollider2D(0, 80, 190, 25); //��� ����
	AddBoxCollider2D(65, 10, 62, 16); //���� ����
	AddBoxCollider2D(88, 26,14, 112); //��� ����

	//moveDown ���� ���� ��ġ ���������
	downEndPos = Random::Range(20, 150);

}
void Enemy::Update()
{
	Move();
	Fire();

	//�ߺ� �浹 �Ǵ� ���� ����
	isBombExpCollided = false; 
	isPlayerExpCollided = false;

} 
void Enemy::SetDropBulletItem(bool drop)
{
	dropBulletItem = drop;
}

void Enemy::Move()
{
	//���� �̵��ϱ� ������Ʈ �ӽ�//
	switch (state)
	{
	case State::moveDown:
	{
		Translate(0, speed * Time::deltaTime);

		if (GetPy() > downEndPos)
		{
			state = State::moveLeft;
		}
	}
	break;
	case State::moveLeft:
	{
		Translate(-speed * Time::deltaTime, 0);

		if (GetPx() < 5)
		{
			state = State::moveRight;
		}
	}
	break;

	case State::moveRight:
	{
		Translate(speed * Time::deltaTime, 0);

		if (GetPx() > WIDTH - 185)
		{
			state = State::moveLeft;
		}
	}
	break;

	case State::fall:
	{
		//�߶� �̵��ϱ�
		Translate(0, fallspeed * Time::deltaTime);

		//Ÿ�Ӿƿ� 
		fallTimeOut -= Time::deltaTime;
		if (fallTimeOut < 0)
		{
			Destroy(this);

			EnemySpawner* spawner = EnemySpawner::Instance();
			
			spawner->AddDestroy();
			
		}
	}
	break;
	}
	
}

void Enemy::Fire()
{
	//�Ѿ� �߻�//
	float px = GetPx();
	float py = GetPy();

	fireTimer = fireTimer + Time::deltaTime;

	if (state == State::moveLeft || state == State::moveRight)
	{
		if (fireTimer >= fireDelay)
		{
			Instantiate(new EnemyBullet(px + 86, py + 110));

			fireTimer = 0;
		}
	}

}



void Enemy::OnTriggerStay2D(GameObject* other)
{
	string tag = other->GetTag();

	if (tag == "������")
	{
		if (isPlayerExpCollided == false)
		{
			isPlayerExpCollided = true;

			hp = hp - 10; //���⿡ ���� ������ �����ϱ�
			printf("���� ü�� %f\n", hp);

			//������ ����ȿ��
			float px = other->GetPx();
			float py = other->GetPy();

			Instantiate(new LaserExp(px - 14, py));

			Destroy(other); // ������ �����ϱ�

			if (80 <= hp && hp <= 100)
			{
				Play(0);
			}
			else if (50 <= hp && hp < 80)
			{
				Play(1);
			}
			else if (0 <= hp && hp < 50)
			{
				Play(2);
				state = State::fall; //���� �߶����·� ����(transition)
			}
			else if (hp <= 0)
			{
				//���� ����
				px = this->GetPx();
				py = this->GetPy();
				Instantiate(new EnemyExp(px - 18, py - 90));
				//���� ����
				Destroy(this);

				//���� ���� ī��Ʈ�ϱ�
				EnemySpawner* spawner = EnemySpawner::Instance();
				spawner->AddDestroy();

				int p = Random::Range(0, 10000);
				/*�������
				if (p < 1000)
				{
					
					//�Ѿ˾����� ��� (������)
					Instantiate(new BulletItem(px + 80, py + 40));
				}
				*/
				
				if (dropBulletItem == true)
				{
					Instantiate(new BulletItem(px + 80, py + 40));
				}
				


			}

		}
	}
	else if (tag == "�÷��̾�")
	{
		printf("---���⿡ �÷��̾ �浹��--- \n");
	}
	else if (tag == "��ź����")
	{
		if (isBombExpCollided == false) // ������ �浹ó���� �ȵǾ������� 
		{
			isBombExpCollided = true; //�浹ó�� ������ ǥ��

			//���� ����ȿ��
			float px = this->GetPx();
			float py = this->GetPy();
			Instantiate(new EnemyExp(px - 18, py - 90),1);


			//���� ���� 
			Destroy(this);

			//���� ���� ī��Ʈ�ϱ�
			EnemySpawner* spawner = EnemySpawner::Instance();
			spawner->AddDestroy();

			//�Ѿ˾����� ��� (������)
			Instantiate(new BulletItem(px + 80, py + 40));
		}
	}
}


