#pragma once
#include <string>
#include <vector>
#include "BoxCollider2D.h"

using namespace std;

class GameObject
{
private:
	//기본속성(인스펙터 - Inspector)//
	string tag;
	string name;
	bool   active;

	//변환속성(트랜스폼 - Transform)//
	float px, py;

	//2D 박스 콜라이더(충돌체)(BoxCollider 2D) 추가하기
	vector<BoxCollider2D> collider;

	//객체 삭제 표시 변수
	bool isDead;

public:
	//생성자, 소멸자//
	GameObject(string tag, string name, bool active, float px, float py);
	virtual ~GameObject();

	//게터, 세터//
	string GetTag();
	string GetName();
	bool   GetActive();
	bool GetDead();

	float GetPx();
	float GetPy();
	void GetPosition(float& px, float& py);

	void SetTag(string tag);
	void SetName(string name);
	void SetActive(bool active);

	void SetPx(float px);
	void SetPy(float py);
	void SetDead(bool Dead);

	//기본 가상함수//
	virtual void Start()  = 0;
	virtual void Update() = 0;
	virtual void Draw()   = 0;

	//기타 활용 함수//
	void Translate(float x, float y);

	//충돌 박스 기즈모 그리기 함수
	virtual void OnDrawGizmos();

	//게임오브젝트 추가/삭제하기//
	void Instantiate(GameObject* obj,int layer = 0);
	void Destroy(GameObject* obj);

	//충돌체 추가하기//
	void AddBoxCollider2D(float x , float y, float width , float height);
	

	//충돌체 게터//
	vector<BoxCollider2D> GetCollider();
	

	//충돌 정보 처리함수//
	virtual void OnTriggerStay2D(GameObject* other);
	
};

