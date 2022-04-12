#include "ShootingGame.h"

Player::Player(float px, float py) : GameObject("플레이어","", true, px, py)
{
	this->speed = 250;			 //이동스피드
	this->showUpspeed = 250;	 //스폰스피드
	this->fireTimer = 0  ;		 //발사타이머 측정 변수
	this->fireDelay = 0.2;		 //발사지연 세팅 변수
	this->index = 3;			 //애니메이션 인덱스
	this->animTimer = 0;		 //애니메이션 시간측정 변수
	this->animDelay = 0.1f;		 // 애니메이션 지연시간 지정 변수
	this->hp = 10;				 //플레이어 체력
	this->state = State::showUp; //시작상태 초기화
	this->bulletCount = 1;
	
}

Player::~Player()
{}

void Player::Start()
{
	//플레이어 애니메이션 이미지 직접 로드//


		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 0, 0, 62, 80, &sprite[0]);
		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 1, 0, 62, 80, &sprite[1]);
		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 2, 0, 62, 80, &sprite[2]);
		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 3, 0, 62, 80, &sprite[3]);
		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 4, 0, 62, 80, &sprite[4]);
		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 5, 0, 62, 80, &sprite[5]);
		Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 64 * 6, 0, 62, 80, &sprite[6]);
	

	//Bitmap::ReadBMP("Asset/팬텀이동2.bmp", 192, 0, 62, 80, &sprite);

	//충돌제 추가하기//
	AddBoxCollider2D(26,9, 9, 61);
	AddBoxCollider2D(9, 37, 44, 14);

}

void Player::Update()
{
	if (state == State::showUp)
	{
		Translate(0, -showUpspeed * Time::deltaTime);

		if (GetPy() <= HEIGHT - 200)
		{
			state = State::control;
		}
	}
	else if (state == State::control)
	{
		Move();
		Fire();
	}


}
void Player::Draw()
{
	float px = GetPx();
	float py = GetPy();

	
	Bitmap::DrawBMP(px, py, &sprite[index]);
	
}
void Player::Move()
{
	//이동하기//
	float dist = Time::deltaTime * speed;

	if ( Input::GetKey(KeyCode::UpArrow) == true )  
	{
		Translate(0, -dist);

		if (GetPy() < 0)
		{
			SetPy(0);
		}


	}

	if ( Input::GetKey(KeyCode::DownArrow)==true)
	{
		Translate(0, dist);

		if (GetPy() > HEIGHT - 75)
		{
			SetPy(HEIGHT - 75);
		}
	}

	if (Input::GetKey(KeyCode::LeftArrow)==true)
	{
		Translate(-dist, 0);

		if (GetPx() < -8)
		{
			SetPx(-8);
		}
		//이미지 변경//
		animTimer += Time::deltaTime;
		
		if (animTimer >= animDelay)
		{
			index--;

			if (index < 0)
			{
				index = 0;
			}
			
			animTimer = 0;
		}

	}

	if (Input::GetKey(KeyCode::RightArrow)==true)
	{
		Translate(dist, 0);

		if (GetPx() > WIDTH - 54)
		{
			SetPx(WIDTH - 54);
		}

		animTimer += Time::deltaTime;

		if (animTimer >= animDelay)
		{
			index++;

			//이미지 변경//
			if (index > 7)
			{
				index = 6;
			}

			animTimer = 0;
		}



	}
	if (Input::GetKey(KeyCode::LeftArrow) != true && Input::GetKey(KeyCode::RightArrow) != true)
	{
		animTimer += Time::deltaTime;

		if (animTimer >= animDelay)
		{
			if (index < 3)
			{
				index++;
			}
			else if (index > 3)
			{
				index--;
			}

			animTimer = 0;
		}



	}
}

void Player::Fire()
{
	//연속 자동 레이저 발사하기//
	if (Input::GetKey(KeyCode::Space) == true)
	{
		fireTimer = fireTimer + Time::deltaTime;

		if (fireTimer >= fireDelay)
		{
			float px = GetPx();
			float py = GetPy();

			/////////////레이저 한발 발사////////////////
			//레이저 객체...생성하기//
			Instantiate(new Laser(px + 34 - 6, py+5));
			
			if (bulletCount == 2)
			{
				/////////////레이저 두발 발사////////////////
				//레이저 객체...생성하기//
				Instantiate(new Laser(px + 34 - 3 - 7, py - 30));
				Instantiate(new Laser(px + 34 - 3 + 7, py - 30));
			}
			else if (bulletCount == 3)
			{
				///////////////레이저 세발 발사//////////////
				//레이저 객체...생성하기//
				Instantiate(new Laser(px + 34 - 3 - 7, py - 28));
				Instantiate(new Laser(px + 34 - 3,     py - 38));
				Instantiate(new Laser(px + 34 - 3 + 7, py - 28));
			}

			//발사타이머...리셋
			fireTimer = 0;
		}
	}	
	
	//폭탄 발사
	if(Input::GetKeyDown(KeyCode::Z)==true)
	{
		float px = GetPx();
		float py = GetPy();

		Instantiate(new Bomb(px+15, py-15));

		
	}
}


void Player::OnTriggerStay2D(GameObject* other)
{
	string tag = other->GetTag();
	
		if (tag == "적기총알" && state == State::control)
		{
			hp = hp - 10; //적기에 피해 데미지 적용하기
			printf("플레이어 체력 %f\n", hp);

			//레이저 폭발효과
			float px = other->GetPx();
			float py = other->GetPy();

			Instantiate(new BulletExp(px - 14, py));

			Destroy(other); // 데이터 삭제하기


			if (hp <= 0)
			{
				//플레이어 폭발
				float px, py;

				other->GetPosition(px, py);

				Instantiate(new EnemyExp(px - 90, py - 140));
				//플레이어 제거
				Destroy(this);



				//[임시]플레이어 리스폰하기//
				ObjectManager::Instantiate(new Player(WIDTH / 2 - 34, HEIGHT + 100));
				bulletCount = 0;


			}
		}
		else if (tag == "총알아이템")
		{
			//아이템 제거

			Destroy(other);

			//총알(레이저) 발사갯수 증가
			if (bulletCount < 3)
			{
				bulletCount++;
			}
			

		}


	
	
}
