#include "ShootingGame.h"


//생성자, 소멸자//
GameObject::GameObject(string tag, string name, bool active, float px, float py)
{
	this->tag	 = tag;
	this->name	 = name;
	this->active = active;

	this->px = px;
	this->py = py;

	this->isDead = false;

}

GameObject::~GameObject()
{}

//게터, 세터//
string GameObject::GetTag()
{
	return tag;
}

string GameObject::GetName()
{
	return name;
}

bool GameObject::GetActive()
{
	return active;
}

float GameObject::GetPx()
{
	return px;
}

float GameObject::GetPy()
{
	return py;
}
bool GameObject::GetDead()
{
	return isDead;
}
void GameObject::SetTag(string tag)
{
	this->tag = tag;
}

void GameObject::SetName(string name)
{
	this->name = name;
}

void GameObject::SetActive(bool active)
{
	this->active = active;
}

void GameObject::SetPx(float px)
{
	//새로운 위치값(px) - 변경 이전의 x 좌표(this->px) = 이동값(dx)//
	float dx = px - this->px; //이동량

	this->px = px; //게임오브젝트 위치 지정

	//충돌체에 이동량 적용하기

	collider.Translate(dx, 0);
}

void GameObject::SetPy(float py)
{
	//새로운 위치값(py) - 변경 이전의 x 좌표(this->py) = 이동값(dy)//
	float dy = py - this->py;

	this->py = py;

	collider.Translate(0, dy);
}
void GameObject::SetDead(bool dead)
{
	this->isDead = true;
}

void GameObject::Translate(float x, float y)
{
	//게임오브젝트 좌표 이동

	px = px + x;
	py = py + y;

	//충돌체 좌표이동

	collider.Translate(x, y);
}

void GameObject::AddBoxCollider2D(float x, float y, float width, float height)
{
	collider = BoxCollider2D(x + px, y + py, width, height);
}
void GameObject::OnDrawGizmos()
{
	//박스 충돌체 사각형 그리기//
	float x, y, width, height;
	

	collider.GetBox(x, y, width, height);

	float x2 = x + width;
	float y2 = y + height;

	DrawLine(x , y,  x2,  y, 255, 0, 0);
	DrawLine(x2, y,  x2, y2, 255, 0, 0);
	DrawLine(x , y2, x2, y2, 255, 0, 0);
	DrawLine(x , y,  x,  y2, 255, 0, 0);
	
}
void GameObject::OnTriggerStay2D(GameObject * other)
{
	
}
BoxCollider2D GameObject::GetCollider()
{
	return collider;
}


void GameObject::Instantiate(GameObject* obj)
{
	ObjectManager::Instantiate(obj);
}

void GameObject::Destroy(GameObject* obj)
{
	ObjectManager::Destroy(obj);
}
